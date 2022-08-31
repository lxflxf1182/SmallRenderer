# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("SmallRenderer")

set(HEADERS
	SmallRenderer/core/file.h
	SmallRenderer/core/image.h
	SmallRenderer/core/util.h
	SmallRenderer/core/vector.h
	SmallRenderer/core/model.h
	SmallRenderer/core/draw2d.h
	SmallRenderer/core/math.h
)
set(SOURCES
	SmallRenderer/core/file.cpp
	SmallRenderer/core/image.cpp
	SmallRenderer/core/util.cpp
	SmallRenderer/core/vector.cpp
	SmallRenderer/core/model.cpp
	SmallRenderer/core/draw2d.cpp
	SmallRenderer/core/math.cpp
	SmallRenderer/main.cpp
)

# ==============================================================================
# Target definition
# ==============================================================================
set(TARGET SRenderer)

# Add source to this project's executable.
add_executable(${TARGET} ${HEADERS} ${SOURCES})
