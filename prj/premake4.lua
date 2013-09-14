solution "solidFire"
   configurations { "Debug", "Release" }
 
   project "thread"
      kind "ConsoleApp"
      language "C++"
      files { "./src/thread/**.h", "./src/thread/**.cc" }
      location "build" 
      libdirs { os.findlib("boost_thread") }
      includedirs {"/usr/local/include", "/usr/include" }
      links { "boost_thread", "boost_program_options", "boost_filesystem"}
      flags { "ExtraWarnings" }
 
      configuration "Debug"
         defines { "DEBUG" }
         flags   { "Symbols" }
         targetdir("bin/debug")
 
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }    
         targetdir("bin/release")

   project "path_info"
      kind "ConsoleApp"
      language "C++"
      files { "./src/path_info/**.h", "./src/path_info/**.cpp" }
      location "build" 
      libdirs { os.findlib("boost_filesystem") }
      includedirs {"/usr/local/include", "/usr/include" }
      links { "boost_program_options", "boost_filesystem"}
      flags { "ExtraWarnings" }
 
      configuration "Debug"
         defines { "DEBUG" }
         flags   { "Symbols" }
         targetdir("bin/debug")
 
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }    
         targetdir("bin/release")
