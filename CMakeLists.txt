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
	SmallRenderer/core/buffer.h
	SmallRenderer/core/matrix.h
	SmallRenderer/core/camera.h
	SmallRenderer/core/transform.h
	SmallRenderer/core/light.h
	SmallRenderer/shader/shader.h
	SmallRenderer/shader/blinnphongshader.h
)
set(SOURCES
	SmallRenderer/core/file.cpp
	SmallRenderer/core/image.cpp
	SmallRenderer/core/util.cpp
	SmallRenderer/core/model.cpp
	SmallRenderer/core/draw2d.cpp
	SmallRenderer/core/math.cpp
	SmallRenderer/core/buffer.cpp
	SmallRenderer/core/camera.cpp
	SmallRenderer/core/transform.cpp
	SmallRenderer/core/light.cpp
	SmallRenderer/shader/shader.cpp
	SmallRenderer/shader/blinnphongshader.cpp
	SmallRenderer/main.cpp
)

# ==============================================================================
# Target definition
# ==============================================================================
set(TARGET SRenderer)

# Add source to this project's executable.
add_executable(${TARGET} ${HEADERS} ${SOURCES})
