cmake_minimum_required(VERSION 3.10)
project(PixelDome)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(VENDOR_SOURCE
	Vendor/Source/glad.c
	Vendor/Source/stb_image.cpp
	Vendor/Source/imgui.cpp
	Vendor/Source/imgui_draw.cpp
	Vendor/Source/imgui_tables.cpp
	Vendor/Source/imgui_widgets.cpp
	Vendor/Source/imgui_impl_glfw.cpp
	Vendor/Source/imgui_impl_opengl3.cpp
)
set(SOURCE_UTIL
	Source/Util/JsonLoader.hpp
	Source/Util/JsonLoader.cpp
)
set(SOURCE_GRAPHICS
	Source/Graphics/Camera.hpp
	Source/Graphics/Camera.cpp
	Source/Graphics/GLContext.hpp
	Source/Graphics/GLContext.cpp
	Source/Graphics/Window.hpp
	Source/Graphics/Window.cpp
	Source/Graphics/VertexArray.hpp
	Source/Graphics/VertexArray.cpp
	Source/Graphics/VertexBuffer.hpp
	Source/Graphics/VertexBuffer.cpp
	Source/Graphics/IndexBuffer.hpp
	Source/Graphics/IndexBuffer.cpp
	Source/Graphics/Mesh.hpp
	Source/Graphics/Mesh.cpp
	Source/Graphics/Shader.hpp
	Source/Graphics/Shader.cpp
	Source/Graphics/Texture.hpp
	Source/Graphics/Texture.cpp
)
set(SOURCE_GUI
	Source/Gui/ImguiManager.hpp
	Source/Gui/ImguiManager.cpp
)
set(SOURCE_MAP
	Source/Map/Level.hpp
	Source/Map/Level.cpp
)
set(SOURCE_ENTITY
	Source/Entity/Player.hpp
	Source/Entity/Player.cpp
	Source/Entity/Tile.hpp
	Source/Entity/Tile.cpp
)
set(SOURCE_DEBUG
	Source/Debug/DebugGui.hpp
	Source/Debug/DebugGui.cpp
	Source/Debug/Editor.hpp
	Source/Debug/Editor.cpp
)
set(SOURCE_BASE
	Source/Base/Game.hpp
	Source/Base/Game.cpp
	Source/Base/State.hpp
	Source/Base/State.cpp
	Source/Base/Main.cpp
)
add_executable(${PROJECT_NAME}
	${VENDOR_SOURCE}
	${SOURCE_UTIL}
	${SOURCE_GRAPHICS}
	${SOURCE_GUI}
	${SOURCE_MAP}
	${SOURCE_ENTITY}
	${SOURCE_DEBUG}
	${SOURCE_BASE}
)
target_include_directories(${PROJECT_NAME} PRIVATE
	${PROJECT_SOURCE_DIR}/Vendor/Include
	${PROJECT_SOURCE_DIR}/Vendor/Include/stb
	${PROJECT_SOURCE_DIR}/Vendor/Include/imgui
	${PROJECT_SOURCE_DIR}/Source
)
target_link_libraries(${PROJECT_NAME} PRIVATE
	${PROJECT_SOURCE_DIR}/Vendor/Library/glfw3.lib
	opengl32.lib
)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/Assets
		$<TARGET_FILE_DIR:${PROJECT_NAME}>/Assets
)