#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace templeG {

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};

}

// templeG graphics
#define TG_TRACE(...)    ::templeG::Log::GetLogger()->trace(__VA_ARGS__)
#define TG_INFO(...)     ::templeG::Log::GetLogger()->info(__VA_ARGS__)
#define TG_WARN(...)     ::templeG::Log::GetLogger()->warn(__VA_ARGS__)
#define TG_ERROR(...)    ::templeG::Log::GetLogger()->error(__VA_ARGS__)
#define TG_CRITICAL(...)    ::templeG::Log::GetLogger()->critical(__VA_ARGS__)