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
