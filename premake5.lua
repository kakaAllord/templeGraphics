workspace "templeGraphics"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}

IncludeDir["GLFW"] = "templeGraphics/vendor/glfw/include"
IncludeDir["Glad"] = "templeGraphics/vendor/Glad/include"

include "templeGraphics/vendor/glfw"
include "templeGraphics/vendor/Glad"

project "templeGraphics"
	location "templeGraphics"
	kind "ConsoleApp"
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "tgpch.h"
	pchsource "templeGraphics/src/tgpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	buildoptions
	{
		"/utf-8"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"templeGraphics_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "templeGraphics_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "templeGraphics_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "templeGraphics_DIST"
		optimize "On"
