#include "Runtime/runtime.hpp"

#include <random>
#include <memory>

std::default_random_engine engine;

void draw_circle(
	const std::vector<std::string>& arguments,
	const std::shared_ptr<purezento::console>& console,
	void* ctx)
{
	std::uniform_real_distribution<float> pRange(0, 500);
	std::uniform_real_distribution<float> sRange(10, 30);
	
	const auto render = static_cast<purezento::render*>(ctx);

	render->draw_elements.push_back(
		purezento::draw_element::circle(
			purezento::circle(
				purezento::vec2(pRange(engine), pRange(engine)),
				sRange(engine)
			),
			purezento::color(1, 0, 0)
		)
	);
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
		purezento::command_callback(draw_circle, runtime->render().get())
	});

	runtime->run_loop();
}