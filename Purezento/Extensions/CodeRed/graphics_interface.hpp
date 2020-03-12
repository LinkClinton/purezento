#pragma once

#include "../../Interface/noncopyable.hpp"

#include <memory>

namespace CodeRed {

	class GpuGraphicsCommandList;
	class GpuCommandAllocator;
	class GpuLogicalDevice;
	class GpuCommandQueue;
	class GpuFrameBuffer;
	class GpuRenderPass;
	class GpuSwapChain;

	class ImGuiWindows;

	class graphics_interface : public purezento::noncopyable {
	public:
		explicit graphics_interface();

		~graphics_interface() = default;

		auto device() const noexcept -> std::shared_ptr<GpuLogicalDevice> { return m_device; }

		auto allocator() const noexcept -> std::shared_ptr<GpuCommandAllocator> { return m_allocator; }

		auto queue() const noexcept -> std::shared_ptr<GpuCommandQueue> { return m_queue; }
	private:
		std::shared_ptr<GpuLogicalDevice> m_device;
		std::shared_ptr<GpuCommandAllocator> m_allocator;
		std::shared_ptr<GpuCommandQueue> m_queue;
	};
	
}
