#include "Runtime/runtime.hpp"

#include <memory>

int main() {

	auto runtime =
		std::make_shared<purezento::runtime>(
			purezento::runtime_startup("UnitTest",
				purezento::font("WTF", 20),
				1920, 1080)
			);

	runtime->run_loop();
}