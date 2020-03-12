#include "runtime_sharing.hpp"
#include "runtime.hpp"

purezento::runtime_sharing::runtime_sharing(runtime* runtime) :
	m_runtime(runtime)
{
	
}

auto purezento::runtime_sharing::graphics_interface() const noexcept -> std::shared_ptr<CodeRed::graphics_interface>
{
	return m_runtime->m_graphics_interface;
}
