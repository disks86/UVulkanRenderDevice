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

#ifndef VEC2_SIZE
#define VEC2_SIZE (sizeof(float)*2)
#endif // !VEC2_SIZE

#ifndef VEC3_SIZE
#define VEC3_SIZE (sizeof(float)*3)
#endif // !VEC3_SIZE

#ifndef VEC4_SIZE
#define VEC4_SIZE (sizeof(float)*4)
#endif // !VEC4_SIZE

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
