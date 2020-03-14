#pragma once

#include "../Extensions/CodeRed/graphics_interface.hpp"
#include "../Interface/noncopyable.hpp"

#include <memory>

namespace purezento {
	
	class runtime;
	class config;
	
	class runtime_sharing : public noncopyable {
	public:
		explicit runtime_sharing(runtime* runtime);

		~runtime_sharing() = default;
		
		auto graphics_interface() const noexcept -> std::shared_ptr<CodeRed::graphics_interface>;

		auto config() const noexcept -> std::shared_ptr<purezento::config>;
		
		auto width() const noexcept -> size_t;

		auto height() const noexcept -> size_t;
	private:
		runtime* m_runtime;
	};
	
}
