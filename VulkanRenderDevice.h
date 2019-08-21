#pragma once
#include "VulkanDriver.h"

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

