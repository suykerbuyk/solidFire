#!/bin/sh
mkdir -p ./bld/Debug/prj >/dev/null
mkdir -p ./bld/Release/prj >/dev/null
cd ./bld/Debug/prj
cmake ../../.. -DCMAKE_BUILD_TYPE=Debug && make
#cd ../Release
#cmake ../../.. -DCMAKE_BUILD_TYPE=Release && make 
