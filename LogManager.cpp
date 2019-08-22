#include "pch.h"
#include "LogManager.h"

static char SeverityText[6][20] =
{
	"[TRACE] ",
	"[DEBUG] ",
	"[INFO] ",
	"[WARNING] ",
	"[ERROR] ",
	"[FATAL] "
};

const std::string mResultStrings[] =
{
	"Unknown",
	"VK_SUCCESS",
	"VK_NOT_READY",
	"VK_TIMEOUT",
	"VK_EVENT_SET",
	"VK_EVENT_RESET",
	"VK_INCOMPLETE",
	"VK_ERROR_OUT_OF_HOST_MEMORY",
	"VK_ERROR_OUT_OF_DEVICE_MEMORY",
	"VK_ERROR_INITIALIZATION_FAILED",
	"VK_ERROR_DEVICE_LOST",
	"VK_ERROR_MEMORY_MAP_FAILED",
	"VK_ERROR_LAYER_NOT_PRESENT",
	"VK_ERROR_EXTENSION_NOT_PRESENT",
	"VK_ERROR_FEATURE_NOT_PRESENT",
	"VK_ERROR_INCOMPATIBLE_DRIVER",
	"VK_ERROR_TOO_MANY_OBJECTS",
	"VK_ERROR_FORMAT_NOT_SUPPORTED",
	"VK_ERROR_FRAGMENTED_POOL",
	"VK_ERROR_SURFACE_LOST_KHR",
	"VK_ERROR_NATIVE_WINDOW_IN_USE_KHR",
	"VK_SUBOPTIMAL_KHR",
	"VK_ERROR_OUT_OF_DATE_KHR",
	"VK_ERROR_INCOMPATIBLE_DISPLAY_KHR",
	"VK_ERROR_VALIDATION_FAILED_EXT",
	"VK_ERROR_INVALID_SHADER_NV",
	"VK_ERROR_OUT_OF_POOL_MEMORY_KHR",
	"VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR",
	"VK_ERROR_NOT_PERMITTED_EXT"
};

std::ostream& operator<< (std::ostream& os, vk::Result result)
{
	switch (result)
	{
	case vk::Result::eSuccess:
		return os <<  mResultStrings[1];
	case vk::Result::eNotReady:
		return os <<  mResultStrings[2];
	case vk::Result::eTimeout:
		return os <<  mResultStrings[3];
	case vk::Result::eEventSet:
		return os <<  mResultStrings[4];
	case vk::Result::eEventReset:
		return os <<  mResultStrings[5];
	case vk::Result::eIncomplete:
		return os <<  mResultStrings[6];
	case vk::Result::eErrorOutOfHostMemory:
		return os <<  mResultStrings[7];
	case vk::Result::eErrorOutOfDeviceMemory:
		return os <<  mResultStrings[8];
	case vk::Result::eErrorInitializationFailed:
		return os <<  mResultStrings[9];
	case vk::Result::eErrorDeviceLost:
		return os <<  mResultStrings[10];
	case vk::Result::eErrorMemoryMapFailed:
		return os <<  mResultStrings[11];
	case vk::Result::eErrorLayerNotPresent:
		return os <<  mResultStrings[12];
	case vk::Result::eErrorExtensionNotPresent:
		return os <<  mResultStrings[13];
	case vk::Result::eErrorFeatureNotPresent:
		return os <<  mResultStrings[14];
	case vk::Result::eErrorIncompatibleDriver:
		return os <<  mResultStrings[15];
	case vk::Result::eErrorTooManyObjects:
		return os <<  mResultStrings[16];
	case vk::Result::eErrorFormatNotSupported:
		return os <<  mResultStrings[17];
	case vk::Result::eErrorFragmentedPool:
		return os <<  mResultStrings[18];
	case vk::Result::eErrorSurfaceLostKHR:
		return os <<  mResultStrings[19];
	case vk::Result::eErrorNativeWindowInUseKHR:
		return os <<  mResultStrings[20];
	case vk::Result::eSuboptimalKHR:
		return os <<  mResultStrings[21];
	case vk::Result::eErrorOutOfDateKHR:
		return os <<  mResultStrings[22];
	case vk::Result::eErrorIncompatibleDisplayKHR:
		return os <<  mResultStrings[23];
	case vk::Result::eErrorValidationFailedEXT:
		return os <<  mResultStrings[24];
	case vk::Result::eErrorInvalidShaderNV:
		return os <<  mResultStrings[25];
	case vk::Result::eErrorOutOfPoolMemoryKHR:
		return os <<  mResultStrings[26];
	case vk::Result::eErrorInvalidExternalHandleKHR:
		return os <<  mResultStrings[27];
	case vk::Result::eErrorNotPermittedEXT:
		return os <<  mResultStrings[28];
	default:
		return os <<  mResultStrings[0];
	}
}

LogManager* LogManager::mInstance;

LogManager::LogManager(const std::string& filename, SeverityLevel severityLevel)
	: mFileStream(filename),
	mSeverityLevel(severityLevel)
{
}

LogManager::~LogManager()
{
}

void LogManager::Create(const std::string& filename, SeverityLevel severityLevel)
{
	LogManager::mInstance = new LogManager(filename, severityLevel);
}

void LogManager::Destroy()
{
	delete LogManager::mInstance;
}

LockedStream Log(SeverityLevel severityLevel)
{
	if (severityLevel >= LogManager::mInstance->mSeverityLevel)
	{
		return LockedStream(LogManager::mInstance->mFileStream, LogManager::mInstance->mMutex);
	}
	else
	{
		return LockedStream(LogManager::mInstance->mNullStream, LogManager::mInstance->mMutex);
	}
};