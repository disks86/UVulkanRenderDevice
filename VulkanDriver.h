#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX

#ifndef MAX_DESCRIPTOR
#define MAX_DESCRIPTOR 2048u
#endif // !MAX_DESCRIPTOR

#ifndef MAX_BUFFERUPDATE
#define MAX_BUFFERUPDATE 65536u
#endif // !MAX_BUFFERUPDATE

#ifndef MAX_BUFFERUPDATE
#define CT_MIN_FILTER_POINT					0x00
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
#ifndef VK_USE_PLATFORM_WIN32_KHR
#define VK_USE_PLATFORM_WIN32_KHR
#endif //VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>
#include <vulkan/vulkan.hpp>
#include <vulkan/vk_sdk_platform.h>
#include <glm/glm.hpp>
//#define UTGLR_NO_APP_MALLOC
#include <stdlib.h>
#include "Engine.h"
#include "UnRender.h"
