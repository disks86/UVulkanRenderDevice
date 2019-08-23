#pragma once
#include "VulkanDriver.h"
#include "LogManager.h"

VKAPI_ATTR VkBool32 VKAPI_CALL DebugReportCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* layerPrefix, const char* message, void* userData);

static PFN_vkCreateDebugReportCallbackEXT pfn_vkCreateDebugReportCallbackEXT;
VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugReportCallbackEXT(
	VkInstance                                  instance,
	const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
	const VkAllocationCallbacks* pAllocator,
	VkDebugReportCallbackEXT* pCallback);

static PFN_vkDestroyDebugReportCallbackEXT pfn_vkDestroyDebugReportCallbackEXT;
VKAPI_ATTR void VKAPI_CALL vkDestroyDebugReportCallbackEXT(
	VkInstance                                  instance,
	VkDebugReportCallbackEXT                    callback,
	const VkAllocationCallbacks* pAllocator);

static PFN_vkDebugReportMessageEXT pfn_vkDebugReportMessageEXT;
VKAPI_ATTR void VKAPI_CALL vkDebugReportMessageEXT(
	VkInstance                                  instance,
	VkDebugReportFlagsEXT                       flags,
	VkDebugReportObjectTypeEXT                  objectType,
	uint64_t                                    object,
	size_t                                      location,
	int32_t                                     messageCode,
	const char* pLayerPrefix,
	const char* pMessage);

static inline void LTrim(std::string& s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch)
		{
			std::locale loc;
			return !std::isspace(ch, loc);
		}));
}

static inline void RTrim(std::string& s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch)
		{
			std::locale loc;
			return !std::isspace(ch, loc);
		}).base(), s.end());
}

static inline void Trim(std::string& s)
{
	LTrim(s);
	RTrim(s);
}

class VulkanRenderDevice
	: public URenderDevice
{
public:
	//RenderDevice Stuff
	DECLARE_CLASS(VulkanRenderDevice, URenderDevice, CLASS_Config, VulkanDriver)
	
	UBOOL Init(UViewport*, INT, INT, INT, UBOOL);
	UBOOL SetRes(INT, INT, INT, UBOOL);
	void Exit(void);
	void Flush(UBOOL);
	void Lock(FPlane, FPlane, FPlane, DWORD, BYTE*, INT*);
	void Unlock(UBOOL);
	void DrawComplexSurface(FSceneNode*, FSurfaceInfo&, FSurfaceFacet&);
	void DrawGouraudPolygon(FSceneNode*, FTextureInfo&, FTransTexture**, int, DWORD, FSpanBuffer*);
	void DrawTile(FSceneNode*, FTextureInfo&, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FSpanBuffer*, FLOAT, FPlane, FPlane, DWORD);
	void Draw2DLine(FSceneNode*, FPlane, DWORD, FVector, FVector);
	void Draw2DPoint(FSceneNode*, FPlane, DWORD, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT);
	void ClearZ(FSceneNode*);
	void PushHit(const BYTE*, INT);
	void PopHit(INT, UBOOL);
	void GetStats(TCHAR*);
	void ReadPixels(FColor*);

	//Vulkan
	vk::UniqueInstance mInstance;
	vk::UniqueDebugReportCallbackEXT mCallback;
	std::vector<vk::PhysicalDevice> mPhysicalDevices;
	size_t mPhysicalDeviceIndex;
	vk::PhysicalDeviceProperties mPhysicalDeviceProperties;
	vk::PhysicalDeviceMemoryProperties mPhysicalDeviceMemoryProperties;
	std::vector<vk::QueueFamilyProperties> mQueueFamilyProperties;
	size_t mGraphicsQueueFamilyIndex;
	size_t mPresentQueueFamilyIndex;
	vk::UniqueDevice mDevice;
	vk::UniqueCommandPool mCommandPool;
	vk::Queue mQueue;
	vk::UniqueDescriptorPool mDescriptorPool;
	vk::UniquePipelineCache mPipelineCache;
	std::vector<vk::UniqueSemaphore> mImageAvailableSemaphores;
	std::vector<vk::UniqueSemaphore> mRenderFinishedSemaphores;
	std::vector<vk::UniqueCommandBuffer> mDrawCommandBuffers;
	std::vector<vk::UniqueFence> mDrawFences;
	uint32_t mFrameIndex = 0;
	std::vector<vk::UniqueCommandBuffer> mUtilityCommandBuffers;
	std::vector<vk::UniqueFence> mUtilityFences;
	uint32_t mUtilityIndex = 0;

	//Vulkan Surface & Swap Chain
	vk::UniqueSurfaceKHR mSurface;
	std::vector<vk::SurfaceFormatKHR> mFormats;
	vk::Format mFormat;
	vk::SurfaceCapabilitiesKHR mSurfaceCapabilities;
	VkExtent2D mSwapchainExtent;
	vk::PresentModeKHR mSwapchainPresentMode;
	vk::UniqueSwapchainKHR mSwapChain;
	std::vector<vk::Image> mSwapChainImages; 
	std::vector<vk::UniqueImageView> mImageViews;

	//Vulkan Depth Buffer
	vk::Format mDepthFormat;
	vk::UniqueImage mDepthImage;
	vk::UniqueDeviceMemory mDepthMemory;
	vk::UniqueImageView mDepthView;

	//Vulkan RenderPass, Framebuffer Scissor, and Viewport
	vk::UniqueRenderPass mRenderPass;
	std::vector <vk::UniqueFramebuffer> mFrameBuffers;
	vk::Rect2D mScissor;
	vk::Viewport mViewport;

	//Misc
	std::map<std::string, std::string> mConfiguration;
	void LoadConfiguration(std::string filename);

	HWND mHWND;
	HDC mHDC;

	INT mNewX;
	INT mNewY;
	INT mNewColorBytes;
	UBOOL mFullscreen;
};

