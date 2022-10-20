workspace "OpenGL"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}
	outputdir="%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project"OpenGL"
	kind "ConsoleApp"
	language"C++"
	
	

	targetdir("bin/"..outputdir.."/%{prj.name}")
	objdir("bin-int/"..outputdir.."/%{prj.name}")

	files
	{
		"%{prj.location}/src/**.h",
		"%{prj.location}/src/**.cpp"
	
	}
	includedirs
	{
		"Src/vendor",
		"Src",
		"Dependencies/GLFW/include",
		"Dependencies/GLEW/include",
		"Dependencies/Assimp/include"
	}
	libdirs
	{	"Dependencies/GLFW/lib-vc2019",
		"Dependencies/GLEW/lib/Release/x64",
		"Dependencies/Assimp/lib/Release"
	}
	links
	{
		"glew32s.lib"
		,"assimp-vc142-mt.lib"
		,"glfw3_mt.lib",
		"OpenGL32.lib"
	}

	
	filter "system:windows"
	cppdialect"C++17"
	staticruntime"on"
	systemversion"10.0.19041.0"

	defines
	{
		"GLEW_STATIC"
	}
	filter "configurations:Debug"
	defines { "DEBUG" }
	symbols "On"

 filter "configurations:Release"
	defines { "NDEBUG" }
	optimize "On"