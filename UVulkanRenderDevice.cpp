#include "pch.h"
#include "UVulkanRenderDevice.h"

static std::map<std::string, std::string> mConfiguration;

VKAPI_ATTR VkBool32 VKAPI_CALL DebugReportCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* layerPrefix, const char* message, void* userData)
{
	switch (flags)
	{
	case VK_DEBUG_REPORT_INFORMATION_BIT_EXT:
		Log(info) << "------DebugReport(Info)------" << std::endl;
		Log(info) << "ObjectType: " << objectType << std::endl;
		Log(info) << "Object: " << object << std::endl;
		Log(info) << "Location: " << location << std::endl;
		Log(info) << "MessageCode: " << messageCode << std::endl;
		Log(info) << "LayerPrefix: " << layerPrefix << std::endl;
		Log(info) << "Message: " << message << std::endl;
		Log(info) << "-----------------------------" << std::endl;
		break;
	case VK_DEBUG_REPORT_WARNING_BIT_EXT:
		Log(warning) << "------DebugReport(Warn)------" << std::endl;
		Log(warning) << "ObjectType: " << objectType << std::endl;
		Log(warning) << "Object: " << object << std::endl;
		Log(warning) << "Location: " << location << std::endl;
		Log(warning) << "MessageCode: " << messageCode << std::endl;
		Log(warning) << "LayerPrefix: " << layerPrefix << std::endl;
		Log(warning) << "Message: " << message << std::endl;
		Log(warning) << "-----------------------------" << std::endl;
		break;
	case VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT:
		Log(warning) << "------DebugReport(Perf)------" << std::endl;
		Log(warning) << "ObjectType: " << objectType << std::endl;
		Log(warning) << "Object: " << object << std::endl;
		Log(warning) << "Location: " << location << std::endl;
		Log(warning) << "MessageCode: " << messageCode << std::endl;
		Log(warning) << "LayerPrefix: " << layerPrefix << std::endl;
		Log(warning) << "Message: " << message << std::endl;
		Log(warning) << "-----------------------------" << std::endl;
		break;
	case VK_DEBUG_REPORT_ERROR_BIT_EXT:
		Log(error) << "------DebugReport(Error)------" << std::endl;
		Log(error) << "ObjectType: " << objectType << std::endl;
		Log(error) << "Object: " << object << std::endl;
		Log(error) << "Location: " << location << std::endl;
		Log(error) << "MessageCode: " << messageCode << std::endl;
		Log(error) << "LayerPrefix: " << layerPrefix << std::endl;
		Log(error) << "Message: " << message << std::endl;
		Log(error) << "------------------------------" << std::endl;
		break;
	case VK_DEBUG_REPORT_DEBUG_BIT_EXT:
		Log(warning) << "------DebugReport(Debug)------" << std::endl;
		Log(warning) << "ObjectType: " << objectType << std::endl;
		Log(warning) << "Object: " << object << std::endl;
		Log(warning) << "Location: " << location << std::endl;
		Log(warning) << "MessageCode: " << messageCode << std::endl;
		Log(warning) << "LayerPrefix: " << layerPrefix << std::endl;
		Log(warning) << "Message: " << message << std::endl;
		Log(warning) << "------------------------------" << std::endl;
		break;
	default:
		Log(error) << "------DebugReport(?)------" << std::endl;
		Log(error) << "ObjectType: " << objectType << std::endl;
		Log(error) << "Object: " << object << std::endl;
		Log(error) << "Location: " << location << std::endl;
		Log(error) << "MessageCode: " << messageCode << std::endl;
		Log(error) << "LayerPrefix: " << layerPrefix << std::endl;
		Log(error) << "Message: " << message << std::endl;
		Log(error) << "--------------------------" << std::endl;
		break;
	}

	return VK_FALSE;
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugReportCallbackEXT(
	VkInstance                                  instance,
	const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
	const VkAllocationCallbacks* pAllocator,
	VkDebugReportCallbackEXT* pCallback)
{
	if (pfn_vkCreateDebugReportCallbackEXT == nullptr)
	{
		return VK_NOT_READY;
	}

	return pfn_vkCreateDebugReportCallbackEXT(
		instance,
		pCreateInfo,
		pAllocator,
		pCallback
	);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyDebugReportCallbackEXT(
	VkInstance                                  instance,
	VkDebugReportCallbackEXT                    callback,
	const VkAllocationCallbacks* pAllocator)
{
	if (pfn_vkDestroyDebugReportCallbackEXT == nullptr)
	{
		return;
	}

	pfn_vkDestroyDebugReportCallbackEXT(
		instance,
		callback,
		pAllocator
	);
}

VKAPI_ATTR void VKAPI_CALL vkDebugReportMessageEXT(
	VkInstance                                  instance,
	VkDebugReportFlagsEXT                       flags,
	VkDebugReportObjectTypeEXT                  objectType,
	uint64_t                                    object,
	size_t                                      location,
	int32_t                                     messageCode,
	const char* pLayerPrefix,
	const char* pMessage)
{
	if (pfn_vkDebugReportMessageEXT == nullptr)
	{
		return;
	}

	pfn_vkDebugReportMessageEXT(
		instance,
		flags,
		objectType,
		object,
		location,
		messageCode,
		pLayerPrefix,
		pMessage
	);
}

const uint32_t DEFAULT_RENDERING_STATE_VERT[] =
#include "DefaultRenderingState.vert.h"
;

const uint32_t DEFAULT_RENDERING_STATE_FRAG[] =
#include "DefaultRenderingState.frag.h"
;

//I can use the element count to switch between zero, single, double, tripple, and quad texture.
const vk::VertexInputAttributeDescription gStandardVertexInputAttributeDescription[6] =
{
	vk::VertexInputAttributeDescription(0U,0U,vk::Format::eR32G32B32Sfloat,0),
	vk::VertexInputAttributeDescription(1U,0U,vk::Format::eR32G32B32A32Sfloat,12),
	vk::VertexInputAttributeDescription(2U,2U,vk::Format::eR32G32Sfloat,0),
	vk::VertexInputAttributeDescription(3U,3U,vk::Format::eR32G32Sfloat,0),
	vk::VertexInputAttributeDescription(4U,4U,vk::Format::eR32G32Sfloat,0),
	vk::VertexInputAttributeDescription(5U,5U,vk::Format::eR32G32Sfloat,0)
};

const vk::VertexInputAttributeDescription gTwoColorVertexInputAttributeDescription[7] =
{
	vk::VertexInputAttributeDescription(0U,0U,vk::Format::eR32G32B32Sfloat,0),
	vk::VertexInputAttributeDescription(1U,0U,vk::Format::eR32G32B32A32Sfloat,12),
	vk::VertexInputAttributeDescription(2U,1U,vk::Format::eR32G32B32A32Sfloat,0),
	vk::VertexInputAttributeDescription(3U,2U,vk::Format::eR32G32Sfloat,0),
	vk::VertexInputAttributeDescription(4U,3U,vk::Format::eR32G32Sfloat,0),
	vk::VertexInputAttributeDescription(5U,4U,vk::Format::eR32G32Sfloat,0),
	vk::VertexInputAttributeDescription(6U,5U,vk::Format::eR32G32Sfloat,0)
};

IMPLEMENT_CLASS(UVulkanRenderDevice);

UVulkanRenderDevice::UVulkanRenderDevice()
{
	guard(UVulkanRenderDevice::UVulkanRenderDevice);
	Log(info) << "UVulkanRenderDevice::UVulkanRenderDevice" << std::endl;
	unguard;
}

void UVulkanRenderDevice::StaticConstructor()
{
	guard(UVulkanRenderDevice::UVulkanRenderDevice);

	//Setup Defaults;
	mConfiguration["LogFile"] = "C:\\Log\\VKUT99.log";
	mConfiguration["VSync"] = "1";
	mConfiguration["LogLevel"] = "0"; //Debug 0 Release 3
	mConfiguration["EnableDebugLayers"] = "1"; //Debug 1 Release 0

	//Load Configuration
	LoadConfiguration("VKUT99.conf");

	//Setup Logging.
	LogManager::Create(mConfiguration["LogFile"], (SeverityLevel)std::stoi(mConfiguration["LogLevel"]));

	unguard;
}

UBOOL UVulkanRenderDevice::Init(UViewport* InViewport, INT NewX, INT NewY, INT NewColorBytes, UBOOL Fullscreen)
{
	BOOL canPresent = false;
	bool enableDebugLayers = true;

	guard(UVulkanRenderDevice::Init);

	//Figure out what layers and extensions to enable.
	{
		std::vector<const char*> extensionNames;
		std::vector<const char*> layerNames;

		if (!mConfiguration["EnableDebugLayers"].empty())
		{
			enableDebugLayers = std::stoi(mConfiguration["EnableDebugLayers"]);
		}

		extensionNames.push_back("VK_KHR_surface");
		extensionNames.push_back("VK_KHR_win32_surface");

		if (enableDebugLayers)
		{
			extensionNames.push_back("VK_EXT_debug_report");
			layerNames.push_back("VK_LAYER_LUNARG_standard_validation");
		}

		//Create an instance (unique instance will auto destroy)
		vk::ApplicationInfo applicationInfo("Unreal Tournament", 99, "Unreal Tournament", 1, VK_MAKE_VERSION(1, 1, 0));
		vk::InstanceCreateInfo createInfo({}, &applicationInfo, static_cast<uint32_t>(layerNames.size()), layerNames.data(), static_cast<uint32_t>(extensionNames.size()), extensionNames.data());
		mInstance = vk::createInstanceUnique(createInfo);
		for (char const* name : extensionNames)
		{
			Log(info) << "Loaded Instance Extension: " << name << std::endl;
		}
	}

	if (enableDebugLayers)
	{
		/*
		If we are debugging then grab the function pointers for the debug methods.
		We have to do this because these are extensions so they aren't definded by default.
		*/
		pfn_vkCreateDebugReportCallbackEXT = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(mInstance->getProcAddr("vkCreateDebugReportCallbackEXT"));
		pfn_vkDebugReportMessageEXT = reinterpret_cast<PFN_vkDebugReportMessageEXT>(mInstance->getProcAddr("vkDebugReportMessageEXT"));
		pfn_vkDestroyDebugReportCallbackEXT = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(mInstance->getProcAddr("vkDestroyDebugReportCallbackEXT"));

		/*
		Now we need to create our callback which will be called when the validation layers catch something.
		From there it's up to us to capture that information in some way. In our case we'll pass it along to the logger.
		*/
		const vk::DebugReportCallbackCreateInfoEXT callbackCreateInfo(
			vk::DebugReportFlagBitsEXT::eWarning | vk::DebugReportFlagBitsEXT::eError | vk::DebugReportFlagBitsEXT::ePerformanceWarning,
			&DebugReportCallback,
			this);
		mCallback = mInstance->createDebugReportCallbackEXTUnique(callbackCreateInfo);
	}

	//Grab the physical devices so we can figure out which one to use.
	mPhysicalDevices = mInstance->enumeratePhysicalDevices();
	mPhysicalDeviceIndex = 0;

	//Count VRAM to try to to guess the most powerful GPU.
	vk::DeviceSize largestSize = 0;
	for (int32_t i = 0; i < (int32_t)mPhysicalDevices.size(); i++)
	{
		vk::PhysicalDeviceMemoryProperties physicalDeviceMemoryProperties;
		mPhysicalDevices[mPhysicalDeviceIndex].getMemoryProperties(&physicalDeviceMemoryProperties);
		vk::DeviceSize size = 0;
		for (int32_t j = 0; j < (int32_t)physicalDeviceMemoryProperties.memoryHeapCount; j++)
		{
			size += physicalDeviceMemoryProperties.memoryHeaps[j].size;
		}
		if (size > largestSize)
		{
			mPhysicalDeviceIndex = i;
		}
	}

	//Grab the properties for GetAdapterIdentifier and other calls.
	mPhysicalDevices[mPhysicalDeviceIndex].getMemoryProperties(&mPhysicalDeviceMemoryProperties);
	mPhysicalDevices[mPhysicalDeviceIndex].getProperties(&mPhysicalDeviceProperties);

	Log(info) << "DeviceName: " << mPhysicalDeviceProperties.deviceName << std::endl;
	Log(info) << "APIVersion: " << mPhysicalDeviceProperties.apiVersion << std::endl;
	Log(info) << "DriverVersion: " << mPhysicalDeviceProperties.driverVersion << std::endl;
	Log(info) << "VendorId: " << mPhysicalDeviceProperties.vendorID << std::endl;
	Log(info) << "PhysicalDeviceIndex: " << mPhysicalDeviceIndex << std::endl;

	//Look for a queue that supports graphics
	mQueueFamilyProperties = mPhysicalDevices[mPhysicalDeviceIndex].getQueueFamilyProperties();
	mGraphicsQueueFamilyIndex = std::distance(mQueueFamilyProperties.begin(), std::find_if(mQueueFamilyProperties.begin(), mQueueFamilyProperties.end(), [](vk::QueueFamilyProperties const& qfp) { return qfp.queueFlags & vk::QueueFlagBits::eGraphics; }));

	//Create a device and command pool (unique device will auto destroy)
	{
		float queuePriority = 0.0f;
		const vk::DeviceQueueCreateInfo deviceQueueCreateInfo(vk::DeviceQueueCreateFlags(), static_cast<uint32_t>(mGraphicsQueueFamilyIndex), 1, &queuePriority);

		auto device = mPhysicalDevices[mPhysicalDeviceIndex];
		vk::PhysicalDeviceFeatures features;
		device.getFeatures(&features);

		std::vector<char const*> deviceExtensionNames;
		deviceExtensionNames.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
		deviceExtensionNames.push_back("VK_KHR_maintenance1");

		mDevice = mPhysicalDevices[mPhysicalDeviceIndex].createDeviceUnique(vk::DeviceCreateInfo({}, 1, &deviceQueueCreateInfo, 0, nullptr, static_cast<uint32_t>(deviceExtensionNames.size()), deviceExtensionNames.data(), &features));
		for (char const* name : deviceExtensionNames)
		{
			Log(info) << "Loaded Device Extension: " << name << std::endl;
		}
		mCommandPool = mDevice->createCommandPoolUnique(vk::CommandPoolCreateInfo(vk::CommandPoolCreateFlagBits::eResetCommandBuffer, deviceQueueCreateInfo.queueFamilyIndex));
	}

	//Get the queue we found for graphics work.
	mDevice->getQueue(static_cast<uint32_t>(mGraphicsQueueFamilyIndex), 0, &mQueue);

	//Create a descriptor pool that should be able to allocate enough of any type.
	{
		//TODO: tune the number of descriptors in the pool
		const vk::DescriptorPoolSize descriptorPoolSizes[11] =
		{
			vk::DescriptorPoolSize(vk::DescriptorType::eSampler,std::min((uint32_t)MAX_DESCRIPTOR, mPhysicalDeviceProperties.limits.maxDescriptorSetSamplers)),
			vk::DescriptorPoolSize(vk::DescriptorType::eCombinedImageSampler,std::min((uint32_t)MAX_DESCRIPTOR, mPhysicalDeviceProperties.limits.maxPerStageDescriptorSamplers)),
			vk::DescriptorPoolSize(vk::DescriptorType::eSampledImage,std::min((uint32_t)MAX_DESCRIPTOR, mPhysicalDeviceProperties.limits.maxDescriptorSetSampledImages)),
			vk::DescriptorPoolSize(vk::DescriptorType::eStorageImage,std::min((uint32_t)MAX_DESCRIPTOR, mPhysicalDeviceProperties.limits.maxDescriptorSetStorageImages)),
			vk::DescriptorPoolSize(vk::DescriptorType::eUniformTexelBuffer,std::min((uint32_t)MAX_DESCRIPTOR, mPhysicalDeviceProperties.limits.maxPerStageDescriptorSampledImages)),
			vk::DescriptorPoolSize(vk::DescriptorType::eStorageTexelBuffer,std::min((uint32_t)MAX_DESCRIPTOR, mPhysicalDeviceProperties.limits.maxPerStageDescriptorStorageImages)),
			vk::DescriptorPoolSize(vk::DescriptorType::eUniformBuffer,std::min((uint32_t)MAX_DESCRIPTOR, mPhysicalDeviceProperties.limits.maxDescriptorSetUniformBuffers)),
			vk::DescriptorPoolSize(vk::DescriptorType::eStorageBuffer,std::min((uint32_t)MAX_DESCRIPTOR, mPhysicalDeviceProperties.limits.maxDescriptorSetStorageBuffers)),
			vk::DescriptorPoolSize(vk::DescriptorType::eUniformBufferDynamic,std::min((uint32_t)MAX_DESCRIPTOR, mPhysicalDeviceProperties.limits.maxDescriptorSetUniformBuffersDynamic)),
			vk::DescriptorPoolSize(vk::DescriptorType::eStorageBufferDynamic,std::min((uint32_t)MAX_DESCRIPTOR, mPhysicalDeviceProperties.limits.maxDescriptorSetStorageBuffersDynamic)),
			vk::DescriptorPoolSize(vk::DescriptorType::eInputAttachment,std::min((uint32_t)MAX_DESCRIPTOR, mPhysicalDeviceProperties.limits.maxDescriptorSetInputAttachments))
		};
		mDescriptorPool = mDevice->createDescriptorPoolUnique(vk::DescriptorPoolCreateInfo(vk::DescriptorPoolCreateFlags(), std::min(MAX_DESCRIPTOR, mPhysicalDeviceProperties.limits.maxDescriptorSetSamplers), 11, &descriptorPoolSizes[0]));
	}

	//Setup Pipeline Cache
	{
		vk::PipelineCacheCreateInfo const pipelineCacheInfo;
		mPipelineCache = mDevice->createPipelineCacheUnique(pipelineCacheInfo);
	}

	//Create Command Buffers, Fences, and semaphores
	{
		vk::SemaphoreCreateInfo semaphoreCreateInfo;
		vk::FenceCreateInfo fenceCreateInfo(vk::FenceCreateFlagBits::eSignaled);

		mDrawCommandBuffers = mDevice->allocateCommandBuffersUnique(vk::CommandBufferAllocateInfo(mCommandPool.get(), vk::CommandBufferLevel::ePrimary, 3));
		for (int32_t i = 0; i < (int32_t)mDrawCommandBuffers.size(); i++)
		{
			mDrawFences.push_back(mDevice->createFenceUnique(fenceCreateInfo));
			mImageAvailableSemaphores.push_back(mDevice->createSemaphoreUnique(semaphoreCreateInfo));
			mRenderFinishedSemaphores.push_back(mDevice->createSemaphoreUnique(semaphoreCreateInfo));
		}

		mUtilityCommandBuffers = mDevice->allocateCommandBuffersUnique(vk::CommandBufferAllocateInfo(mCommandPool.get(), vk::CommandBufferLevel::ePrimary, 7));
		for (int32_t i = 0; i < (int32_t)mUtilityCommandBuffers.size(); i++)
		{
			mUtilityFences.push_back(mDevice->createFenceUnique(fenceCreateInfo));
		}
	}

	//TODO: setup remaining rendering structures.

	//Snag the window handle and DC. After that try to set the new resolution
	{
		Viewport = InViewport;

		mHWND = (HWND)InViewport->GetWindow();
		check(mHWND);
		mHDC = GetDC(mHWND);
		check(mHDC);
		mHINSTANCE = GetModuleHandle(nullptr);
		check(mHINSTANCE);

		//Window is only passed in on init so we can assume the same window for this device.
		auto const createInfo = vk::Win32SurfaceCreateInfoKHR()
			.setHinstance(mHINSTANCE)
			.setHwnd(mHWND);
		mSurface = mInstance->createWin32SurfaceKHRUnique(createInfo);

		canPresent = mPhysicalDevices[mPhysicalDeviceIndex].getSurfaceSupportKHR(mGraphicsQueueFamilyIndex, mSurface.get());
		if (canPresent)
		{
			if (!SetRes(NewX, NewY, NewColorBytes, Fullscreen))
			{
				Exit();
				return false;
			}
		}
		else
		{
			Exit();
			//Return will happen anyway.
		}
	}

	Log(info) << "SurfaceSupportKHR: " << canPresent << std::endl;

	unguard;

	return canPresent;
}

UBOOL UVulkanRenderDevice::SetRes(INT NewX, INT NewY, INT NewColorBytes, UBOOL Fullscreen)
{
	guard(UVulkanRenderDevice::SetRes);

	//Stash the input parameters for later use.
	mNewX = NewX;
	mNewY = NewY;
	mNewColorBytes = NewColorBytes;
	mFullscreen = Fullscreen;

	Log(info) << "NewX: " << NewX << std::endl;
	Log(info) << "NewY: " << NewY << std::endl;
	Log(info) << "NewColorBytes: " << NewColorBytes << std::endl;
	Log(info) << "Fullscreen: " << Fullscreen << std::endl;

	//Destroy old surface info if there is any.
	mFrameBuffers.clear();
	mRenderPass.reset(vk::RenderPass());
	mImageViews.clear();
	mSwapChainImages.clear();
	mSwapChain.reset(vk::SwapchainKHR());
	mFormats.clear();

	//Grab surface information.
	mFormats = mPhysicalDevices[mPhysicalDeviceIndex].getSurfaceFormatsKHR(mSurface.get());
	mFormat = mFormats[0].format;
	mColorSpace = mFormats[0].colorSpace;
	//Log(info) << "Format: " << mFormat << std::endl;
	//Log(info) << "ColorSpace: " << mColorSpace << std::endl;

	mSurfaceCapabilities = mPhysicalDevices[mPhysicalDeviceIndex].getSurfaceCapabilitiesKHR(mSurface.get());
	if (mSurfaceCapabilities.currentExtent.width == std::numeric_limits<uint32_t>::max())
	{
		//Get real viewport size
		if (Viewport != nullptr)
		{
			NewX = Viewport->SizeX;
			NewY = Viewport->SizeY;
		}

		//Don't break editor and tiny windowed mode
		if (NewX < 16) NewX = 16;
		if (NewY < 16) NewY = 16;

		// If the surface size is undefined, the size is set to the size of the images requested.
		mSwapchainExtent.width = std::clamp((uint32_t)NewX, mSurfaceCapabilities.minImageExtent.width, mSurfaceCapabilities.maxImageExtent.width);
		mSwapchainExtent.height = std::clamp((uint32_t)NewY, mSurfaceCapabilities.minImageExtent.height, mSurfaceCapabilities.maxImageExtent.height);
	}
	else
	{
		// If the surface size is defined, the swap chain size must match
		mSwapchainExtent = mSurfaceCapabilities.currentExtent;
	}
	Log(info) << "SwapchainExtentHeight: " << mSwapchainExtent.height << std::endl;
	Log(info) << "SwapchainExtentWidth: " << mSwapchainExtent.width << std::endl;

	/*
	Now we need to figure out what presentation mode to use. We'll fall back to Fifo if there is nothing better.
	Mailbox is prefered but immediate is second best.
	If the parameters say to use V-Sync then just roll with FIFO regardless of what is available.
	*/
	mSwapchainPresentMode = vk::PresentModeKHR::eFifo;
	if (!mConfiguration["VSync"].empty() && !std::stoi(mConfiguration["VSync"]))
	{
		Log(info) << "VSync: false" << std::endl;
		auto presentModes = mPhysicalDevices[mPhysicalDeviceIndex].getSurfacePresentModesKHR(mSurface.get());
		for (auto& presentMode : presentModes)
		{
			if (presentMode == vk::PresentModeKHR::eMailbox)
			{
				mSwapchainPresentMode = vk::PresentModeKHR::eMailbox;
				break;
			}
			else if (presentMode == vk::PresentModeKHR::eImmediate)
			{
				mSwapchainPresentMode = vk::PresentModeKHR::eImmediate;
			}
		}
	}
	else
	{
		Log(info) << "VSync: true" << std::endl;
	}
	//Log(info) << "SwapchainPresentMode: " << mSwapchainPresentMode << std::endl;

	//If I need to handle seperate present and graphics queue then do that here.

	//Setup swap chain, frame buffer, and render target
	const vk::SurfaceTransformFlagBitsKHR preTransform = (mSurfaceCapabilities.supportedTransforms & vk::SurfaceTransformFlagBitsKHR::eIdentity) ? vk::SurfaceTransformFlagBitsKHR::eIdentity : mSurfaceCapabilities.currentTransform;
	const vk::CompositeAlphaFlagBitsKHR compositeAlpha =
		(mSurfaceCapabilities.supportedCompositeAlpha & vk::CompositeAlphaFlagBitsKHR::ePreMultiplied) ? vk::CompositeAlphaFlagBitsKHR::ePreMultiplied :
		(mSurfaceCapabilities.supportedCompositeAlpha & vk::CompositeAlphaFlagBitsKHR::ePostMultiplied) ? vk::CompositeAlphaFlagBitsKHR::ePostMultiplied :
		(mSurfaceCapabilities.supportedCompositeAlpha & vk::CompositeAlphaFlagBitsKHR::eInherit) ? vk::CompositeAlphaFlagBitsKHR::eInherit : vk::CompositeAlphaFlagBitsKHR::eOpaque;

	mSwapChainCreateInfo
		.setSurface(mSurface.get())
		.setMinImageCount(mSurfaceCapabilities.minImageCount)
		.setImageFormat(mFormat)
		.setImageColorSpace(mColorSpace)
		.setImageExtent(mSwapchainExtent)
		.setImageArrayLayers(1)
		.setImageUsage(vk::ImageUsageFlagBits::eColorAttachment | vk::ImageUsageFlagBits::eTransferDst)
		.setImageSharingMode(vk::SharingMode::eExclusive)
		.setQueueFamilyIndexCount(0)
		.setPQueueFamilyIndices(nullptr)
		.setPreTransform(preTransform)
		.setCompositeAlpha(compositeAlpha)
		.setPresentMode(mSwapchainPresentMode)
		.setClipped(true)
		.setOldSwapchain(nullptr);

	mSwapChain = mDevice->createSwapchainKHRUnique(mSwapChainCreateInfo);
	mSwapChainImages = mDevice->getSwapchainImagesKHR(mSwapChain.get());
	mImageViews.reserve(mSwapChainImages.size());

	{
		const vk::ComponentMapping componentMapping(vk::ComponentSwizzle::eR, vk::ComponentSwizzle::eG, vk::ComponentSwizzle::eB, vk::ComponentSwizzle::eA);
		const vk::ImageSubresourceRange subResourceRange(vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1);
		for (auto image : mSwapChainImages)
		{
			const vk::ImageViewCreateInfo imageViewCreateInfo(vk::ImageViewCreateFlags(), image, vk::ImageViewType::e2D, mFormat, componentMapping, subResourceRange);
			mImageViews.push_back(mDevice->createImageViewUnique(imageViewCreateInfo));
		}
	}

	//Setup Depth Buffer

	mDepthFormat = vk::Format::eD16Unorm;
	vk::FormatProperties formatProperties = mPhysicalDevices[mPhysicalDeviceIndex].getFormatProperties(mDepthFormat);

	vk::ImageTiling tiling;
	if (formatProperties.linearTilingFeatures & vk::FormatFeatureFlagBits::eDepthStencilAttachment)
	{
		tiling = vk::ImageTiling::eLinear;
	}
	else if (formatProperties.optimalTilingFeatures & vk::FormatFeatureFlagBits::eDepthStencilAttachment)
	{
		tiling = vk::ImageTiling::eOptimal;
	}
	else
	{
		throw std::runtime_error("DepthStencilAttachment is not supported for D16Unorm depth format.");
	}

	vk::ImageCreateInfo imageCreateInfo(vk::ImageCreateFlags(), vk::ImageType::e2D, mDepthFormat, vk::Extent3D(mSwapchainExtent.width, mSwapchainExtent.height, 1), 1, 1, vk::SampleCountFlagBits::e1, tiling, vk::ImageUsageFlagBits::eDepthStencilAttachment);
	mDepthImage = mDevice->createImageUnique(imageCreateInfo);

	vk::PhysicalDeviceMemoryProperties memoryProperties = mPhysicalDevices[mPhysicalDeviceIndex].getMemoryProperties();
	vk::MemoryRequirements memoryRequirements = mDevice->getImageMemoryRequirements(mDepthImage.get());
	uint32_t typeBits = memoryRequirements.memoryTypeBits;
	uint32_t typeIndex = uint32_t(~0);
	for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++)
	{
		if ((typeBits & 1) && ((memoryProperties.memoryTypes[i].propertyFlags & vk::MemoryPropertyFlagBits::eDeviceLocal) == vk::MemoryPropertyFlagBits::eDeviceLocal))
		{
			typeIndex = i;
			break;
		}
		typeBits >>= 1;
	}
	assert(typeIndex != ~0);
	mDepthMemory = mDevice->allocateMemoryUnique(vk::MemoryAllocateInfo(memoryRequirements.size, typeIndex));

	mDevice->bindImageMemory(mDepthImage.get(), mDepthMemory.get(), 0);
	{
		const vk::ComponentMapping componentMapping(vk::ComponentSwizzle::eR, vk::ComponentSwizzle::eG, vk::ComponentSwizzle::eB, vk::ComponentSwizzle::eA);
		vk::ImageSubresourceRange subResourceRange(vk::ImageAspectFlagBits::eDepth, 0, 1, 0, 1);
		mDepthView = mDevice->createImageViewUnique(vk::ImageViewCreateInfo(vk::ImageViewCreateFlags(), mDepthImage.get(), vk::ImageViewType::e2D, mDepthFormat, componentMapping, subResourceRange));
	}

	//Setup Render pass and frame buffer.

	vk::AttachmentDescription attachments[2];
	attachments[0] = vk::AttachmentDescription(vk::AttachmentDescriptionFlags(), mFormat, vk::SampleCountFlagBits::e1, vk::AttachmentLoadOp::eLoad, vk::AttachmentStoreOp::eStore, vk::AttachmentLoadOp::eLoad, vk::AttachmentStoreOp::eStore, vk::ImageLayout::eUndefined, vk::ImageLayout::eColorAttachmentOptimal);
	attachments[1] = vk::AttachmentDescription(vk::AttachmentDescriptionFlags(), mDepthFormat, vk::SampleCountFlagBits::e1, vk::AttachmentLoadOp::eClear, vk::AttachmentStoreOp::eStore, vk::AttachmentLoadOp::eClear, vk::AttachmentStoreOp::eStore, vk::ImageLayout::eUndefined, vk::ImageLayout::eDepthStencilAttachmentOptimal);

	vk::AttachmentReference colorReference(0, vk::ImageLayout::eColorAttachmentOptimal);
	vk::AttachmentReference depthReference(1, vk::ImageLayout::eDepthStencilAttachmentOptimal);
	vk::SubpassDescription subpass(vk::SubpassDescriptionFlags(), vk::PipelineBindPoint::eGraphics, 0, nullptr, 1, &colorReference, nullptr, &depthReference);

	mRenderPass = mDevice->createRenderPassUnique(vk::RenderPassCreateInfo(vk::RenderPassCreateFlags(), 2, attachments, 1, &subpass));

	vk::ImageView frameAttachments[2];

	vk::FramebufferCreateInfo framebufferCreateInfo;
	framebufferCreateInfo.renderPass = mRenderPass.get();
	framebufferCreateInfo.attachmentCount = 2;
	framebufferCreateInfo.pAttachments = frameAttachments;
	framebufferCreateInfo.width = mSwapchainExtent.width;
	framebufferCreateInfo.height = mSwapchainExtent.height;
	framebufferCreateInfo.layers = 1;

	frameAttachments[1] = mDepthView.get();
	for (auto& imageView : mImageViews)
	{
		frameAttachments[0] = imageView.get();
		mFrameBuffers.push_back(mDevice->createFramebufferUnique(framebufferCreateInfo, nullptr));
	}

	//Setup viewport and scissor based on new size. (include half-pixel offset)
	mScissor = vk::Rect2D(vk::Offset2D(0, 0), vk::Extent2D(mSwapchainExtent.width, mSwapchainExtent.height));

	mViewport
		.setX(0.0f - 0.5f)
		.setY(static_cast<float>(mSwapchainExtent.height) - 0.5f)
		.setWidth(static_cast<float>(mSwapchainExtent.width) - 0.5f)
		.setHeight(-(static_cast<float>(mSwapchainExtent.height) - 0.5f))
		.setMinDepth(0.0f)
		.setMaxDepth(1.0f);

	unguard;

	return true;
}

void UVulkanRenderDevice::Exit(void)
{
	guard(UVulkanRenderDevice::Exit);
	//TODO: check to see if I really need to use this.
	Log(info) << "UVulkanRenderDevice::Exit" << std::endl;
	unguard;
}

void UVulkanRenderDevice::Flush(UBOOL AllowPrecache)
{
	guard(UVulkanRenderDevice::Flush);
	Log(info) << "UVulkanRenderDevice::Flush" << std::endl;
	unguard;
}

void UVulkanRenderDevice::Lock(FPlane InFlashScale, FPlane InFlashFog, FPlane ScreenClear, DWORD RenderLockFlags, BYTE* InHitData, INT* InHitSize)
{
	guard(UVulkanRenderDevice::Lock);

	//TODO: Reset any stats or counters.

	mFrameIndex = (mFrameIndex++) % mSwapChainImages.size();
	mDevice->waitForFences(1, &mDrawFences[mFrameIndex].get(), VK_TRUE, UINT64_MAX);
	mDevice->resetFences(1, &mDrawFences[mFrameIndex].get());

	mDevice->acquireNextImageKHR(mSwapChain.get(), UINT64_MAX, mImageAvailableSemaphores[mFrameIndex].get(), vk::Fence(), &mImageIndex);

	vk::ImageMemoryBarrier prePresentBarrier;
	prePresentBarrier.srcAccessMask = vk::AccessFlags();
	prePresentBarrier.dstAccessMask = vk::AccessFlagBits::eMemoryRead;
	prePresentBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	prePresentBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	prePresentBarrier.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };

	auto& commandBuffer = mDrawCommandBuffers[mFrameIndex].get();
	vk::CommandBufferBeginInfo beginInfo(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);
	commandBuffer.begin(&beginInfo);

	const std::array<float, 4> colorValues = { ScreenClear.X, ScreenClear.Y, ScreenClear.Z, ScreenClear.W };
	mClearValues[0].color = vk::ClearColorValue(colorValues);
	mClearValues[1].depthStencil = vk::ClearDepthStencilValue(1.0f, 0);

	//Always clear z but only clear color if LOCKR_ClearScreen is set.
	if (RenderLockFlags & LOCKR_ClearScreen)
	{
		prePresentBarrier.image = mSwapChainImages[mImageIndex];
		prePresentBarrier.oldLayout = vk::ImageLayout::eUndefined;
		prePresentBarrier.newLayout = vk::ImageLayout::eTransferDstOptimal;
		commandBuffer.pipelineBarrier(vk::PipelineStageFlagBits::eAllCommands, vk::PipelineStageFlagBits::eAllCommands, vk::DependencyFlags(), 0, nullptr, 0, nullptr, 1, &prePresentBarrier);

		vk::ImageSubresourceRange subResourceRange;
		subResourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
		subResourceRange.baseMipLevel = 0;
		subResourceRange.levelCount = 1;
		subResourceRange.baseArrayLayer = 0;
		subResourceRange.layerCount = 1;
		commandBuffer.clearColorImage(mSwapChainImages[mImageIndex], vk::ImageLayout::eTransferDstOptimal, &mClearValues[0].color, 1, &subResourceRange);

		prePresentBarrier.image = mSwapChainImages[mImageIndex];
		prePresentBarrier.oldLayout = vk::ImageLayout::eTransferDstOptimal;
		prePresentBarrier.newLayout = vk::ImageLayout::eColorAttachmentOptimal;
		commandBuffer.pipelineBarrier(vk::PipelineStageFlagBits::eAllCommands, vk::PipelineStageFlagBits::eAllCommands, vk::DependencyFlags(), 0, nullptr, 0, nullptr, 1, &prePresentBarrier);
	}

	//Start the render pass so the worker rendering will end up in our framebuffer.
	mRenderPassBeginInfo.renderPass = mRenderPass.get();
	mRenderPassBeginInfo.framebuffer = mFrameBuffers[mFrameIndex].get();
	mRenderPassBeginInfo.renderArea.offset.x = 0;
	mRenderPassBeginInfo.renderArea.offset.y = 0;
	mRenderPassBeginInfo.renderArea.extent.width = mSwapchainExtent.width;
	mRenderPassBeginInfo.renderArea.extent.height = mSwapchainExtent.height;
	mRenderPassBeginInfo.clearValueCount = 2;
	mRenderPassBeginInfo.pClearValues = mClearValues;
	commandBuffer.beginRenderPass(&mRenderPassBeginInfo, vk::SubpassContents::eInline);

	unguard;
}

void UVulkanRenderDevice::Unlock(UBOOL Blit)
{
	guard(UVulkanRenderDevice::Unlock);

	auto& commandBuffer = mDrawCommandBuffers[mFrameIndex].get();

	commandBuffer.endRenderPass();

	vk::ImageMemoryBarrier prePresentBarrier;
	prePresentBarrier.srcAccessMask = vk::AccessFlags();
	prePresentBarrier.dstAccessMask = vk::AccessFlagBits::eMemoryRead;
	prePresentBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	prePresentBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	prePresentBarrier.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
	prePresentBarrier.image = mSwapChainImages[mImageIndex];
	prePresentBarrier.oldLayout = vk::ImageLayout::eColorAttachmentOptimal;
	prePresentBarrier.newLayout = vk::ImageLayout::ePresentSrcKHR;
	commandBuffer.pipelineBarrier(vk::PipelineStageFlagBits::eAllCommands, vk::PipelineStageFlagBits::eAllCommands, vk::DependencyFlags(), 0, nullptr, 0, nullptr, 1, &prePresentBarrier);

	commandBuffer.end();

	//Now that we have the work all bundled up we need to submit it to the
	vk::PipelineStageFlags pipelineFlag[] = { vk::PipelineStageFlagBits::eColorAttachmentOutput };
	vk::SubmitInfo submitInfo;
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = &mImageAvailableSemaphores[mFrameIndex].get();
	submitInfo.pWaitDstStageMask = pipelineFlag;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = &mRenderFinishedSemaphores[mFrameIndex].get();
	mQueue.submit(1, &submitInfo, mDrawFences[mFrameIndex].get());

	//Take the swap chain image and display it to the screen.
	if (Blit)
	{
		vk::PresentInfoKHR presentInfo;
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = &mRenderFinishedSemaphores[mFrameIndex].get();
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = &mSwapChain.get();
		presentInfo.pImageIndices = &mImageIndex;
		mQueue.presentKHR(&presentInfo);
	}

	unguard;
}

void UVulkanRenderDevice::DrawComplexSurface(FSceneNode* Frame, FSurfaceInfo& Surface, FSurfaceFacet& Facet)
{
	guard(UVulkanRenderDevice::DrawComplexSurface);
	Log(info) << "UVulkanRenderDevice::DrawComplexSurface" << std::endl;
	unguard;
}

void UVulkanRenderDevice::DrawGouraudPolygon(FSceneNode* Frame, FTextureInfo& Info, FTransTexture** Pts, int NumPts, DWORD PolyFlags, FSpanBuffer* Span)
{
	guard(UVulkanRenderDevice::DrawGouraudPolygon);
	Log(info) << "UVulkanRenderDevice::DrawGouraudPolygon" << std::endl;
	unguard;
}

void UVulkanRenderDevice::DrawTile(FSceneNode* Frame, FTextureInfo& Info, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL, FLOAT U, FLOAT V, FLOAT UL, FLOAT VL, class FSpanBuffer* Span, FLOAT Z, FPlane Color, FPlane Fog, DWORD PolyFlags)
{
	guard(UVulkanRenderDevice::DrawTile);
	Log(info) << "UVulkanRenderDevice::DrawTile" << std::endl;
	unguard;
}

void UVulkanRenderDevice::Draw2DLine(FSceneNode* Frame, FPlane Color, DWORD LineFlags, FVector P1, FVector P2)
{
	guard(UVulkanRenderDevice::Draw2DLine);
	Log(info) << "UVulkanRenderDevice::Draw2DLine" << std::endl;
	unguard;
}

void UVulkanRenderDevice::Draw2DPoint(FSceneNode* Frame, FPlane Color, DWORD LineFlags, FLOAT X1, FLOAT Y1, FLOAT X2, FLOAT Y2, FLOAT Z)
{
	guard(UVulkanRenderDevice::Draw2DPoint);
	Log(info) << "UVulkanRenderDevice::Draw2DPoint" << std::endl;
	unguard;
}

void UVulkanRenderDevice::ClearZ(FSceneNode* Frame)
{
	guard(UVulkanRenderDevice::ClearZ);

	//The depth is setup as clear in the render pass so just stop and start it. The Color is load/store so that should be safe.
	auto& commandBuffer = mDrawCommandBuffers[mFrameIndex].get();
	commandBuffer.endRenderPass();
	commandBuffer.beginRenderPass(&mRenderPassBeginInfo, vk::SubpassContents::eInline);

	unguard;
}

void UVulkanRenderDevice::PushHit(const BYTE* Data, INT Count)
{
	guard(UVulkanRenderDevice::PushHit);
	Log(info) << "UVulkanRenderDevice::PushHit" << std::endl;
	unguard;
}

void UVulkanRenderDevice::PopHit(INT Count, UBOOL bForce)
{
	guard(UVulkanRenderDevice::PopHit);
	Log(info) << "UVulkanRenderDevice::PopHit" << std::endl;
	unguard;
}

void UVulkanRenderDevice::GetStats(TCHAR* Result)
{
	guard(UVulkanRenderDevice::GetStats);
	Log(info) << "UVulkanRenderDevice::GetStats" << std::endl;
	unguard;
}

void UVulkanRenderDevice::ReadPixels(FColor* Pixels)
{
	guard(UVulkanRenderDevice::ReadPixels);
	Log(info) << "UVulkanRenderDevice::ReadPixels" << std::endl;
	unguard;
}

void UVulkanRenderDevice::LoadConfiguration(std::string filename)
{
	std::string key;
	std::string value;
	std::ifstream input(filename);

	while (input)
	{
		//load key/value pair
		std::getline(input, key, '=');
		std::getline(input, value, '\n');

		//scrub \r out just in case this is a DOS/Windows format file.
		key.erase(std::remove(key.begin(), key.end(), '\r'), key.end());
		value.erase(std::remove(value.begin(), value.end(), '\r'), value.end());

		//Handle leading and trailing spaces.
		Trim(key);
		Trim(value);

		mConfiguration[key] = value;
	}

	input.close();
}