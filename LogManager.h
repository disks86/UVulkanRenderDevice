#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>

#include <vulkan/vulkan.hpp>

std::ostream& operator<< (std::ostream& os, vk::Result result);

enum SeverityLevel
{
	trace,
	debug,
	info,
	warning,
	error,
	fatal
};

class NullBuffer
	: public std::streambuf
{
public:
	int overflow(int c) { return c; }
};

class NullStream
	: public std::ostream
{
private:
	NullBuffer obj;
public:
	NullStream()
		: std::ostream(&obj)
	{
	}
};

class LockedStream
{
	std::unique_lock<std::mutex> mLock;
	std::ostream* mStream;

public:
	LockedStream(std::ostream& stream, std::mutex& mutant)
		: mStream(&stream),
		mLock(mutant)
	{
	}

	 LockedStream(LockedStream&& obj) noexcept
		: mLock(std::move(obj.mLock))
		, mStream(obj.mStream)
	{
		obj.mStream = nullptr;
	}

	friend LockedStream&& operator << (LockedStream&& ls, std::ostream& (*argument)(std::ostream&))
	{
		(*ls.mStream) << argument;
		return std::move(ls);
	}

	friend LockedStream&& operator << (LockedStream&& ls, uint32_t&& argument)
	{
		(*ls.mStream) << argument;
		return std::move(ls);
	}

	template <typename ArgumentType>
	friend LockedStream&& operator << (LockedStream&& ls, ArgumentType&& argument)
	{
		(*ls.mStream) << std::forward<ArgumentType>(argument);
		return std::move(ls);
	}
};

class LogManager
{
private:
	static LogManager* mInstance;

	std::mutex mMutex;
	std::ofstream mFileStream;
	NullStream mNullStream;
	SeverityLevel mSeverityLevel;

public:
	LogManager(const std::string& filename, SeverityLevel severityLevel);
	~LogManager();
	static void Create(const std::string& filename, SeverityLevel severityLevel);
	static void Destroy();

	friend LockedStream Log(SeverityLevel severityLevel);
};

LockedStream Log(SeverityLevel severityLevel);