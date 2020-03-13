#include "graphics_interface.hpp"

#include "CodeRed/Core/CodeRedGraphics.hpp"

#include <cassert>

CodeRed::graphics_interface::graphics_interface()
{
	const auto system_info = std::make_shared<DirectX12SystemInfo>();
	const auto adapters = system_info->selectDisplayAdapter();

	assert(!adapters.empty());
	
	m_device = std::make_shared<DirectX12LogicalDevice>(adapters[0]);

	m_allocator = m_device->createCommandAllocator();
	m_queue = m_device->createCommandQueue();
}