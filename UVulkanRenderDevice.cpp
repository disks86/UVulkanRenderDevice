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
	vk::VertexInputAttributeDescription(1U,0U,vk::Format::eR32G32B32A32Sfloat,VEC3_SIZE),
	vk::VertexInputAttributeDescription(2U,2U,vk::Format::eR32G32Sfloat,0),
	vk::VertexInputAttributeDescription(3U,3U,vk::Format::eR32G32Sfloat,0),
	vk::VertexInputAttributeDescription(4U,4U,vk::Format::eR32G32Sfloat,0),
	vk::VertexInputAttributeDescription(5U,5U,vk::Format::eR32G32Sfloat,0)
};

const vk::VertexInputBindingDescription gStandardVertexInputBindingDescription[6] =
{
	vk::VertexInputBindingDescription(0U,VEC3_SIZE + VEC4_SIZE,vk::VertexInputRate::eVertex),
	vk::VertexInputBindingDescription(1U,VEC3_SIZE,vk::VertexInputRate::eVertex),
	vk::VertexInputBindingDescription(2U,VEC2_SIZE,vk::VertexInputRate::eVertex),
	vk::VertexInputBindingDescription(3U,VEC2_SIZE,vk::VertexInputRate::eVertex),
	vk::VertexInputBindingDescription(4U,VEC2_SIZE,vk::VertexInputRate::eVertex),
	vk::VertexInputBindingDescription(5U,VEC2_SIZE,vk::VertexInputRate::eVertex)
};

const vk::VertexInputAttributeDescription gTwoColorVertexInputAttributeDescription[7] =
{
	vk::VertexInputAttributeDescription(0U,0U,vk::Format::eR32G32B32Sfloat,0),
	vk::VertexInputAttributeDescription(1U,0U,vk::Format::eR32G32B32A32Sfloat,VEC3_SIZE),
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

	//Load Configuration (May completely replace with UT properties at some point.)
	LoadConfiguration("VKUT99.conf");

	//Setup properties.
#define CPP_PROPERTY_LOCAL(_name) _name, CPP_PROPERTY(_name)
#define CPP_PROPERTY_LOCAL_DCV(_name) DCV._name, CPP_PROPERTY(DCV._name)

	AddFloatConfigParam(TEXT("LODBias"), CPP_PROPERTY_LOCAL(LODBias), 0.0f);
	AddIntConfigParam(TEXT("MaxAnisotropy"), CPP_PROPERTY_LOCAL(MaxAnisotropy), 0);
	AddIntConfigParam(TEXT("LogLevel"), CPP_PROPERTY_LOCAL(LogLevel), 0); //Debug 0 Release 3
	AddIntConfigParam(TEXT("MinLogTextureSize"), CPP_PROPERTY_LOCAL(MinLogTextureSize), 0);
	AddIntConfigParam(TEXT("MaxLogTextureSize"), CPP_PROPERTY_LOCAL(MaxLogTextureSize), 8);
	AddBoolConfigParam(0, TEXT("UseTripleBuffering"), CPP_PROPERTY_LOCAL(UseTripleBuffering), 0);
	AddBoolConfigParam(0, TEXT("EnableDebugLayers"), CPP_PROPERTY_LOCAL(EnableDebugLayers), 1);
	AddBoolConfigParam(0, TEXT("UseVSync"), CPP_PROPERTY_LOCAL(UseVSync), 1);

#undef CPP_PROPERTY_LOCAL
#undef CPP_PROPERTY_LOCAL_DCV

	//Setup Logging.
	LogManager::Create(mConfiguration["LogFile"], (SeverityLevel)LogLevel);

	unguard;
}

UBOOL UVulkanRenderDevice::Init(UViewport* InViewport, INT NewX, INT NewY, INT NewColorBytes, UBOOL Fullscreen)
{
	//UT flags
	Viewport = InViewport;
	SpanBased = false;
	FullscreenOnly = false;
	SupportsFogMaps = false;
	SupportsTC = true;
	SupportsDistanceFog = false;
	SupportsLazyTextures = false;
	Coronas = true;
	DetailTextures = true;
	ShinySurfaces = true;
	HighDetailActors = true;
	VolumetricLighting = true;

	//Start Vulkan
	BOOL canPresent = false;

	guard(UVulkanRenderDevice::Init);

	//Figure out what layers and extensions to enable.
	{
		std::vector<const char*> extensionNames;
		std::vector<const char*> layerNames;

		extensionNames.push_back("VK_KHR_surface");
		extensionNames.push_back("VK_KHR_win32_surface");

		EnableDebugLayers = 1; //TODO: remove this line.
		if (EnableDebugLayers)
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

	if (EnableDebugLayers)
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
	{
		mPhysicalDevices = mInstance->enumeratePhysicalDevices();
		mPhysicalDeviceIndex = 0;
	}

	//Count VRAM to try to to guess the most powerful GPU.
	{
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
	}

	//Grab the properties for GetAdapterIdentifier and other calls.
	{
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
	}

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

	//Create Descriptor layout.
	const uint32_t textureCount = 4;
	{
		const vk::DescriptorSetLayoutBinding layoutBindings[3] =
		{
			vk::DescriptorSetLayoutBinding()
				.setBinding(0)
				.setDescriptorType(vk::DescriptorType::eUniformBuffer)
				.setDescriptorCount(1)
				.setStageFlags(vk::ShaderStageFlagBits::eVertex)
				.setPImmutableSamplers(nullptr),
			vk::DescriptorSetLayoutBinding()
				.setBinding(1)
				.setDescriptorType(vk::DescriptorType::eUniformBuffer)
				.setDescriptorCount(1)
				.setStageFlags(vk::ShaderStageFlagBits::eFragment)
				.setPImmutableSamplers(nullptr),
			vk::DescriptorSetLayoutBinding()
				.setBinding(2)
				.setDescriptorType(vk::DescriptorType::eCombinedImageSampler)
				.setDescriptorCount(textureCount)
				.setStageFlags(vk::ShaderStageFlagBits::eFragment)
				.setPImmutableSamplers(nullptr),
		};
		auto const descriptorLayout = vk::DescriptorSetLayoutCreateInfo().setBindingCount(3).setPBindings(layoutBindings);
		mDescriptorLayout = mDevice->createDescriptorSetLayoutUnique(descriptorLayout);
	}

	//Create Pipeline layout.
	{
		//std::array<vk::PushConstantRange, 1> ranges =
		//{
		//	vk::PushConstantRange
		//	{
		//		vk::ShaderStageFlagBits::eVertex,
		//		0,
		//		sizeof(uint32_t) * 4
		//	}
		//};

		//TODO: look into optimizations using push constants and/or specialization constants.

		auto const pipelineLayoutCreateInfo = vk::PipelineLayoutCreateInfo()
			.setSetLayoutCount(1)
			//.setPPushConstantRanges(ranges.data())
			//.setPushConstantRangeCount(1)
			.setPSetLayouts(&mDescriptorLayout.get());
		mPipelineLayout = mDevice->createPipelineLayoutUnique(pipelineLayoutCreateInfo);
	}

	//Create Color1Buffer
	{
		auto const upVertexBufferInfo = vk::BufferCreateInfo().setSize(MAX_BUFFERUPDATE).setUsage(vk::BufferUsageFlagBits::eVertexBuffer | vk::BufferUsageFlagBits::eTransferDst);
		mColor1Buffer = mDevice->createBufferUnique(upVertexBufferInfo);
		vk::MemoryRequirements mem_reqs;
		mDevice->getBufferMemoryRequirements(mColor1Buffer.get(), &mem_reqs);
		auto mem_alloc = vk::MemoryAllocateInfo().setAllocationSize(mem_reqs.size).setMemoryTypeIndex(0);
		FindMemoryTypeFromProperties(mem_reqs.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal, &mem_alloc.memoryTypeIndex);
		mColor1BufferMemory = mDevice->allocateMemoryUnique(mem_alloc);
		mDevice->bindBufferMemory(mColor1Buffer.get(), mColor1BufferMemory.get(), 0);
	}

	//Create Color2Buffer
	{
		auto const upVertexBufferInfo = vk::BufferCreateInfo().setSize(MAX_BUFFERUPDATE).setUsage(vk::BufferUsageFlagBits::eVertexBuffer | vk::BufferUsageFlagBits::eTransferDst);
		mColor2Buffer = mDevice->createBufferUnique(upVertexBufferInfo);
		vk::MemoryRequirements mem_reqs;
		mDevice->getBufferMemoryRequirements(mColor2Buffer.get(), &mem_reqs);
		auto mem_alloc = vk::MemoryAllocateInfo().setAllocationSize(mem_reqs.size).setMemoryTypeIndex(0);
		FindMemoryTypeFromProperties(mem_reqs.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal, &mem_alloc.memoryTypeIndex);
		mColor2BufferMemory = mDevice->allocateMemoryUnique(mem_alloc);
		mDevice->bindBufferMemory(mColor2Buffer.get(), mColor2BufferMemory.get(), 0);
	}

	//Create Texcoord1Buffer
	{
		auto const upVertexBufferInfo = vk::BufferCreateInfo().setSize(MAX_BUFFERUPDATE).setUsage(vk::BufferUsageFlagBits::eVertexBuffer | vk::BufferUsageFlagBits::eTransferDst);
		mTexcoord1Buffer = mDevice->createBufferUnique(upVertexBufferInfo);
		vk::MemoryRequirements mem_reqs;
		mDevice->getBufferMemoryRequirements(mTexcoord1Buffer.get(), &mem_reqs);
		auto mem_alloc = vk::MemoryAllocateInfo().setAllocationSize(mem_reqs.size).setMemoryTypeIndex(0);
		FindMemoryTypeFromProperties(mem_reqs.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal, &mem_alloc.memoryTypeIndex);
		mTexcoord1BufferMemory = mDevice->allocateMemoryUnique(mem_alloc);
		mDevice->bindBufferMemory(mTexcoord1Buffer.get(), mTexcoord1BufferMemory.get(), 0);
	}

	//Create Texcoord2Buffer
	{
		auto const upVertexBufferInfo = vk::BufferCreateInfo().setSize(MAX_BUFFERUPDATE).setUsage(vk::BufferUsageFlagBits::eVertexBuffer | vk::BufferUsageFlagBits::eTransferDst);
		mTexcoord2Buffer = mDevice->createBufferUnique(upVertexBufferInfo);
		vk::MemoryRequirements mem_reqs;
		mDevice->getBufferMemoryRequirements(mTexcoord2Buffer.get(), &mem_reqs);
		auto mem_alloc = vk::MemoryAllocateInfo().setAllocationSize(mem_reqs.size).setMemoryTypeIndex(0);
		FindMemoryTypeFromProperties(mem_reqs.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal, &mem_alloc.memoryTypeIndex);
		mTexcoord2BufferMemory = mDevice->allocateMemoryUnique(mem_alloc);
		mDevice->bindBufferMemory(mTexcoord2Buffer.get(), mTexcoord2BufferMemory.get(), 0);
	}

	//Create Texcoord3Buffer
	{
		auto const upVertexBufferInfo = vk::BufferCreateInfo().setSize(MAX_BUFFERUPDATE).setUsage(vk::BufferUsageFlagBits::eVertexBuffer | vk::BufferUsageFlagBits::eTransferDst);
		mTexcoord3Buffer = mDevice->createBufferUnique(upVertexBufferInfo);
		vk::MemoryRequirements mem_reqs;
		mDevice->getBufferMemoryRequirements(mTexcoord3Buffer.get(), &mem_reqs);
		auto mem_alloc = vk::MemoryAllocateInfo().setAllocationSize(mem_reqs.size).setMemoryTypeIndex(0);
		FindMemoryTypeFromProperties(mem_reqs.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal, &mem_alloc.memoryTypeIndex);
		mTexcoord3BufferMemory = mDevice->allocateMemoryUnique(mem_alloc);
		mDevice->bindBufferMemory(mTexcoord3Buffer.get(), mTexcoord3BufferMemory.get(), 0);
	}

	//Create Texcoord4Buffer
	{
		auto const upVertexBufferInfo = vk::BufferCreateInfo().setSize(MAX_BUFFERUPDATE).setUsage(vk::BufferUsageFlagBits::eVertexBuffer | vk::BufferUsageFlagBits::eTransferDst);
		mTexcoord4Buffer = mDevice->createBufferUnique(upVertexBufferInfo);
		vk::MemoryRequirements mem_reqs;
		mDevice->getBufferMemoryRequirements(mTexcoord4Buffer.get(), &mem_reqs);
		auto mem_alloc = vk::MemoryAllocateInfo().setAllocationSize(mem_reqs.size).setMemoryTypeIndex(0);
		FindMemoryTypeFromProperties(mem_reqs.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal, &mem_alloc.memoryTypeIndex);
		mTexcoord4BufferMemory = mDevice->allocateMemoryUnique(mem_alloc);
		mDevice->bindBufferMemory(mTexcoord4Buffer.get(), mTexcoord4BufferMemory.get(), 0);
	}

	//Create VertexUniformBuffer
	{
		auto const bufferInfo = vk::BufferCreateInfo().setSize(sizeof(VertexGlobalConstants)).setUsage(vk::BufferUsageFlagBits::eUniformBuffer | vk::BufferUsageFlagBits::eTransferDst);
		mVertexConstantBuffer = mDevice->createBufferUnique(bufferInfo);
		vk::MemoryRequirements mem_reqs;
		mDevice->getBufferMemoryRequirements(mVertexConstantBuffer.get(), &mem_reqs);
		auto mem_alloc = vk::MemoryAllocateInfo().setAllocationSize(mem_reqs.size).setMemoryTypeIndex(0);
		FindMemoryTypeFromProperties(mem_reqs.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal, &mem_alloc.memoryTypeIndex);
		mVertexConstantBufferMemory = mDevice->allocateMemoryUnique(mem_alloc);
		mDevice->bindBufferMemory(mVertexConstantBuffer.get(), mVertexConstantBufferMemory.get(), 0);
	}

	//Create FragmentUniformBuffer
	{
		auto const bufferInfo = vk::BufferCreateInfo().setSize(sizeof(FragmentGlobalConstants)).setUsage(vk::BufferUsageFlagBits::eUniformBuffer | vk::BufferUsageFlagBits::eTransferDst);
		mFragmentConstantBuffer = mDevice->createBufferUnique(bufferInfo);
		vk::MemoryRequirements mem_reqs;
		mDevice->getBufferMemoryRequirements(mFragmentConstantBuffer.get(), &mem_reqs);
		auto mem_alloc = vk::MemoryAllocateInfo().setAllocationSize(mem_reqs.size).setMemoryTypeIndex(0);
		FindMemoryTypeFromProperties(mem_reqs.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal, &mem_alloc.memoryTypeIndex);
		mFragmentConstantBufferMemory = mDevice->allocateMemoryUnique(mem_alloc);
		mDevice->bindBufferMemory(mFragmentConstantBuffer.get(), mFragmentConstantBufferMemory.get(), 0);
	}

	//Setup descriptor write structures
	{
		//Vertex Constants
		mDescriptorBufferInfo[0].buffer = mVertexConstantBuffer.get();
		mDescriptorBufferInfo[0].offset = 0;
		mDescriptorBufferInfo[0].range = sizeof(mVertexGlobalConstants);

		mWriteDescriptorSet[0].dstBinding = 0;
		mWriteDescriptorSet[0].dstArrayElement = 0;
		mWriteDescriptorSet[0].descriptorType = vk::DescriptorType::eUniformBuffer;
		mWriteDescriptorSet[0].descriptorCount = 1;
		mWriteDescriptorSet[0].pBufferInfo = &mDescriptorBufferInfo[0];

		//Fragment Constants
		mDescriptorBufferInfo[1].buffer = mFragmentConstantBuffer.get();
		mDescriptorBufferInfo[1].offset = 0;
		mDescriptorBufferInfo[1].range = sizeof(mFragmentGlobalConstants);

		mWriteDescriptorSet[1].dstBinding = 1;
		mWriteDescriptorSet[1].dstArrayElement = 0;
		mWriteDescriptorSet[1].descriptorType = vk::DescriptorType::eUniformBuffer;
		mWriteDescriptorSet[1].descriptorCount = 1;
		mWriteDescriptorSet[1].pBufferInfo = &mDescriptorBufferInfo[1];

		//Image
		mWriteDescriptorSet[2].dstBinding = 2;
		mWriteDescriptorSet[2].dstArrayElement = 0;
		mWriteDescriptorSet[2].descriptorType = vk::DescriptorType::eCombinedImageSampler;
		mWriteDescriptorSet[2].descriptorCount = textureCount;
		mWriteDescriptorSet[2].pImageInfo = mDescriptorImageInfo;
	}

	//Load Shaders
	{
		mDefaultRenderingStateVertex = LoadShaderFromConst(DEFAULT_RENDERING_STATE_VERT);
		mDefaultRenderingStateFragment = LoadShaderFromConst(DEFAULT_RENDERING_STATE_FRAG);
	}

	//TODO: setup remaining rendering structures.

	//Snag the window handle and DC. After that try to set the new resolution
	{
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

	//Misc UT setup
	if (MaxLogTextureSize <= 0)
	{
		MaxLogTextureSize = 12;
	}
	if (MinLogTextureSize <= 2)
	{
		MinLogTextureSize = 2;
	}

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
	if (!UseVSync)
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
		.setMinImageCount(std::clamp(2U, mSurfaceCapabilities.minImageCount, mSurfaceCapabilities.maxImageCount))
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

	vk::ImageCreateInfo imageCreateInfo(vk::ImageCreateFlags(), vk::ImageType::e2D, mDepthFormat, vk::Extent3D(mSwapchainExtent.width, mSwapchainExtent.height, 1), 1, 1, vk::SampleCountFlagBits::e1, tiling, vk::ImageUsageFlagBits::eDepthStencilAttachment | vk::ImageUsageFlagBits::eTransferDst);
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
	attachments[1] = vk::AttachmentDescription(vk::AttachmentDescriptionFlags(), mDepthFormat, vk::SampleCountFlagBits::e1, vk::AttachmentLoadOp::eLoad, vk::AttachmentStoreOp::eStore, vk::AttachmentLoadOp::eLoad, vk::AttachmentStoreOp::eStore, vk::ImageLayout::eUndefined, vk::ImageLayout::eDepthStencilAttachmentOptimal);

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
	mDevice->waitIdle();
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
	mDescriptorSetIndex = 0;
	mLastDescriptorSet = vk::DescriptorSet();
	mPipelines[mFrameIndex].clear();

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

	const VkDeviceSize offsetInBytes = 0;
	commandBuffer.bindVertexBuffers(0, 1, &mColor1Buffer.get(), &offsetInBytes);
	commandBuffer.bindVertexBuffers(1, 1, &mColor2Buffer.get(), &offsetInBytes);
	commandBuffer.bindVertexBuffers(2, 1, &mTexcoord1Buffer.get(), &offsetInBytes);
	commandBuffer.bindVertexBuffers(3, 1, &mTexcoord2Buffer.get(), &offsetInBytes);
	commandBuffer.bindVertexBuffers(4, 1, &mTexcoord3Buffer.get(), &offsetInBytes);
	commandBuffer.bindVertexBuffers(5, 1, &mTexcoord4Buffer.get(), &offsetInBytes);

	commandBuffer.setScissor(0, 1, &mScissor);
	commandBuffer.setViewport(0, 1, &mViewport);

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

	{
		prePresentBarrier.subresourceRange = { VK_IMAGE_ASPECT_DEPTH_BIT, 0, 1, 0, 1 };

		prePresentBarrier.image = mDepthImage.get();
		prePresentBarrier.oldLayout = vk::ImageLayout::eUndefined;
		prePresentBarrier.newLayout = vk::ImageLayout::eTransferDstOptimal;
		commandBuffer.pipelineBarrier(vk::PipelineStageFlagBits::eAllCommands, vk::PipelineStageFlagBits::eAllCommands, vk::DependencyFlags(), 0, nullptr, 0, nullptr, 1, &prePresentBarrier);

		vk::ImageSubresourceRange subResourceRange;
		subResourceRange.aspectMask = vk::ImageAspectFlagBits::eDepth;
		subResourceRange.baseMipLevel = 0;
		subResourceRange.levelCount = 1;
		subResourceRange.baseArrayLayer = 0;
		subResourceRange.layerCount = 1;
		commandBuffer.clearDepthStencilImage(mDepthImage.get(), vk::ImageLayout::eTransferDstOptimal, &mClearValues[1].depthStencil, 1, &subResourceRange);

		prePresentBarrier.image = mDepthImage.get();
		prePresentBarrier.oldLayout = vk::ImageLayout::eTransferDstOptimal;
		prePresentBarrier.newLayout = vk::ImageLayout::eDepthStencilAttachmentOptimal;
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

	auto& commandBuffer = mDrawCommandBuffers[mFrameIndex].get();

	Log(info) << "UVulkanRenderDevice::DrawComplexSurface" << std::endl;
	unguard;
}

void UVulkanRenderDevice::DrawGouraudPolygon(FSceneNode* Frame, FTextureInfo& Info, FTransTexture** Pts, int NumPts, DWORD PolyFlags, FSpanBuffer* Span)
{
	guard(UVulkanRenderDevice::DrawGouraudPolygon);

	auto& commandBuffer = mDrawCommandBuffers[mFrameIndex].get();

	BindTexture(0, 4, Info, PolyFlags);
	UpdateDescriptors(true);
	UpdatePipline(PolyFlags, vk::PrimitiveTopology::eTriangleFan, 3, false);

	Log(info) << "UVulkanRenderDevice::DrawGouraudPolygon" << std::endl;
	unguard;
}

void UVulkanRenderDevice::DrawTile(FSceneNode* Frame, FTextureInfo& Info, FLOAT X, FLOAT Y, FLOAT XL, FLOAT YL, FLOAT U, FLOAT V, FLOAT UL, FLOAT VL, class FSpanBuffer* Span, FLOAT Z, FPlane Color, FPlane Fog, DWORD PolyFlags)
{
	guard(UVulkanRenderDevice::DrawTile);

	// Precompute stuff.
	FLOAT rcpFrameFX = 1.0f / Frame->FX;
	mAspect = Frame->FY * rcpFrameFX;
	mRProjZ = appTan((double)Viewport->Actor->FovAngle * PI / 360.0);
	mRFX2 = 2.0f * mRProjZ * rcpFrameFX;
	mRFY2 = 2.0f * mRProjZ * rcpFrameFX;

	//Build Vertex Data
	FLOAT PX1 = X - Frame->FX2;
	FLOAT PX2 = PX1 + XL;
	FLOAT PY1 = Y - Frame->FY2;
	FLOAT PY2 = PY1 + YL;

	FLOAT RPX1 = mRFX2 * PX1;
	FLOAT RPX2 = mRFX2 * PX2;
	FLOAT RPY1 = mRFY2 * PY1;
	FLOAT RPY2 = mRFY2 * PY2;

	if (!Frame->Viewport->IsOrtho())
	{
		RPX1 *= Z;
		RPX2 *= Z;
		RPY1 *= Z;
		RPY2 *= Z;
	}

	const FGLVertexColor position[6] =
	{
		{ RPX1, RPY1 , Z, Color},
		{ RPX2, RPY1 , Z, Color},
		{ RPX2, RPY2 , Z, Color},
		{ RPX1, RPY1 , Z, Color},
		{ RPX2, RPY2 , Z, Color},
		{ RPX1, RPY2 , Z, Color}
	};

	FLOAT TexInfoUMult = 1.0f / (Info.UScale * (Info.USize << mUCopyBits));;
	FLOAT TexInfoVMult = 1.0f / (Info.VScale * (Info.VSize << mVCopyBits));

	FLOAT SU1 = (U)* TexInfoUMult;
	FLOAT SU2 = (U + UL) * TexInfoUMult;
	FLOAT SV1 = (V)* TexInfoVMult;
	FLOAT SV2 = (V + VL) * TexInfoVMult;

	const FGLTexCoord texcoord[6] =
	{
		{SU1,SV1},
		{SU2,SV1},
		{SU2,SV2},
		{SU1,SV1},
		{SU2,SV2},
		{SU1,SV2}
	};

	auto& commandBuffer = mDrawCommandBuffers[mFrameIndex].get();

	commandBuffer.endRenderPass();
	{
		commandBuffer.updateBuffer(mColor1Buffer.get(), 0, sizeof(position), &position);
		commandBuffer.updateBuffer(mTexcoord1Buffer.get(), 0, sizeof(texcoord), &texcoord);

		const auto uboBarrier = vk::MemoryBarrier()
			.setSrcAccessMask(vk::AccessFlagBits::eTransferWrite)
			.setDstAccessMask(vk::AccessFlagBits::eVertexAttributeRead);
		commandBuffer.pipelineBarrier(vk::PipelineStageFlagBits::eTransfer, vk::PipelineStageFlagBits::eVertexInput, vk::DependencyFlags(), 1, &uboBarrier, 0, nullptr, 0, nullptr);
	}
	commandBuffer.beginRenderPass(&mRenderPassBeginInfo, vk::SubpassContents::eInline);

	BindTexture(0, 4, Info, PolyFlags);
	UpdateDescriptors(true);
	UpdatePipline(PolyFlags, vk::PrimitiveTopology::eTriangleFan, 3, false);

	commandBuffer.draw(6, 1, 0, 0);

	Log(info) << "UVulkanRenderDevice::DrawTile" << std::endl;
	unguard;
}

void UVulkanRenderDevice::Draw2DLine(FSceneNode* Frame, FPlane Color, DWORD LineFlags, FVector P1, FVector P2)
{
	guard(UVulkanRenderDevice::Draw2DLine);

	auto& commandBuffer = mDrawCommandBuffers[mFrameIndex].get();

	UpdateDescriptors(false);
	UpdatePipline(0, vk::PrimitiveTopology::eTriangleFan, 2, false);

	Log(info) << "UVulkanRenderDevice::Draw2DLine" << std::endl;
	unguard;
}

void UVulkanRenderDevice::Draw2DPoint(FSceneNode* Frame, FPlane Color, DWORD LineFlags, FLOAT X1, FLOAT Y1, FLOAT X2, FLOAT Y2, FLOAT Z)
{
	guard(UVulkanRenderDevice::Draw2DPoint);

	auto& commandBuffer = mDrawCommandBuffers[mFrameIndex].get();

	UpdateDescriptors(false);
	UpdatePipline(0, vk::PrimitiveTopology::eTriangleFan, 2, false);

	Log(info) << "UVulkanRenderDevice::Draw2DPoint" << std::endl;
	unguard;
}

void UVulkanRenderDevice::ClearZ(FSceneNode* Frame)
{
	guard(UVulkanRenderDevice::ClearZ);

	//The depth is setup as clear in the render pass so just stop and start it. The Color is load/store so that should be safe.
	auto& commandBuffer = mDrawCommandBuffers[mFrameIndex].get();
	commandBuffer.endRenderPass();
	{
		vk::ImageMemoryBarrier prePresentBarrier;
		prePresentBarrier.srcAccessMask = vk::AccessFlags();
		prePresentBarrier.dstAccessMask = vk::AccessFlagBits::eMemoryRead;
		prePresentBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		prePresentBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		prePresentBarrier.subresourceRange = { VK_IMAGE_ASPECT_DEPTH_BIT , 0, 1, 0, 1 };

		prePresentBarrier.image = mDepthImage.get();
		prePresentBarrier.oldLayout = vk::ImageLayout::eUndefined;
		prePresentBarrier.newLayout = vk::ImageLayout::eTransferDstOptimal;
		commandBuffer.pipelineBarrier(vk::PipelineStageFlagBits::eAllCommands, vk::PipelineStageFlagBits::eAllCommands, vk::DependencyFlags(), 0, nullptr, 0, nullptr, 1, &prePresentBarrier);

		vk::ImageSubresourceRange subResourceRange;
		subResourceRange.aspectMask = vk::ImageAspectFlagBits::eDepth;
		subResourceRange.baseMipLevel = 0;
		subResourceRange.levelCount = 1;
		subResourceRange.baseArrayLayer = 0;
		subResourceRange.layerCount = 1;
		commandBuffer.clearDepthStencilImage(mDepthImage.get(), vk::ImageLayout::eTransferDstOptimal, &mClearValues[1].depthStencil, 1, &subResourceRange);

		prePresentBarrier.image = mDepthImage.get();
		prePresentBarrier.oldLayout = vk::ImageLayout::eTransferDstOptimal;
		prePresentBarrier.newLayout = vk::ImageLayout::eDepthStencilAttachmentOptimal;
		commandBuffer.pipelineBarrier(vk::PipelineStageFlagBits::eAllCommands, vk::PipelineStageFlagBits::eAllCommands, vk::DependencyFlags(), 0, nullptr, 0, nullptr, 1, &prePresentBarrier);
	}
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

void UVulkanRenderDevice::BeginRecordingUtilityCommands()
{
	mUtilityRecordingCount++;

	if (mUtilityRecordingCount > 1)
	{
		return;
	}

	mUtilityIndex = (mUtilityIndex++) % mUtilityCommandBuffers.size();

	mDevice->waitForFences(1, &mUtilityFences[mUtilityIndex].get(), VK_TRUE, UINT64_MAX);
	mDevice->resetFences(1, &mUtilityFences[mUtilityIndex].get());

	mCurrentUtilityCommandBuffer = mUtilityCommandBuffers[mUtilityIndex].get();

	vk::CommandBufferBeginInfo beginInfo(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);
	mCurrentUtilityCommandBuffer.begin(&beginInfo);
}

void UVulkanRenderDevice::StopRecordingUtilityCommands()
{
	mUtilityRecordingCount--;

	if (mUtilityRecordingCount > 0)
	{
		return;
	}

	mCurrentUtilityCommandBuffer.end();

	vk::PipelineStageFlags pipelineFlag[] = { vk::PipelineStageFlagBits::eColorAttachmentOutput }; //eAllCommands
	vk::SubmitInfo submitInfo;
	submitInfo.pWaitDstStageMask = pipelineFlag;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &mCurrentUtilityCommandBuffer;
	mQueue.submit(1, &submitInfo, mUtilityFences[mUtilityIndex].get());

	mUtilityRecordingCount = 0;
}

void UVulkanRenderDevice::SetImageLayout(CachedTexture& cachedTexture, vk::ImageLayout newLayout)
{
	BeginRecordingUtilityCommands();
	{
		const vk::PipelineStageFlags src_stages = ((cachedTexture.mImageLayout == vk::ImageLayout::eTransferSrcOptimal || cachedTexture.mImageLayout == vk::ImageLayout::eTransferDstOptimal) ? vk::PipelineStageFlagBits::eTransfer : vk::PipelineStageFlagBits::eTopOfPipe);
		const vk::PipelineStageFlags dest_stages = ((newLayout == vk::ImageLayout::eTransferSrcOptimal || newLayout == vk::ImageLayout::eTransferDstOptimal) ? vk::PipelineStageFlagBits::eTransfer : vk::PipelineStageFlagBits::eFragmentShader); //eColorAttachmentOutput

		auto DstAccessMask = [](vk::ImageLayout const& layout)
		{
			vk::AccessFlags flags;

			switch (layout) {
			case vk::ImageLayout::eTransferDstOptimal:
				// Make sure anything that was copying from this image has completed
				flags = vk::AccessFlagBits::eTransferWrite;
				break;
			case vk::ImageLayout::eColorAttachmentOptimal:
				flags = vk::AccessFlagBits::eColorAttachmentWrite;
				break;
			case vk::ImageLayout::eDepthStencilAttachmentOptimal:
				flags = vk::AccessFlagBits::eDepthStencilAttachmentWrite;
				break;
			case vk::ImageLayout::eShaderReadOnlyOptimal:
				// Make sure any Copy or CPU writes to image are flushed
				flags = vk::AccessFlagBits::eShaderRead | vk::AccessFlagBits::eInputAttachmentRead;
				break;
			case vk::ImageLayout::eTransferSrcOptimal:
				flags = vk::AccessFlagBits::eTransferRead;
				break;
			case vk::ImageLayout::ePresentSrcKHR:
				flags = vk::AccessFlagBits::eMemoryRead;
				break;
			default:
				break;
			}

			return flags;
		};

		auto const barrier = vk::ImageMemoryBarrier()
			.setSrcAccessMask(vk::AccessFlagBits())
			.setDstAccessMask(DstAccessMask(newLayout))
			.setOldLayout(cachedTexture.mImageLayout)
			.setNewLayout(newLayout)
			.setSrcQueueFamilyIndex(VK_QUEUE_FAMILY_IGNORED)
			.setDstQueueFamilyIndex(VK_QUEUE_FAMILY_IGNORED)
			.setImage(cachedTexture.mImage.get())
			.setSubresourceRange(vk::ImageSubresourceRange((vk::ImageAspectFlagBits::eColor), 0, 1, 0, 1));

		mCurrentUtilityCommandBuffer.pipelineBarrier(src_stages, dest_stages, vk::DependencyFlagBits(), 0, nullptr, 0, nullptr, 1, &barrier);

	}
	StopRecordingUtilityCommands();

	cachedTexture.mImageLayout = newLayout;
}

bool UVulkanRenderDevice::FindMemoryTypeFromProperties(uint32_t typeBits, vk::MemoryPropertyFlags requirements_mask, uint32_t* typeIndex)
{
	// Search memtypes to find first index with those properties
	for (uint32_t i = 0; i < VK_MAX_MEMORY_TYPES; i++)
	{
		if ((typeBits & 1) == 1)
		{
			// Type is available, does it match user properties?
			if ((mPhysicalDeviceMemoryProperties.memoryTypes[i].propertyFlags & requirements_mask) == requirements_mask)
			{
				*typeIndex = i;
				return true;
			}
		}
		typeBits >>= 1;
	}

	// No memory types matched, return failure
	return false;
}

void UVulkanRenderDevice::BindTexture(uint32_t index, uint32_t count, FTextureInfo& Info, DWORD PolyFlags)
{
	guard(UVulkanRenderDevice::BindTexture);

	std::shared_ptr<CachedTexture> cachedTexture;

	QWORD cacheId = Info.CacheID;
	bool isDirty = false;

	// Figure out scaling info for the texture.
	INT BaseMip = 0;
	INT UBits = Info.Mips[0]->UBits;
	INT VBits = Info.Mips[0]->VBits;
	if ((UBits - VBits) > MaxLogTextureSize)
	{
		mVCopyBits += (UBits - VBits) - MaxLogTextureSize;
		VBits = UBits - MaxLogTextureSize;
	}
	if ((VBits - UBits) > MaxLogTextureSize)
	{
		mUCopyBits += (VBits - UBits) - MaxLogTextureSize;
		UBits = VBits - MaxLogTextureSize;
	}
	if (UBits < MinLogTextureSize)
	{
		mUCopyBits += MinLogTextureSize - UBits;
		UBits += MinLogTextureSize - UBits;
	}
	if (VBits < MinLogTextureSize)
	{
		mVCopyBits += MinLogTextureSize - VBits;
		VBits += MinLogTextureSize - VBits;
	}
	if (UBits > MaxLogTextureSize)
	{
		BaseMip += UBits - MaxLogTextureSize;
		VBits -= UBits - MaxLogTextureSize;
		UBits = MaxLogTextureSize;
		if (VBits < 0) {
			mVCopyBits = -VBits;
			VBits = 0;
		}
	}
	if (VBits > MaxLogTextureSize)
	{
		BaseMip += VBits - MaxLogTextureSize;
		UBits -= VBits - MaxLogTextureSize;
		VBits = MaxLogTextureSize;
		if (UBits < 0) {
			mUCopyBits = -UBits;
			UBits = 0;
		}
	}

	//Look for texture or create if it if we haven't seen it yet.
	auto it = mCachedTextures.find(cacheId);
	if (it != mCachedTextures.end())
	{
		cachedTexture = it->second;
		isDirty = Info.bRealtimeChanged;
	}
	else
	{
		isDirty = true;

		cachedTexture = std::make_shared<CachedTexture>();
		mCachedTextures[cacheId] = cachedTexture;

		//Figure out Image information
		cachedTexture->mWidth = 1U << UBits;
		cachedTexture->mHeight = 1U << VBits;
		cachedTexture->mMipMapCount = std::max(Info.NumMips, 1);

		vk::ComponentMapping componentMapping;

		switch (Info.Format)
		{
		case TEXF_P8:
			cachedTexture->mFormat = vk::Format::eR8Unorm;
			componentMapping = vk::ComponentMapping(vk::ComponentSwizzle::eR, vk::ComponentSwizzle::eR, vk::ComponentSwizzle::eR, vk::ComponentSwizzle::eOne);
			break;
		case TEXF_RGBA7:
			cachedTexture->mFormat = vk::Format::eBc7UnormBlock; //Double check mapping.
			break;
		case TEXF_RGB16:
			cachedTexture->mFormat = vk::Format::eR16G16B16Unorm;
			break;
		case TEXF_DXT1:
			if (!(PolyFlags & PF_Masked))
			{
				cachedTexture->mFormat = vk::Format::eBc3UnormBlock;
			}
			else
			{
				cachedTexture->mFormat = vk::Format::eBc1RgbUnormBlock;
			}
			break;
		case TEXF_RGB8:
			cachedTexture->mFormat = vk::Format::eR8G8B8Unorm;
			break;
		case TEXF_RGBA8:
			cachedTexture->mFormat = vk::Format::eR8G8B8A8Unorm;
			break;
		default:
			cachedTexture->mFormat = vk::Format::eR8G8B8A8Unorm;
			break;
		}

		//Setup Image and View
		{
			const vk::ImageTiling tiling = vk::ImageTiling::eOptimal;
			const vk::ImageUsageFlags usage = vk::ImageUsageFlagBits::eSampled | vk::ImageUsageFlagBits::eTransferDst;
			const vk::MemoryPropertyFlags required_props = vk::MemoryPropertyFlagBits::eDeviceLocal;

			const vk::ImageCreateInfo imageCreateInfo = vk::ImageCreateInfo()
				.setImageType(vk::ImageType::e2D)
				.setFormat(cachedTexture->mFormat)
				.setExtent({ cachedTexture->mWidth, cachedTexture->mHeight, 1 })
				.setMipLevels(cachedTexture->mMipMapCount)
				.setArrayLayers(1)
				.setSamples(vk::SampleCountFlagBits::e1)
				.setTiling(tiling)
				.setUsage(usage)
				.setSharingMode(vk::SharingMode::eExclusive)
				.setQueueFamilyIndexCount(0)
				.setPQueueFamilyIndices(nullptr)
				.setInitialLayout(vk::ImageLayout::ePreinitialized);
			cachedTexture->mImage = mDevice->createImageUnique(imageCreateInfo);

			vk::MemoryRequirements memoryRequirements;
			mDevice->getImageMemoryRequirements(cachedTexture->mImage.get(), &memoryRequirements);

			vk::MemoryAllocateInfo imageMemoryAllocateInfo = vk::MemoryAllocateInfo()
				.setAllocationSize(memoryRequirements.size)
				.setMemoryTypeIndex(0);

			auto pass = FindMemoryTypeFromProperties(memoryRequirements.memoryTypeBits, required_props, &imageMemoryAllocateInfo.memoryTypeIndex);

			cachedTexture->mImageDeviceMemory = mDevice->allocateMemoryUnique(imageMemoryAllocateInfo);

			mDevice->bindImageMemory(cachedTexture->mImage.get(), cachedTexture->mImageDeviceMemory.get(), 0);

			auto const viewInfo = vk::ImageViewCreateInfo()
				.setImage(cachedTexture->mImage.get())
				.setViewType(vk::ImageViewType::e2D)
				.setFormat(cachedTexture->mFormat)
				.setSubresourceRange(vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor, 0, cachedTexture->mMipMapCount, 0, 1))
				.setComponents(componentMapping);
			cachedTexture->mImageView = mDevice->createImageViewUnique(viewInfo);
		}

		//Create staging buffer.
		{
			cachedTexture->mSize = cachedTexture->mWidth * cachedTexture->mHeight * SizeOf(cachedTexture->mFormat); //TODO: double check this.
			auto const bufferInfo = vk::BufferCreateInfo().setSize((vk::DeviceSize)cachedTexture->mSize).setUsage(vk::BufferUsageFlagBits::eTransferSrc);

			cachedTexture->mStagingBuffer = mDevice->createBufferUnique(bufferInfo);

			vk::MemoryRequirements mem_reqs;
			mDevice->getBufferMemoryRequirements(cachedTexture->mStagingBuffer.get(), &mem_reqs);

			auto mem_alloc = vk::MemoryAllocateInfo().setAllocationSize(mem_reqs.size).setMemoryTypeIndex(0);
			FindMemoryTypeFromProperties(mem_reqs.memoryTypeBits, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent, &mem_alloc.memoryTypeIndex);

			cachedTexture->mStagingBufferMemory = mDevice->allocateMemoryUnique(mem_alloc);

			mDevice->bindBufferMemory(cachedTexture->mStagingBuffer.get(), cachedTexture->mStagingBufferMemory.get(), 0);
		}

		//Create sampler
		{
			//TODO: Revisit later
			const auto addressMode = vk::SamplerAddressMode::eClampToEdge;
			const auto magFilter = vk::Filter::eLinear;
			const auto minFilter = vk::Filter::eLinear;
			const auto mipMode = vk::SamplerMipmapMode::eLinear;

			const vk::SamplerCreateInfo samplerCreateInfo = vk::SamplerCreateInfo()
				.setMagFilter(magFilter)
				.setMinFilter(minFilter)
				.setAddressModeU(addressMode)
				.setAddressModeV(addressMode)
				.setAddressModeW(addressMode)
				.setMipmapMode(mipMode)
				.setMipLodBias(LODBias)
				.setBorderColor(vk::BorderColor::eFloatOpaqueWhite)
				.setUnnormalizedCoordinates(VK_FALSE)
				.setCompareOp(vk::CompareOp::eNever)
				.setMinLod(0.0f)
				.setMaxLod(0.0f)
				.setAnisotropyEnable((vk::Bool32)MaxAnisotropy)
				.setMaxAnisotropy(MaxAnisotropy);

			cachedTexture->mSampler = mDevice->createSamplerUnique(samplerCreateInfo);
		}
	}

	if (isDirty)
	{
		if (SupportsLazyTextures)
		{
			Info.Load();
		}


		//Upload provided texture data.
		for (size_t i = 0; i < cachedTexture->mMipMapCount; i++)
		{
			const void* textureData = (void*)Info.Mips[BaseMip + i]->DataPtr;

			if (!textureData)
			{
				break;
			}

			void* bufferPointer = mDevice->mapMemory(cachedTexture->mStagingBufferMemory.get(), (vk::DeviceSize)0, VK_WHOLE_SIZE);

			if (bufferPointer)
			{
				memcpy(bufferPointer, textureData, cachedTexture->mSize);
				Info.bRealtimeChanged = 0;
			}

			mDevice->unmapMemory(cachedTexture->mStagingBufferMemory.get());

			BeginRecordingUtilityCommands();
			{
				this->SetImageLayout(*cachedTexture, vk::ImageLayout::eTransferDstOptimal);

				auto const subresource = vk::ImageSubresourceLayers()
					.setAspectMask(vk::ImageAspectFlagBits::eColor)
					.setMipLevel(i)
					.setBaseArrayLayer(0)
					.setLayerCount(1);

				auto const copy_region =
					vk::BufferImageCopy()
					.setBufferOffset(0)
					.setBufferRowLength(cachedTexture->mWidth)
					.setBufferImageHeight(cachedTexture->mHeight)
					.setImageSubresource(subresource)
					.setImageOffset({ 0, 0, 0 })
					.setImageExtent({ cachedTexture->mWidth, cachedTexture->mHeight, 1 });

				mCurrentUtilityCommandBuffer.copyBufferToImage(cachedTexture->mStagingBuffer.get(), cachedTexture->mImage.get(), vk::ImageLayout::eTransferDstOptimal, 1, &copy_region);

				SetImageLayout(*cachedTexture, vk::ImageLayout::eShaderReadOnlyOptimal);
			}
			StopRecordingUtilityCommands();
		}

		if (SupportsLazyTextures)
		{
			Info.Unload();
		}
	}

	for (size_t i = index; i < (index + count); i++)
	{
		mDescriptorImageInfo[i].imageLayout = vk::ImageLayout::eShaderReadOnlyOptimal;
		mDescriptorImageInfo[i].sampler = cachedTexture->mSampler.get();
		mDescriptorImageInfo[i].imageView = cachedTexture->mImageView.get();
	}

	unguard;
}

void UVulkanRenderDevice::UpdateDescriptors(bool write)
{
	guard(UVulkanRenderDevice::UpdateDescriptors);

	if (write || mLastDescriptorSet == vk::DescriptorSet())
	{
		//If we're out of descriptor sets to write into then allocate a new one.
		if (mDescriptorSetIndex >= (int32_t)mDescriptorSets[mFrameIndex].size())
		{
			vk::DescriptorSet descriptorSet;
			vk::DescriptorSetAllocateInfo descriptorSetInfo(mDescriptorPool.get(), 1, &mDescriptorLayout.get());
			vk::Result result = mDevice->allocateDescriptorSets(&descriptorSetInfo, &descriptorSet);
			if (result != vk::Result::eSuccess)
			{
				Log(fatal) << "UVulkanRenderDevice::UpdateDescriptors vkAllocateDescriptorSets failed with return code of " << result << std::endl;
				return;
			}
			mDescriptorSets[mFrameIndex].push_back(descriptorSet);
		}

		mLastDescriptorSet = mDescriptorSets[mFrameIndex][mDescriptorSetIndex];

		mWriteDescriptorSet[0].dstSet = mLastDescriptorSet; //Vertex
		mWriteDescriptorSet[1].dstSet = mLastDescriptorSet; //Fragment
		mWriteDescriptorSet[2].dstSet = mLastDescriptorSet; //Fragment
		mWriteDescriptorSet[2].pImageInfo = mDescriptorImageInfo; //Fragment

		mDevice->updateDescriptorSets(3, &mWriteDescriptorSet[0], 0, nullptr);
	}

	auto& commandBuffer = mDrawCommandBuffers[mFrameIndex].get();

	commandBuffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, mPipelineLayout.get(), 0, 1, &mLastDescriptorSet, 0, nullptr);

	mDescriptorSetIndex++;

	unguard;
}

void UVulkanRenderDevice::UpdatePipline(DWORD PolyFlags, vk::PrimitiveTopology topology, uint32_t vertexElementCount, bool secondColor)
{
	guard(UVulkanRenderDevice::UpdateDescriptors);

	auto const vertexInputInfo = vk::PipelineVertexInputStateCreateInfo()
		.setPVertexAttributeDescriptions(secondColor ? gTwoColorVertexInputAttributeDescription : gStandardVertexInputAttributeDescription)
		.setVertexAttributeDescriptionCount(vertexElementCount)
		.setPVertexBindingDescriptions(gStandardVertexInputBindingDescription)
		.setVertexBindingDescriptionCount(6);

	auto const inputAssemblyInfo = vk::PipelineInputAssemblyStateCreateInfo().setTopology(topology);
	auto const viewportInfo = vk::PipelineViewportStateCreateInfo().setViewportCount(1).setScissorCount(1);
	auto const rasterizationInfo = vk::PipelineRasterizationStateCreateInfo()
		.setDepthClampEnable(VK_FALSE)
		.setRasterizerDiscardEnable(VK_FALSE)
		.setPolygonMode(vk::PolygonMode::eFill)
		.setCullMode(vk::CullModeFlagBits::eNone)
		.setFrontFace(vk::FrontFace::eClockwise) //TODO: double check winding order.
		.setDepthBiasEnable(VK_TRUE)
		.setLineWidth(1.0f);

	auto const multisampleInfo = vk::PipelineMultisampleStateCreateInfo();

	auto const frontStencilOp = vk::StencilOpState()
		//.setReference()
		//.setCompareMask()
		//.setWriteMask()
		//.setFailOp()
		//.setPassOp()
		//.setCompareOp()
		;
	auto const backStencilOp = vk::StencilOpState()
		//.setReference()
		//.setCompareMask()
		//.setWriteMask()
		//.setFailOp()
		//.setPassOp()
		//.setCompareOp()
		;
	auto const depthStencilInfo = vk::PipelineDepthStencilStateCreateInfo()
		.setDepthTestEnable(VK_TRUE)
		.setDepthWriteEnable(VK_TRUE)
		.setDepthCompareOp(vk::CompareOp::eLessOrEqual)
		.setDepthBoundsTestEnable(VK_FALSE)
		.setStencilTestEnable(VK_FALSE)
		.setFront(frontStencilOp)
		.setBack(backStencilOp);

	vk::PipelineColorBlendAttachmentState const colorBlendAttachments[1] =
	{
		vk::PipelineColorBlendAttachmentState()
		.setColorWriteMask(((PolyFlags & PF_Invisible) == 0) ? vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA : vk::ColorComponentFlags())
		.setBlendEnable(VK_TRUE)
		.setColorBlendOp(vk::BlendOp::eAdd)
		.setSrcColorBlendFactor(vk::BlendFactor::eOne)
		.setDstColorBlendFactor(vk::BlendFactor::eZero)
		.setAlphaBlendOp(vk::BlendOp::eAdd)
		.setSrcAlphaBlendFactor(vk::BlendFactor::eOne)
		.setDstAlphaBlendFactor(vk::BlendFactor::eZero)
	};
	auto const colorBlendInfo = vk::PipelineColorBlendStateCreateInfo().setAttachmentCount(1).setPAttachments(colorBlendAttachments);

	//TODO: Add additional shaders for higher texture count and second color.
	vk::PipelineShaderStageCreateInfo const shaderStageInfo[2] =
	{
		vk::PipelineShaderStageCreateInfo().setStage(vk::ShaderStageFlagBits::eVertex).setModule(mDefaultRenderingStateVertex.get()).setPName("main"),
		vk::PipelineShaderStageCreateInfo().setStage(vk::ShaderStageFlagBits::eFragment).setModule(mDefaultRenderingStateFragment.get()).setPName("main")
	};

	vk::DynamicState const dynamicStates[2] = { vk::DynamicState::eViewport, vk::DynamicState::eScissor }; //vk::DynamicState::eDepthBias
	auto const dynamicStateInfo = vk::PipelineDynamicStateCreateInfo().setPDynamicStates(dynamicStates).setDynamicStateCount(2);
	auto const pipeline = vk::GraphicsPipelineCreateInfo()
		.setStageCount(2) //Vertex & Fragment
		.setPStages(shaderStageInfo)
		.setPVertexInputState(&vertexInputInfo)
		.setPInputAssemblyState(&inputAssemblyInfo)
		.setPViewportState(&viewportInfo)
		.setPRasterizationState(&rasterizationInfo)
		.setPMultisampleState(&multisampleInfo)
		.setPDepthStencilState(&depthStencilInfo)
		.setPColorBlendState(&colorBlendInfo)
		.setPDynamicState(&dynamicStateInfo)
		.setLayout(mPipelineLayout.get())
		.setRenderPass(mRenderPass.get());

	mPipelines[mFrameIndex].push_back(mDevice->createGraphicsPipelineUnique(mPipelineCache.get(), pipeline));

	auto& commandBuffer = mDrawCommandBuffers[mFrameIndex].get();
	commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, mPipelines[mFrameIndex][mPipelines[mFrameIndex].size() - 1].get());

	unguard;
}

void UVulkanRenderDevice::AddFloatConfigParam(const TCHAR* pName, FLOAT& param, ECppProperty EC_CppProperty, INT InOffset, FLOAT defaultValue)
{
	param = defaultValue;
	new(GetClass(), pName, RF_Public)UFloatProperty(EC_CppProperty, InOffset, TEXT("Options"), CPF_Config);
}

void UVulkanRenderDevice::AddBoolConfigParam(DWORD BitMaskOffset, const TCHAR* pName, UBOOL& param, ECppProperty EC_CppProperty, INT InOffset, UBOOL defaultValue)
{
	param = (((defaultValue) != 0) ? 1 : 0) << BitMaskOffset; //Doesn't exactly work like a UBOOL "// Boolean 0 (false) or 1 (true)."
	new(GetClass(), pName, RF_Public)UBoolProperty(EC_CppProperty, InOffset, TEXT("Options"), CPF_Config);
}

void UVulkanRenderDevice::AddIntConfigParam(const TCHAR* pName, INT& param, ECppProperty EC_CppProperty, INT InOffset, INT defaultValue)
{
	param = defaultValue;
	new(GetClass(), pName, RF_Public)UIntProperty(EC_CppProperty, InOffset, TEXT("Options"), CPF_Config);
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