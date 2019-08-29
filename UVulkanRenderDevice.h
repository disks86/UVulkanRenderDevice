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

struct VertexGlobalConstants
{
	glm::mat4 ProjectionMatrix;
	glm::vec2 XAxis;
	glm::vec2 UDot;
	glm::vec2 YAxis;
	glm::vec2 VDot;
	float Upan1;
	float VPan1;
	float UMult1;
	float VMult1;
	float Upan2;
	float VPan2;
	float UMult2;
	float VMult2;
	float Upan3;
	float VPan3;
	float UMult3;
	float VMult3;
	float Upan4;
	float VPan4;
	float UMult4;
	float VMult4;
};

struct FragmentGlobalConstants
{
	float AlphaTestLevel;
	float Unused1;
	float Unused2;
	float LightmapBlendScaleFactor;
};

struct CachedTexture
{
	vk::UniqueImage mImage;
	vk::UniqueDeviceMemory mImageDeviceMemory;
	vk::UniqueImageView mImageView;

	uint32_t mWidth = 0;
	uint32_t mHeight = 0;
	uint32_t mMipMapCount = 0;
};

class UVulkanRenderDevice
	: public URenderDevice
{
public:

	UVulkanRenderDevice();

	DECLARE_CLASS(UVulkanRenderDevice, URenderDevice, CLASS_Config, VulkanDriver)

	void StaticConstructor();

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
	size_t mPhysicalDeviceIndex = 0;
	vk::PhysicalDeviceProperties mPhysicalDeviceProperties;
	vk::PhysicalDeviceMemoryProperties mPhysicalDeviceMemoryProperties;
	std::vector<vk::QueueFamilyProperties> mQueueFamilyProperties;
	size_t mGraphicsQueueFamilyIndex = 0;
	size_t mPresentQueueFamilyIndex = 0;
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
	vk::UniqueDescriptorSetLayout mDescriptorLayout;
	vk::UniquePipelineLayout mPipelineLayout;
	vk::DescriptorBufferInfo mDescriptorBufferInfo[3];
	vk::WriteDescriptorSet mWriteDescriptorSet[3];
	vk::DescriptorImageInfo mDescriptorImageInfo[4];

	//Vulkan Surface & Swap Chain
	vk::UniqueSurfaceKHR mSurface;
	std::vector<vk::SurfaceFormatKHR> mFormats;
	vk::Format mFormat = vk::Format::eUndefined;
	vk::ColorSpaceKHR mColorSpace = vk::ColorSpaceKHR::eSrgbNonlinear;
	vk::SurfaceCapabilitiesKHR mSurfaceCapabilities;
	VkExtent2D mSwapchainExtent = {};
	vk::PresentModeKHR mSwapchainPresentMode = vk::PresentModeKHR::eFifo;
	vk::UniqueSwapchainKHR mSwapChain;
	std::vector<vk::Image> mSwapChainImages;
	std::vector<vk::UniqueImageView> mImageViews;
	vk::SwapchainCreateInfoKHR mSwapChainCreateInfo;

	//Vulkan Depth Buffer
	vk::Format mDepthFormat = vk::Format::eUndefined;
	vk::UniqueImage mDepthImage;
	vk::UniqueDeviceMemory mDepthMemory;
	vk::UniqueImageView mDepthView;

	//Vulkan RenderPass, Framebuffer Scissor, and Viewport
	vk::UniqueRenderPass mRenderPass;
	std::vector <vk::UniqueFramebuffer> mFrameBuffers;
	vk::Rect2D mScissor = {};
	vk::Viewport mViewport = {};
	uint32_t mImageIndex = 0;
	vk::ClearValue mClearValues[2] = {};
	vk::RenderPassBeginInfo mRenderPassBeginInfo = {};

	//Vulkan Buffers
	vk::UniqueBuffer mColor1Buffer;
	vk::UniqueDeviceMemory mColor1BufferMemory;
	vk::UniqueBuffer mColor2Buffer;
	vk::UniqueDeviceMemory mColor2BufferMemory;
	vk::UniqueBuffer mTexcoord1Buffer;
	vk::UniqueDeviceMemory mTexcoord1BufferMemory;
	vk::UniqueBuffer mTexcoord2Buffer;
	vk::UniqueDeviceMemory mTexcoord2BufferMemory;
	vk::UniqueBuffer mTexcoord3Buffer;
	vk::UniqueDeviceMemory mTexcoord3BufferMemory;
	vk::UniqueBuffer mTexcoord4Buffer;
	vk::UniqueDeviceMemory mTexcoord4BufferMemory;
	vk::UniqueBuffer mVertexConstantBuffer;
	vk::UniqueDeviceMemory mVertexConstantBufferMemory;
	vk::UniqueBuffer mFragmentConstantBuffer;
	vk::UniqueDeviceMemory mFragmentConstantBufferMemory;

	VertexGlobalConstants mVertexGlobalConstants = {};
	FragmentGlobalConstants mFragmentGlobalConstants = {};

	std::map<QWORD, std::shared_ptr<CachedTexture> > mCachedTextures;

	//Vulkan Shaders
	template < typename T, int32_t arraySize>
	vk::UniqueShaderModule LoadShaderFromConst(const T(&data)[arraySize])
	{
		const vk::ShaderModuleCreateInfo moduleCreateInfo(vk::ShaderModuleCreateFlags(), arraySize * sizeof(T), (const uint32_t*)data);
		return mDevice->createShaderModuleUnique(moduleCreateInfo);
	}

	vk::UniqueShaderModule mDefaultRenderingStateVertex;
	vk::UniqueShaderModule mDefaultRenderingStateFragment;

	bool FindMemoryTypeFromProperties(uint32_t typeBits, vk::MemoryPropertyFlags requirements_mask, uint32_t* typeIndex);
	void BindTexture(uint32_t index, FTextureInfo& Info, DWORD PolyFlags);

	//Misc
	void LoadConfiguration(std::string filename);

	HWND mHWND = 0;
	HDC mHDC = 0;
	HINSTANCE mHINSTANCE = 0;
	INT mNewX = 0;
	INT mNewY = 0;
	INT mNewColorBytes = 0;
	UBOOL mFullscreen = 0;
};

