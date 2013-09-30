
solution "solidFire"
   configurations { "Debug", "Release" }
   libdirs { os.findlib("boost_filesystem") }
   includedirs {"/usr/local/include", "/usr/include" }
   if _ACTION == "clean" then
      os.rmdir("../bin")
      os.rmdir("../bld")
      os.remove("Makefile")
   else 
      local clang_complete = io.open(".clang_complete", "w")
      for key,value in pairs(configuration().includedirs) do
        clang_complete:write(string.format("-I%s\n", tostring(value)))
      end
   end

   configuration "Debug"
      defines { "DEBUG" }
      flags   { "Symbols" }
      flags   { "ExtraWarnings" }
      targetdir("../bin/debug")

   configuration "Release"
      defines  { "NDEBUG" }
      flags    { "Optimize" }    
      flags    { "ExtraWarnings" }
      targetdir("../bin/release")


   project "wordcount"
      kind "ConsoleApp"
      language "C++"
      files { "../src/wordcount/**.hpp", "../src/wordcount/**.cpp" }
      libdirs { os.findlib("boost_thread") }
      includedirs {"/usr/local/include", "/usr/include", "../src/wordcount/inc" }
      links { "boost_thread", "boost_program_options", "boost_filesystem"}
      location "../bld" 

   project "path_info"
      kind "ConsoleApp"
      language "C++"
      files { "../src/path_info/**.h", "../src/path_info/**.cpp" }
      links { "boost_program_options", "boost_filesystem"}
      location "../bld" 
 
   project "asio_timer"
      kind "ConsoleApp"
      language "C++"
      files { "../src/asio_timer/**.h", "../src/asio_timer/**.cpp" }
      links { "boost_thread"}
      location "../bld" 
 
