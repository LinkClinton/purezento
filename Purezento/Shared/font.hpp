#pragma once

#include <string>

namespace purezento {
	
	struct font {
		std::string name = "";
		size_t size = 20;

		font() = default;

		font(const std::string& name, const size_t size) :
			name(name), size(size) {}
	};

}
