# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("MumbleLink")

# Optimize for speed
add_compile_options(/O2>)
add_compile_options(/Ot>)
add_compile_options(/Ox>)
add_compile_options(/Oy>)

# Enable intrinsic functions
add_compile_options(/Oi>)

# Separate functions for the linker to improve the optimization process
add_compile_options(/Gy>)

# Optimize global data to reduce the binary size
add_compile_options(/Gw>)

# Enable string pooling to reduce binary size by consolidating duplicate strings
add_compile_options(/GF>)

# Optimize floating point operations for speed (may introduce minor precision differences)
add_compile_options(/fp:fast>)

# Inline any suitable function to improve performance by reducing function call overhead
add_compile_options(/Ob2>)

add_compile_options(/GR-)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /OPT:REF /OPT:ICF")
add_compile_options(/GL)

# Include sub-projects.
add_subdirectory ("MumbleLink")
