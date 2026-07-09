rm -rf ./build 
conan install .conan --output-folder=build --build=missing -pr:h=.conan/profiles/default -pr:b=.conan/profiles/default -s build_type=Debug
cmake --preset conan-debug
cmake --build --preset conan-debug