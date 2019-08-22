#include "pch.h"
#include "VulkanRenderDevice.h"

VKAPI_ATTR VkBool32 VKAPI_CALL DebugReportCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* layerPrefix, const char* message, void* userData)
{
	switch (flags)
	{
	case VK_DEBUG_REPORT_INFORMATION_BIT_EXT:
		//Log(info) << "------DebugReport(Info)------" << std::endl;
		//Log(info) << "ObjectType: " << objectType << std::endl;
		//Log(info) << "Object: " << object << std::endl;
		//Log(info) << "Location: " << location << std::endl;
		//Log(info) << "MessageCode: " << messageCode << std::endl;
		//Log(info) << "LayerPrefix: " << layerPrefix << std::endl;
		//Log(info) << "Message: " << message << std::endl;
		//Log(info) << "-----------------------------" << std::endl;
		break;
	case VK_DEBUG_REPORT_WARNING_BIT_EXT:
/*		Log(warning) << "------DebugReport(Warn)------" << std::endl;
		Log(warning) << "ObjectType: " << objectType << std::endl;
		Log(warning) << "Object: " << object << std::endl;
		Log(warning) << "Location: " << location << std::endl;
		Log(warning) << "MessageCode: " << messageCode << std::endl;
		Log(warning) << "LayerPrefix: " << layerPrefix << std::endl;
		Log(warning) << "Message: " << message << std::endl;
		Log(warning) << "-----------------------------" << std::endl*/;
		break;
	case VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT:
		//Log(warning) << "------DebugReport(Perf)------" << std::endl;
		//Log(warning) << "ObjectType: " << objectType << std::endl;
		//Log(warning) << "Object: " << object << std::endl;
		//Log(warning) << "Location: " << location << std::endl;
		//Log(warning) << "MessageCode: " << messageCode << std::endl;
		//Log(warning) << "LayerPrefix: " << layerPrefix << std::endl;
		//Log(warning) << "Message: " << message << std::endl;
		//Log(warning) << "-----------------------------" << std::endl;
		break;
	case VK_DEBUG_REPORT_ERROR_BIT_EXT:
		//Log(error) << "------DebugReport(Error)------" << std::endl;
		//Log(error) << "ObjectType: " << objectType << std::endl;
		//Log(error) << "Object: " << object << std::endl;
		//Log(error) << "Location: " << location << std::endl;
		//Log(error) << "MessageCode: " << messageCode << std::endl;
		//Log(error) << "LayerPrefix: " << layerPrefix << std::endl;
		//Log(error) << "Message: " << message << std::endl;
		//Log(error) << "------------------------------" << std::endl;
		break;
	case VK_DEBUG_REPORT_DEBUG_BIT_EXT:
		//Log(warning) << "------DebugReport(Debug)------" << std::endl;
		//Log(warning) << "ObjectType: " << objectType << std::endl;
		//Log(warning) << "Object: " << object << std::endl;
		//Log(warning) << "Location: " << location << std::endl;
		//Log(warning) << "MessageCode: " << messageCode << std::endl;
		//Log(warning) << "LayerPrefix: " << layerPrefix << std::endl;
		//Log(warning) << "Message: " << message << std::endl;
		//Log(warning) << "------------------------------" << std::endl;
		break;
	default:
		//Log(error) << "------DebugReport(?)------" << std::endl;
		//Log(error) << "ObjectType: " << objectType << std::endl;
		//Log(error) << "Object: " << object << std::endl;
		//Log(error) << "Location: " << location << std::endl;
		//Log(error) << "MessageCode: " << messageCode << std::endl;
		//Log(error) << "LayerPrefix: " << layerPrefix << std::endl;
		//Log(error) << "Message: " << message << std::endl;
		//Log(error) << "--------------------------" << std::endl;
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

UBOOL VulkanRenderDevice::Init(UViewport* InViewport, INT NewX, INT NewY, INT NewColorBytes, UBOOL Fullscreen)
{
	//Setup Defaults;
	mConfiguration["LogFile"] = "VKUT99.log";
	mConfiguration["VSync"] = "1";
#ifdef _DEBUG
	mConfiguration["LogLevel"] = "0";
	mConfiguration["EnableDebugLayers"] = "1";
	bool enableDebugLayers = true;
#else
	mConfiguration["LogLevel"] = "3";
	mConfiguration["EnableDebugLayers"] = "0";
	bool enableDebugLayers = false;
#endif

	//Load Configuration
	LoadConfiguration("VKUT99.conf");

	//Setup Logging.
	LogManager::Create(mConfiguration["LogFile"], (SeverityLevel)std::stoi(mConfiguration["LogLevel"]));

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

		mDrawCommandBuffers = mDevice->allocateCommandBuffersUnique(vk::CommandBufferAllocateInfo(mCommandPool.get(), vk::CommandBufferLevel::ePrimary, 2));
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
		mHWND = (HWND)InViewport->GetWindow();
		mHDC = GetDC(mHWND);

		if (!SetRes(NewX, NewY, NewColorBytes, Fullscreen))
		{
			Exit();
			return false;
		}
	}

	return true;
}

UBOOL VulkanRenderDevice::SetRes(INT NewX, INT NewY, INT NewColorBytes, UBOOL Fullscreen)
{

}

void VulkanRenderDevice::Exit(void)
{

}

void VulkanRenderDevice::Flush(UBOOL AllowPrecache)
{

}

void VulkanRenderDevice::Lock(FPlane InFlashScale, FPlane InFlashFog, FPlane ScreenClear, DWORD RenderLockFlags, BYTE* InHitData, INT* InHitSize)
{

}

void VulkanRenderDevice::Unlock(UBOOL Blit)
{
	//Present happens here.
}

void VulkanRenderDevice::DrawComplexSurface(FSceneNode* Frame, FSurfaceInfo& Surface, FSurfaceFacet& Facet)
{

}

void VulkanRenderDevice::DrawGouraudPolygon(FSceneNode* Frame, FTextureInfo& Info, FTransTexture** Pts, INT NumPts, DWORD PolyFlags, FSpanBuffer* Span)
{

}

void VulkanRenderDevice::DrawTile(FSceneNode* Frame, FTextureInfo& Info, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL, FLOAT U, FLOAT V, FLOAT UL, FLOAT VL, class FSpanBuffer* Span, FLOAT Z, FPlane Color, FPlane Fog, DWORD PolyFlags)
{

}

void VulkanRenderDevice::Draw2DLine(FSceneNode* Frame, FPlane Color, DWORD LineFlags, FVector P1, FVector P2)
{

}

void VulkanRenderDevice::Draw2DPoint(FSceneNode* Frame, FPlane Color, DWORD LineFlags, FLOAT X1, FLOAT Y1, FLOAT X2, FLOAT Y2, FLOAT Z)
{

}

void VulkanRenderDevice::ClearZ(FSceneNode* Frame)
{

}

void VulkanRenderDevice::PushHit(const BYTE* Data, INT Count)
{

}

void VulkanRenderDevice::PopHit(INT Count, UBOOL bForce)
{

}

void VulkanRenderDevice::GetStats(TCHAR* Result)
{

}

void VulkanRenderDevice::ReadPixels(FColor* Pixels)
{

}

void VulkanRenderDevice::LoadConfiguration(std::string filename)
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