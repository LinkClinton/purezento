#include "Runtime/runtime.hpp"

#include "Extensions/ImGui/imgui.hpp"

#include <random>
#include <memory>

std::default_random_engine engine;

std::shared_ptr<float> radius = std::make_shared<float>(10.f);

void draw_circle(
	const std::vector<std::string>& arguments,
	const std::shared_ptr<purezento::console>& console,
	const std::shared_ptr<void>& ctx)
{
	std::uniform_real_distribution<float> pRange(0, 500);
	std::uniform_real_distribution<float> sRange(10, 30);
	
	const auto render = std::static_pointer_cast<purezento::render>(ctx);

	render->draw_elements["circle"].push_back(
		purezento::draw_element::circle(
			purezento::circle(
				purezento::vec2(pRange(engine), pRange(engine)),
				*radius
			),
			purezento::color(1, 0, 0)
		)
	);
}

void circle_radius(
	const std::shared_ptr<purezento::config>& config,
	const std::shared_ptr<void>& ctx)
{
	ImGui::InputFloat("Radius", static_cast<float*>(ctx.get()));
}

int main() {
	auto runtime =
		std::make_shared<purezento::runtime>(
			purezento::runtime_startup("UnitTest",
				purezento::font("./Consola.ttf", 12),
				1280, 720)
			);

	runtime->console()->callbacks.insert( {
		"whz",
		purezento::command_callback(draw_circle, runtime->render())
	});

	runtime->config()->callbacks.insert({
		"Circle",
		purezento::config_callback(circle_radius, radius)
		});

	runtime->run_loop();
}