// cmake -A Win32 -B build -S . -DCMAKE_TOOLCHAIN_FILE=C:\Packages\scripts\buildsystems\vcpkg.cmake
// cmake --build .\build\ --config Release
// .\build\Release\features.exe
// rm -Recurse -Force .\build

#include "example01.hpp"
#include "example02.hpp"

int main()
{
  // Example01::main();
  Example02::main();
}