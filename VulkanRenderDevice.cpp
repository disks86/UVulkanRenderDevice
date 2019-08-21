#include "pch.h"
#include "VulkanRenderDevice.h"

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
