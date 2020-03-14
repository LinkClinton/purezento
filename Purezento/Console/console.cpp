#include "console.hpp"

#include "../Extensions/ImGui/imgui.hpp"
#include "../Config/config.hpp"

purezento::console::console(
	const std::shared_ptr<runtime_sharing>& sharing) :
	m_runtime_sharing(sharing)
{
	std::memset(m_buffer.data(), 0, m_buffer.size() * sizeof(char));
}

void purezento::console::update(float delta)
{
	if (!m_runtime_sharing->config()->m_console_window_info.visible) return;

	ImGui::Begin("Console", &m_runtime_sharing->config()->m_console_window_info.visible,
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoMove);

	const auto width = m_runtime_sharing->config()->m_console_window_info.size.x;
	const auto height = m_runtime_sharing->config()->m_console_window_info.size.y;
	
	ImGui::SetWindowSize(ImVec2(width, height));
	ImGui::SetWindowPos(ImVec2(0, m_runtime_sharing->height() - height));

	const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();

	ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1));

	for (const auto& text : texts) {
		ImGui::TextColored(
			ImColor(
				static_cast<int>(text.color.red * 255),
				static_cast<int>(text.color.green * 255),
				static_cast<int>(text.color.blue * 255),
				static_cast<int>(text.color.alpha * 255)
			),
			text.text.c_str()
		);
	}

	if (m_scroll_to_bottom)
		ImGui::SetScrollHereY(1.0f);

	m_scroll_to_bottom = false;
	
	ImGui::PopStyleVar();
	ImGui::EndChild();
	ImGui::Separator();

	bool reclaim_focus = false;

	ImGui::AlignTextToFramePadding();
	ImGui::Text("command :"); ImGui::SameLine();

	ImGui::AlignTextToFramePadding();
	if (ImGui::InputText("##Input", m_buffer.data(), m_buffer.size(), ImGuiInputTextFlags_EnterReturnsTrue)) {
		execute_command(m_buffer.data());
		
		std::memset(m_buffer.data(), 0, m_buffer.size() * sizeof(char));

		m_scroll_to_bottom = true;
		reclaim_focus = true;
	}

	if (reclaim_focus) ImGui::SetKeyboardFocusHere(-1);
	
	ImGui::End();
}

void purezento::console::execute_command(const std::string& command)
{
	static color common_color(0, 0, 0, 1);
	static color error_color(1, 0, 0, 1);

	texts.push_back({
		command,
		common_color
		});
	
	std::vector<std::string> arguments;
	std::string text;

	for (const auto& c : command) {
		if (c == ' ' && !text.empty()) { arguments.push_back(text); text.clear(); }

		if (c != ' ') text.push_back(c);
	}

	if (!text.empty()) arguments.push_back(text);

	// invalid command
	if (arguments.empty()) {
		texts.push_back({
			"error : command is invalid.",
			error_color
			});

		return;
	}

	// command not found
	if (callbacks.find(arguments[0]) == callbacks.end()) {
		texts.push_back({
			"error : command not found.",
			error_color
			});

		return;
	}

	callbacks[arguments[0]].function(arguments, shared_from_this(), callbacks[arguments[0]].context);
}
