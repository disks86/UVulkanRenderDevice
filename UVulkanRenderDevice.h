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

inline uint32_t SizeOf(vk::Format format) noexcept
{
	switch (format)
	{
	case vk::Format::eUndefined: //VK_FORMAT_UNDEFINED,
		return 0;
	case vk::Format::eR4G4UnormPack8: //VK_FORMAT_R4G4_UNORM_PACK8,
		return 1;
	case vk::Format::eR4G4B4A4UnormPack16: //VK_FORMAT_R4G4B4A4_UNORM_PACK16,
		return 2;
	case vk::Format::eB4G4R4A4UnormPack16: //VK_FORMAT_B4G4R4A4_UNORM_PACK16,
		return 2;
	case vk::Format::eR5G6B5UnormPack16: //VK_FORMAT_R5G6B5_UNORM_PACK16,
		return 2;
	case vk::Format::eB5G6R5UnormPack16: //VK_FORMAT_B5G6R5_UNORM_PACK16,
		return 2;
	case vk::Format::eR5G5B5A1UnormPack16: //VK_FORMAT_R5G5B5A1_UNORM_PACK16,
		return 2;
	case vk::Format::eB5G5R5A1UnormPack16: //VK_FORMAT_B5G5R5A1_UNORM_PACK16,
		return 2;
	case vk::Format::eA1R5G5B5UnormPack16: //VK_FORMAT_A1R5G5B5_UNORM_PACK16,
		return 2;
	case vk::Format::eR8Unorm: //VK_FORMAT_R8_UNORM,
		return 1;
	case vk::Format::eR8Snorm: //VK_FORMAT_R8_SNORM,
		return 1;
	case vk::Format::eR8Uscaled: //VK_FORMAT_R8_USCALED,
		return 1;
	case vk::Format::eR8Sscaled: //VK_FORMAT_R8_SSCALED,
		return 1;
	case vk::Format::eR8Uint: //VK_FORMAT_R8_UINT,
		return 1;
	case vk::Format::eR8Sint: //VK_FORMAT_R8_SINT,
		return 1;
	case vk::Format::eR8Srgb: //VK_FORMAT_R8_SRGB,
		return 1;
	case vk::Format::eR8G8Unorm: //VK_FORMAT_R8G8_UNORM,
		return 2;
	case vk::Format::eR8G8Snorm: //VK_FORMAT_R8G8_SNORM,
		return 2;
	case vk::Format::eR8G8Uscaled: //VK_FORMAT_R8G8_USCALED,
		return 2;
	case vk::Format::eR8G8Sscaled: //VK_FORMAT_R8G8_SSCALED,
		return 2;
	case vk::Format::eR8G8Uint: //VK_FORMAT_R8G8_UINT,
		return 2;
	case vk::Format::eR8G8Sint: //VK_FORMAT_R8G8_SINT,
		return 2;
	case vk::Format::eR8G8Srgb: //VK_FORMAT_R8G8_SRGB,
		return 2;
	case vk::Format::eR8G8B8Unorm: //VK_FORMAT_R8G8B8_UNORM,
		return 3;
	case vk::Format::eR8G8B8Snorm: //VK_FORMAT_R8G8B8_SNORM,
		return 3;
	case vk::Format::eR8G8B8Uscaled: //VK_FORMAT_R8G8B8_USCALED,
		return 3;
	case vk::Format::eR8G8B8Sscaled: //VK_FORMAT_R8G8B8_SSCALED,
		return 3;
	case vk::Format::eR8G8B8Uint: //VK_FORMAT_R8G8B8_UINT,
		return 3;
	case vk::Format::eR8G8B8Sint: //VK_FORMAT_R8G8B8_SINT,
		return 3;
	case vk::Format::eR8G8B8Srgb: //VK_FORMAT_R8G8B8_SRGB,
		return 3;
	case vk::Format::eB8G8R8Unorm: //VK_FORMAT_B8G8R8_UNORM,
		return 3;
	case vk::Format::eB8G8R8Snorm: //VK_FORMAT_B8G8R8_SNORM,
		return 3;
	case vk::Format::eB8G8R8Uscaled: //VK_FORMAT_B8G8R8_USCALED,
		return 3;
	case vk::Format::eB8G8R8Sscaled: //VK_FORMAT_B8G8R8_SSCALED,
		return 3;
	case vk::Format::eB8G8R8Uint: //VK_FORMAT_B8G8R8_UINT,
		return 3;
	case vk::Format::eB8G8R8Sint: //VK_FORMAT_B8G8R8_SINT,
		return 3;
	case vk::Format::eB8G8R8Srgb: //VK_FORMAT_B8G8R8_SRGB,
		return 3;
	case vk::Format::eR8G8B8A8Unorm: //VK_FORMAT_R8G8B8A8_UNORM,
		return 4;
	case vk::Format::eR8G8B8A8Snorm: //VK_FORMAT_R8G8B8A8_SNORM,
		return 4;
	case vk::Format::eR8G8B8A8Uscaled: //VK_FORMAT_R8G8B8A8_USCALED,
		return 4;
	case vk::Format::eR8G8B8A8Sscaled: //VK_FORMAT_R8G8B8A8_SSCALED,
		return 4;
	case vk::Format::eR8G8B8A8Uint: //VK_FORMAT_R8G8B8A8_UINT,
		return 4;
	case vk::Format::eR8G8B8A8Sint: //VK_FORMAT_R8G8B8A8_SINT,
		return 4;
	case vk::Format::eR8G8B8A8Srgb: //VK_FORMAT_R8G8B8A8_SRGB,
		return 4;
	case vk::Format::eB8G8R8A8Unorm: //VK_FORMAT_B8G8R8A8_UNORM,
		return 4;
	case vk::Format::eB8G8R8A8Snorm: //VK_FORMAT_B8G8R8A8_SNORM,
		return 4;
	case vk::Format::eB8G8R8A8Uscaled: //VK_FORMAT_B8G8R8A8_USCALED,
		return 4;
	case vk::Format::eB8G8R8A8Sscaled: //VK_FORMAT_B8G8R8A8_SSCALED,
		return 4;
	case vk::Format::eB8G8R8A8Uint: //VK_FORMAT_B8G8R8A8_UINT,
		return 4;
	case vk::Format::eB8G8R8A8Sint: //VK_FORMAT_B8G8R8A8_SINT,
		return 4;
	case vk::Format::eB8G8R8A8Srgb: //VK_FORMAT_B8G8R8A8_SRGB,
		return 4;
	case vk::Format::eA8B8G8R8UnormPack32: //VK_FORMAT_A8B8G8R8_UNORM_PACK32,
		return 4;
	case vk::Format::eA8B8G8R8SnormPack32: //VK_FORMAT_A8B8G8R8_SNORM_PACK32,
		return 4;
	case vk::Format::eA8B8G8R8UscaledPack32: //VK_FORMAT_A8B8G8R8_USCALED_PACK32,
		return 4;
	case vk::Format::eA8B8G8R8SscaledPack32: //VK_FORMAT_A8B8G8R8_SSCALED_PACK32,
		return 4;
	case vk::Format::eA8B8G8R8UintPack32: //VK_FORMAT_A8B8G8R8_UINT_PACK32,
		return 4;
	case vk::Format::eA8B8G8R8SintPack32: //VK_FORMAT_A8B8G8R8_SINT_PACK32,
		return 4;
	case vk::Format::eA8B8G8R8SrgbPack32: //VK_FORMAT_A8B8G8R8_SRGB_PACK32,
		return 4;
	case vk::Format::eA2R10G10B10UnormPack32: //VK_FORMAT_A2R10G10B10_UNORM_PACK32,
		return 4;
	case vk::Format::eA2R10G10B10SnormPack32: //VK_FORMAT_A2R10G10B10_SNORM_PACK32,
		return 4;
	case vk::Format::eA2R10G10B10UscaledPack32: //VK_FORMAT_A2R10G10B10_USCALED_PACK32,
		return 4;
	case vk::Format::eA2R10G10B10SscaledPack32: //VK_FORMAT_A2R10G10B10_SSCALED_PACK32,
		return 4;
	case vk::Format::eA2R10G10B10UintPack32: //VK_FORMAT_A2R10G10B10_UINT_PACK32,
		return 4;
	case vk::Format::eA2R10G10B10SintPack32: //VK_FORMAT_A2R10G10B10_SINT_PACK32,
		return 4;
	case vk::Format::eA2B10G10R10UnormPack32: //VK_FORMAT_A2B10G10R10_UNORM_PACK32,
		return 4;
	case vk::Format::eA2B10G10R10SnormPack32: //VK_FORMAT_A2B10G10R10_SNORM_PACK32,
		return 4;
	case vk::Format::eA2B10G10R10UscaledPack32: //VK_FORMAT_A2B10G10R10_USCALED_PACK32,
		return 4;
	case vk::Format::eA2B10G10R10SscaledPack32: //VK_FORMAT_A2B10G10R10_SSCALED_PACK32,
		return 4;
	case vk::Format::eA2B10G10R10UintPack32: //VK_FORMAT_A2B10G10R10_UINT_PACK32,
		return 4;
	case vk::Format::eA2B10G10R10SintPack32: //VK_FORMAT_A2B10G10R10_SINT_PACK32,
		return 4;
	case vk::Format::eR16Unorm: //VK_FORMAT_R16_UNORM,
		return 2;
	case vk::Format::eR16Snorm: //VK_FORMAT_R16_SNORM,
		return 2;
	case vk::Format::eR16Uscaled: //VK_FORMAT_R16_USCALED,
		return 2;
	case vk::Format::eR16Sscaled: //VK_FORMAT_R16_SSCALED,
		return 2;
	case vk::Format::eR16Uint: //VK_FORMAT_R16_UINT,
		return 2;
	case vk::Format::eR16Sint: //VK_FORMAT_R16_SINT,
		return 2;
	case vk::Format::eR16Sfloat: //VK_FORMAT_R16_SFLOAT,
		return 2;
	case vk::Format::eR16G16Unorm: //VK_FORMAT_R16G16_UNORM,
		return 4;
	case vk::Format::eR16G16Snorm: //VK_FORMAT_R16G16_SNORM,
		return 4;
	case vk::Format::eR16G16Uscaled: //VK_FORMAT_R16G16_USCALED,
		return 4;
	case vk::Format::eR16G16Sscaled: //VK_FORMAT_R16G16_SSCALED,
		return 4;
	case vk::Format::eR16G16Uint: //VK_FORMAT_R16G16_UINT,
		return 4;
	case vk::Format::eR16G16Sint: //VK_FORMAT_R16G16_SINT,
		return 4;
	case vk::Format::eR16G16Sfloat: //VK_FORMAT_R16G16_SFLOAT,
		return 4;
	case vk::Format::eR16G16B16Unorm: //VK_FORMAT_R16G16B16_UNORM,
		return 6;
	case vk::Format::eR16G16B16Snorm: //VK_FORMAT_R16G16B16_SNORM
		return 6;
	case vk::Format::eR16G16B16Uscaled: //VK_FORMAT_R16G16B16_USCALED,
		return 6;
	case vk::Format::eR16G16B16Sscaled: //VK_FORMAT_R16G16B16_SSCALED,
		return 6;
	case vk::Format::eR16G16B16Uint: //VK_FORMAT_R16G16B16_UINT,
		return 6;
	case vk::Format::eR16G16B16Sint: //VK_FORMAT_R16G16B16_SINT,
		return 6;
	case vk::Format::eR16G16B16Sfloat: //VK_FORMAT_R16G16B16_SFLOAT,
		return 6;
	case vk::Format::eR16G16B16A16Unorm: //VK_FORMAT_R16G16B16A16_UNORM,
		return 8;
	case vk::Format::eR16G16B16A16Snorm: //VK_FORMAT_R16G16B16A16_SNORM,
		return 8;
	case vk::Format::eR16G16B16A16Uscaled: //VK_FORMAT_R16G16B16A16_USCALED,
		return 8;
	case vk::Format::eR16G16B16A16Sscaled: //VK_FORMAT_R16G16B16A16_SSCALED,
		return 8;
	case vk::Format::eR16G16B16A16Uint: //VK_FORMAT_R16G16B16A16_UINT,
		return 8;
	case vk::Format::eR16G16B16A16Sint: //VK_FORMAT_R16G16B16A16_SINT,
		return 8;
	case vk::Format::eR16G16B16A16Sfloat: //VK_FORMAT_R16G16B16A16_SFLOAT,
		return 8;
	case vk::Format::eR32Uint: //VK_FORMAT_R32_UINT,
		return 4;
	case vk::Format::eR32Sint: //VK_FORMAT_R32_SINT,
		return 4;
	case vk::Format::eR32Sfloat: //VK_FORMAT_R32_SFLOAT,
		return 4;
	case vk::Format::eR32G32Uint: //VK_FORMAT_R32G32_UINT,
		return 8;
	case vk::Format::eR32G32Sint: //VK_FORMAT_R32G32_SINT,
		return 8;
	case vk::Format::eR32G32Sfloat: //VK_FORMAT_R32G32_SFLOAT,
		return 8;
	case vk::Format::eR32G32B32Uint: //VK_FORMAT_R32G32B32_UINT,
		return 12;
	case vk::Format::eR32G32B32Sint: //VK_FORMAT_R32G32B32_SINT,
		return 12;
	case vk::Format::eR32G32B32Sfloat: //VK_FORMAT_R32G32B32_SFLOAT,
		return 12;
	case vk::Format::eR32G32B32A32Uint: //VK_FORMAT_R32G32B32A32_UINT,
		return 16;
	case vk::Format::eR32G32B32A32Sint: //VK_FORMAT_R32G32B32A32_SINT,
		return 16;
	case vk::Format::eR32G32B32A32Sfloat: //VK_FORMAT_R32G32B32A32_SFLOAT,
		return 16;
	case vk::Format::eR64Uint: //VK_FORMAT_R64_UINT,
		return 8;
	case vk::Format::eR64Sint: //VK_FORMAT_R64_SINT,
		return 8;
	case vk::Format::eR64Sfloat: //VK_FORMAT_R64_SFLOAT,
		return 8;
	case vk::Format::eR64G64Uint: //VK_FORMAT_R64G64_UINT,
		return 16;
	case vk::Format::eR64G64Sint: //VK_FORMAT_R64G64_SINT,
		return 16;
	case vk::Format::eR64G64Sfloat: //VK_FORMAT_R64G64_SFLOAT,
		return 16;
	case vk::Format::eR64G64B64Uint: //VK_FORMAT_R64G64B64_UINT,
		return 24;
	case vk::Format::eR64G64B64Sint: //VK_FORMAT_R64G64B64_SINT,
		return 24;
	case vk::Format::eR64G64B64Sfloat: //VK_FORMAT_R64G64B64_SFLOAT,
		return 24;
	case vk::Format::eR64G64B64A64Uint: //VK_FORMAT_R64G64B64A64_UINT,
		return 32;
	case vk::Format::eR64G64B64A64Sint: //VK_FORMAT_R64G64B64A64_SINT,
		return 32;
	case vk::Format::eR64G64B64A64Sfloat: //VK_FORMAT_R64G64B64A64_SFLOAT,
		return 32;
	case vk::Format::eB10G11R11UfloatPack32: //VK_FORMAT_B10G11R11_UFLOAT_PACK32,
	case vk::Format::eE5B9G9R9UfloatPack32: //VK_FORMAT_E5B9G9R9_UFLOAT_PACK32,
	case vk::Format::eD16Unorm: //VK_FORMAT_D16_UNORM,
		return 2;
	case vk::Format::eX8D24UnormPack32: //VK_FORMAT_X8_D24_UNORM_PACK32,
	case vk::Format::eD32Sfloat: //VK_FORMAT_D32_SFLOAT,
		return 4;
	case vk::Format::eS8Uint: //VK_FORMAT_S8_UINT,
		return 1;
	case vk::Format::eD16UnormS8Uint: //VK_FORMAT_D16_UNORM_S8_UINT,
		return 3;
	case vk::Format::eD24UnormS8Uint: //VK_FORMAT_D24_UNORM_S8_UINT,
		return 5;
	case vk::Format::eD32SfloatS8Uint: //VK_FORMAT_D32_SFLOAT_S8_UINT,
	case vk::Format::eBc1RgbUnormBlock: //VK_FORMAT_BC1_RGB_UNORM_BLOCK,
	case vk::Format::eBc1RgbSrgbBlock: //VK_FORMAT_BC1_RGB_SRGB_BLOCK,
	case vk::Format::eBc1RgbaUnormBlock: //VK_FORMAT_BC1_RGBA_UNORM_BLOCK,
	case vk::Format::eBc1RgbaSrgbBlock: //VK_FORMAT_BC1_RGBA_SRGB_BLOCK,
	case vk::Format::eBc2UnormBlock: //VK_FORMAT_BC2_UNORM_BLOCK,
	case vk::Format::eBc2SrgbBlock: //VK_FORMAT_BC2_SRGB_BLOCK,
	case vk::Format::eBc3UnormBlock: //VK_FORMAT_BC3_UNORM_BLOCK,
	case vk::Format::eBc3SrgbBlock: //VK_FORMAT_BC3_SRGB_BLOCK,
	case vk::Format::eBc4UnormBlock: //VK_FORMAT_BC4_UNORM_BLOCK,
	case vk::Format::eBc4SnormBlock: //VK_FORMAT_BC4_SNORM_BLOCK,
	case vk::Format::eBc5UnormBlock: //VK_FORMAT_BC5_UNORM_BLOCK,
	case vk::Format::eBc5SnormBlock: //VK_FORMAT_BC5_SNORM_BLOCK,
	case vk::Format::eBc6HUfloatBlock: //VK_FORMAT_BC6H_UFLOAT_BLOCK,
	case vk::Format::eBc6HSfloatBlock: //VK_FORMAT_BC6H_SFLOAT_BLOCK,
	case vk::Format::eBc7UnormBlock: //VK_FORMAT_BC7_UNORM_BLOCK,
	case vk::Format::eBc7SrgbBlock: //VK_FORMAT_BC7_SRGB_BLOCK,
	case vk::Format::eEtc2R8G8B8UnormBlock: //VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK,
	case vk::Format::eEtc2R8G8B8SrgbBlock: //VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK,
	case vk::Format::eEtc2R8G8B8A1UnormBlock: //VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK,
	case vk::Format::eEtc2R8G8B8A1SrgbBlock: //VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK,
	case vk::Format::eEtc2R8G8B8A8UnormBlock: //VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK,
	case vk::Format::eEtc2R8G8B8A8SrgbBlock: //VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK,
	case vk::Format::eEacR11UnormBlock: //VK_FORMAT_EAC_R11_UNORM_BLOCK,
	case vk::Format::eEacR11SnormBlock: //VK_FORMAT_EAC_R11_SNORM_BLOCK,
	case vk::Format::eEacR11G11UnormBlock: //VK_FORMAT_EAC_R11G11_UNORM_BLOCK,
	case vk::Format::eEacR11G11SnormBlock: //VK_FORMAT_EAC_R11G11_SNORM_BLOCK,
	case vk::Format::eAstc4x4UnormBlock: //VK_FORMAT_ASTC_4x4_UNORM_BLOCK,
	case vk::Format::eAstc4x4SrgbBlock: //VK_FORMAT_ASTC_4x4_SRGB_BLOCK,
	case vk::Format::eAstc5x4UnormBlock: //VK_FORMAT_ASTC_5x4_UNORM_BLOCK,
	case vk::Format::eAstc5x4SrgbBlock: //VK_FORMAT_ASTC_5x4_SRGB_BLOCK,
	case vk::Format::eAstc5x5UnormBlock: //VK_FORMAT_ASTC_5x5_UNORM_BLOCK,
	case vk::Format::eAstc5x5SrgbBlock: //VK_FORMAT_ASTC_5x5_SRGB_BLOCK,
	case vk::Format::eAstc6x5UnormBlock: //VK_FORMAT_ASTC_6x5_UNORM_BLOCK,
	case vk::Format::eAstc6x5SrgbBlock: //VK_FORMAT_ASTC_6x5_SRGB_BLOCK,
	case vk::Format::eAstc6x6UnormBlock: //VK_FORMAT_ASTC_6x6_UNORM_BLOCK,
	case vk::Format::eAstc6x6SrgbBlock: //VK_FORMAT_ASTC_6x6_SRGB_BLOCK,
	case vk::Format::eAstc8x5UnormBlock: //VK_FORMAT_ASTC_8x5_UNORM_BLOCK,
	case vk::Format::eAstc8x5SrgbBlock: //VK_FORMAT_ASTC_8x5_SRGB_BLOCK,
	case vk::Format::eAstc8x6UnormBlock: //VK_FORMAT_ASTC_8x6_UNORM_BLOCK,
	case vk::Format::eAstc8x6SrgbBlock: //VK_FORMAT_ASTC_8x6_SRGB_BLOCK,
	case vk::Format::eAstc8x8UnormBlock: //VK_FORMAT_ASTC_8x8_UNORM_BLOCK,
	case vk::Format::eAstc8x8SrgbBlock: //VK_FORMAT_ASTC_8x8_SRGB_BLOCK,
	case vk::Format::eAstc10x5UnormBlock: //VK_FORMAT_ASTC_10x5_UNORM_BLOCK,
	case vk::Format::eAstc10x5SrgbBlock: //VK_FORMAT_ASTC_10x5_SRGB_BLOCK,
	case vk::Format::eAstc10x6UnormBlock: //VK_FORMAT_ASTC_10x6_UNORM_BLOCK,
	case vk::Format::eAstc10x6SrgbBlock: //VK_FORMAT_ASTC_10x6_SRGB_BLOCK,
	case vk::Format::eAstc10x8UnormBlock: //VK_FORMAT_ASTC_10x8_UNORM_BLOCK,
	case vk::Format::eAstc10x8SrgbBlock: //VK_FORMAT_ASTC_10x8_SRGB_BLOCK,
	case vk::Format::eAstc10x10UnormBlock: //VK_FORMAT_ASTC_10x10_UNORM_BLOCK,
	case vk::Format::eAstc10x10SrgbBlock: //VK_FORMAT_ASTC_10x10_SRGB_BLOCK,
	case vk::Format::eAstc12x10UnormBlock: //VK_FORMAT_ASTC_12x10_UNORM_BLOCK,
	case vk::Format::eAstc12x10SrgbBlock: //VK_FORMAT_ASTC_12x10_SRGB_BLOCK,
	case vk::Format::eAstc12x12UnormBlock: //VK_FORMAT_ASTC_12x12_UNORM_BLOCK,
	case vk::Format::eAstc12x12SrgbBlock: //VK_FORMAT_ASTC_12x12_SRGB_BLOCK,
	case vk::Format::eG8B8G8R8422Unorm: //VK_FORMAT_G8B8G8R8_422_UNORM,
	//case vk::Format::eG8B8G8R8422UnormKHR: //VK_FORMAT_G8B8G8R8_422_UNORM,
	case vk::Format::eB8G8R8G8422Unorm: //VK_FORMAT_B8G8R8G8_422_UNORM,
	//case vk::Format::eB8G8R8G8422UnormKHR: //VK_FORMAT_B8G8R8G8_422_UNORM,
	case vk::Format::eG8B8R83Plane420Unorm: //VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM,
	//case vk::Format::eG8B8R83Plane420UnormKHR: //VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM,
	case vk::Format::eG8B8R82Plane420Unorm: //VK_FORMAT_G8_B8R8_2PLANE_420_UNORM,
	//case vk::Format::eG8B8R82Plane420UnormKHR: //VK_FORMAT_G8_B8R8_2PLANE_420_UNORM,
	case vk::Format::eG8B8R83Plane422Unorm: //VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM,
	//case vk::Format::eG8B8R83Plane422UnormKHR: //VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM,
	case vk::Format::eG8B8R82Plane422Unorm: //VK_FORMAT_G8_B8R8_2PLANE_422_UNORM,
	//case vk::Format::eG8B8R82Plane422UnormKHR: //VK_FORMAT_G8_B8R8_2PLANE_422_UNORM,
	case vk::Format::eG8B8R83Plane444Unorm: //VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM,
	//case vk::Format::eG8B8R83Plane444UnormKHR: //VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM,
	case vk::Format::eR10X6UnormPack16: //VK_FORMAT_R10X6_UNORM_PACK16,
	//case vk::Format::eR10X6UnormPack16KHR: //VK_FORMAT_R10X6_UNORM_PACK16,
	case vk::Format::eR10X6G10X6Unorm2Pack16: //VK_FORMAT_R10X6G10X6_UNORM_2PACK16,
	//case vk::Format::eR10X6G10X6Unorm2Pack16KHR: //VK_FORMAT_R10X6G10X6_UNORM_2PACK16,
	case vk::Format::eR10X6G10X6B10X6A10X6Unorm4Pack16: //VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16,
	//case vk::Format::eR10X6G10X6B10X6A10X6Unorm4Pack16KHR: //VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16,
	case vk::Format::eG10X6B10X6G10X6R10X6422Unorm4Pack16: //VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16,
	//case vk::Format::eG10X6B10X6G10X6R10X6422Unorm4Pack16KHR: //VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16,
	case vk::Format::eB10X6G10X6R10X6G10X6422Unorm4Pack16: //VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16,
	//case vk::Format::eB10X6G10X6R10X6G10X6422Unorm4Pack16KHR: //VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16,
	case vk::Format::eG10X6B10X6R10X63Plane420Unorm3Pack16: //VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16,
	//case vk::Format::eG10X6B10X6R10X63Plane420Unorm3Pack16KHR: //VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16,
	case vk::Format::eG10X6B10X6R10X62Plane420Unorm3Pack16: //VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16,
	//case vk::Format::eG10X6B10X6R10X62Plane420Unorm3Pack16KHR: //VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16,
	case vk::Format::eG10X6B10X6R10X63Plane422Unorm3Pack16: //VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16,
	//case vk::Format::eG10X6B10X6R10X63Plane422Unorm3Pack16KHR: //VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16,
	case vk::Format::eG10X6B10X6R10X62Plane422Unorm3Pack16: //VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16,
	//case vk::Format::eG10X6B10X6R10X62Plane422Unorm3Pack16KHR: //VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16,
	case vk::Format::eG10X6B10X6R10X63Plane444Unorm3Pack16: //VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16,
	//case vk::Format::eG10X6B10X6R10X63Plane444Unorm3Pack16KHR: //VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16,
	case vk::Format::eR12X4UnormPack16: //VK_FORMAT_R12X4_UNORM_PACK16,
	//case vk::Format::eR12X4UnormPack16KHR: //VK_FORMAT_R12X4_UNORM_PACK16,
	case vk::Format::eR12X4G12X4Unorm2Pack16: //VK_FORMAT_R12X4G12X4_UNORM_2PACK16,
	//case vk::Format::eR12X4G12X4Unorm2Pack16KHR: //VK_FORMAT_R12X4G12X4_UNORM_2PACK16,
	case vk::Format::eR12X4G12X4B12X4A12X4Unorm4Pack16: //VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16,
	//case vk::Format::eR12X4G12X4B12X4A12X4Unorm4Pack16KHR: //VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16,
	case vk::Format::eG12X4B12X4G12X4R12X4422Unorm4Pack16: //VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16,
	//case vk::Format::eG12X4B12X4G12X4R12X4422Unorm4Pack16KHR: //VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16,
	case vk::Format::eB12X4G12X4R12X4G12X4422Unorm4Pack16: //VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16,
	//case vk::Format::eB12X4G12X4R12X4G12X4422Unorm4Pack16KHR: //VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16,
	case vk::Format::eG12X4B12X4R12X43Plane420Unorm3Pack16: //VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16,
	//case vk::Format::eG12X4B12X4R12X43Plane420Unorm3Pack16KHR: //VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16,
	case vk::Format::eG12X4B12X4R12X42Plane420Unorm3Pack16: //VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16,
	//case vk::Format::eG12X4B12X4R12X42Plane420Unorm3Pack16KHR: //VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16,
	case vk::Format::eG12X4B12X4R12X43Plane422Unorm3Pack16: //VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16,
	//case vk::Format::eG12X4B12X4R12X43Plane422Unorm3Pack16KHR: //VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16,
	case vk::Format::eG12X4B12X4R12X42Plane422Unorm3Pack16: //VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16,
	//case vk::Format::eG12X4B12X4R12X42Plane422Unorm3Pack16KHR: //VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16,
	case vk::Format::eG12X4B12X4R12X43Plane444Unorm3Pack16: //VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16,
	//case vk::Format::eG12X4B12X4R12X43Plane444Unorm3Pack16KHR: //VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16,
	case vk::Format::eG16B16G16R16422Unorm: //VK_FORMAT_G16B16G16R16_422_UNORM,
	//case vk::Format::eG16B16G16R16422UnormKHR: //VK_FORMAT_G16B16G16R16_422_UNORM,
	case vk::Format::eB16G16R16G16422Unorm: //VK_FORMAT_B16G16R16G16_422_UNORM,
	//case vk::Format::eB16G16R16G16422UnormKHR: //VK_FORMAT_B16G16R16G16_422_UNORM,
	case vk::Format::eG16B16R163Plane420Unorm: //VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM,
	//case vk::Format::eG16B16R163Plane420UnormKHR: //VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM,
	case vk::Format::eG16B16R162Plane420Unorm: //VK_FORMAT_G16_B16R16_2PLANE_420_UNORM,
	//case vk::Format::eG16B16R162Plane420UnormKHR: //VK_FORMAT_G16_B16R16_2PLANE_420_UNORM,
	case vk::Format::eG16B16R163Plane422Unorm: //VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM,
	//case vk::Format::eG16B16R163Plane422UnormKHR: //VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM,
	case vk::Format::eG16B16R162Plane422Unorm: //VK_FORMAT_G16_B16R16_2PLANE_422_UNORM,
	//case vk::Format::eG16B16R162Plane422UnormKHR: //VK_FORMAT_G16_B16R16_2PLANE_422_UNORM,
	case vk::Format::eG16B16R163Plane444Unorm: //VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM,
	//case vk::Format::eG16B16R163Plane444UnormKHR: //VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM,
	case vk::Format::ePvrtc12BppUnormBlockIMG: //VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG,
	case vk::Format::ePvrtc14BppUnormBlockIMG: //VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG,
	case vk::Format::ePvrtc22BppUnormBlockIMG: //VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG,
	case vk::Format::ePvrtc24BppUnormBlockIMG: //VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG,
	case vk::Format::ePvrtc12BppSrgbBlockIMG: //VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG,
	case vk::Format::ePvrtc14BppSrgbBlockIMG: //VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG,
	case vk::Format::ePvrtc22BppSrgbBlockIMG: //VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG,
	case vk::Format::ePvrtc24BppSrgbBlockIMG: //VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG
	default:
		return 4;
	}
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

	vk::UniqueSampler mSampler;

	vk::UniqueBuffer mStagingBuffer;
	vk::UniqueDeviceMemory mStagingBufferMemory;

	vk::Format mFormat = vk::Format::eUndefined;
	vk::ImageLayout mImageLayout{ vk::ImageLayout::eUndefined };

	uint32_t mSize;
	uint32_t mWidth = 0;
	uint32_t mHeight = 0;
	uint32_t mMipMapCount = 0;
};

//Vertex only (for intermediate buffering)
struct FGLVertex
{
	FLOAT x;
	FLOAT y;
	FLOAT z;
};

//Vertex and primary color
struct FGLVertexColor
{
	FLOAT x;
	FLOAT y;
	FLOAT z;
	FPlane color;
};

//Normals
struct FGLNormal
{
	FLOAT x;
	FLOAT y;
	FLOAT z;
};

//Tex coords
struct FGLTexCoord
{
	FLOAT u;
	FLOAT v;
};

//Secondary color
struct FGLSecondaryColor
{
	FPlane specular;
};

struct FGLMapDot
{
	FLOAT u;
	FLOAT v;
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
	int32_t mUtilityRecordingCount = 0;
	vk::UniqueDescriptorSetLayout mDescriptorLayout;
	vk::UniquePipelineLayout mPipelineLayout;
	vk::DescriptorBufferInfo mDescriptorBufferInfo[3];
	vk::WriteDescriptorSet mWriteDescriptorSet[3];
	vk::DescriptorImageInfo mDescriptorImageInfo[4];
	std::array<std::vector<vk::DescriptorSet>, 3> mDescriptorSets;
	int32_t mDescriptorSetIndex = 0;
	vk::DescriptorSet mLastDescriptorSet;
	std::array<std::vector<vk::UniquePipeline>, 3> mPipelines;
	//vk::CommandBuffer mCurrentDrawCommandBuffer;
	vk::CommandBuffer mCurrentUtilityCommandBuffer;

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
	vk::UniqueShaderModule mDefaultRenderingStateVertex;
	vk::UniqueShaderModule mDefaultRenderingStateFragment;



	//Vulkan Functions
	template < typename T, int32_t arraySize>
	vk::UniqueShaderModule LoadShaderFromConst(const T(&data)[arraySize])
	{
		const vk::ShaderModuleCreateInfo moduleCreateInfo(vk::ShaderModuleCreateFlags(), arraySize * sizeof(T), (const uint32_t*)data);
		return mDevice->createShaderModuleUnique(moduleCreateInfo);
	}

	void BeginRecordingUtilityCommands();
	void StopRecordingUtilityCommands();
	void SetImageLayout(CachedTexture& cachedTexture, vk::ImageLayout newLayout);
	bool FindMemoryTypeFromProperties(uint32_t typeBits, vk::MemoryPropertyFlags requirements_mask, uint32_t* typeIndex);
	void BindTexture(uint32_t index, uint32_t count, FTextureInfo& Info, DWORD PolyFlags);
	void UpdateDescriptors(bool write);
	void UpdatePipline(DWORD PolyFlags, vk::PrimitiveTopology topology = vk::PrimitiveTopology::eTriangleFan, uint32_t vertexElementCount = 2, bool secondColor = false);

	//UT Config Params
	void AddFloatConfigParam(const TCHAR* pName, FLOAT& param, ECppProperty EC_CppProperty, INT InOffset, FLOAT defaultValue);
	void AddBoolConfigParam(DWORD BitMaskOffset, const TCHAR* pName, UBOOL& param, ECppProperty EC_CppProperty, INT InOffset, UBOOL defaultValue);
	void AddIntConfigParam(const TCHAR* pName, INT& param, ECppProperty EC_CppProperty, INT InOffset, INT defaultValue);

	FLOAT LODBias = 0.0f;
	INT MaxAnisotropy = 0;
	INT LogLevel = 0;
	INT MinLogTextureSize = 0;
	INT MaxLogTextureSize = 8;
	UBOOL UseTripleBuffering = 0;
	UBOOL EnableDebugLayers = 0;
	UBOOL UseVSync = 0;

	//Misc
	void LoadConfiguration(std::string filename);

	HWND mHWND = 0;
	HDC mHDC = 0;
	HINSTANCE mHINSTANCE = 0;
	INT mNewX = 0;
	INT mNewY = 0;
	INT mNewColorBytes = 0;
	UBOOL mFullscreen = 0;

	FLOAT mRProjZ = 0.0f;
	FLOAT mAspect = 0.0f;
	FLOAT mRFX2 = 0.0f;
	FLOAT mRFY2 = 0.0f;
	INT mUCopyBits = 0;
	INT mVCopyBits = 0;
};

