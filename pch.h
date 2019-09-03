// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX

#ifndef MAX_DESCRIPTOR
#define MAX_DESCRIPTOR 2048u
#endif // !MAX_DESCRIPTOR

#ifndef MAX_BUFFERUPDATE
#define MAX_BUFFERUPDATE 65536u
#endif // !MAX_BUFFERUPDATE

#ifndef CT_MIN_FILTER_LINEAR
#define CT_MIN_FILTER_LINEAR				0x01
#endif // !CT_MIN_FILTER_LINEAR

#ifndef CT_MIN_FILTER_ANISOTROPIC
#define CT_MIN_FILTER_ANISOTROPIC			0x02
#endif // !CT_MIN_FILTER_ANISOTROPIC

#ifndef CT_MIN_FILTER_MASK
#define CT_MIN_FILTER_MASK					0x03
#endif // !CT_MIN_FILTER_MASK

#ifndef CT_MIP_FILTER_NONE
#define CT_MIP_FILTER_NONE					0x00
#endif // !CT_MIP_FILTER_NONE

#ifndef CT_MIP_FILTER_POINT
#define CT_MIP_FILTER_POINT					0x04
#endif // !CT_MIP_FILTER_POINT

#ifndef CT_MIP_FILTER_LINEAR
#define CT_MIP_FILTER_LINEAR				0x08
#endif // !CT_MIP_FILTER_LINEAR

#ifndef CT_MIP_FILTER_MASK
#define CT_MIP_FILTER_MASK					0x0C
#endif // !CT_MIP_FILTER_MASK

#ifndef CT_MAG_FILTER_LINEAR_NOT_POINT_BIT
#define CT_MAG_FILTER_LINEAR_NOT_POINT_BIT	0x10
#endif // !CT_MAG_FILTER_LINEAR_NOT_POINT_BIT

#ifndef CT_HAS_MIPMAPS_BIT
#define CT_HAS_MIPMAPS_BIT					0x20
#endif // !CT_HAS_MIPMAPS_BIT

#ifndef CT_ADDRESS_CLAMP_NOT_WRAP_BIT
#define CT_ADDRESS_CLAMP_NOT_WRAP_BIT		0x40
#endif // !CT_ADDRESS_CLAMP_NOT_WRAP_BIT

//#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include "atlstr.h"
#include <vector>
#include <map>
#include <string>
#include <locale>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <memory>
#include "framework.h"
#ifndef VK_USE_PLATFORM_WIN32_KHR
#define VK_USE_PLATFORM_WIN32_KHR
#endif //VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>
#include <vulkan/vulkan.hpp>
#include <vulkan/vk_sdk_platform.h>
#include <glm/glm.hpp>
//#define UTGLR_NO_APP_MALLOC
#include <stdlib.h>
#include <Engine.h>
#include <UnRender.h>
#endif //PCH_H
