#pragma once
#include "VulkanDriver.h"

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

class VulkanRenderDevice
	: public URenderDevice
{
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
};

