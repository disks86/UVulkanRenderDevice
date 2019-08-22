#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX

#ifndef MAX_DESCRIPTOR
#define MAX_DESCRIPTOR 2048u
#endif // !MAX_DESCRIPTOR

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
#include <vulkan/vulkan.hpp>
#include <vulkan/vk_sdk_platform.h>
//#define UTGLR_NO_APP_MALLOC
#include <stdlib.h>
#include "Engine.h"
#include "UnRender.h"
