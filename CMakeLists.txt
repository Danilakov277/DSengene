cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(PROJECT_NAME DSEngene)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
    src/try.cpp 
    src/Render/ShaderProgram.cpp
    src/Render/Texture2D.h
    src/Render/Texture2D.cpp
    src/Render/ShaderProgram.h
    src/Render/Sprite.cpp
    src/Render/Sprite.h
    src/Resources/ResourcesManger.cpp
    src/Resources/ResourcesManger.h
    src/Resources/stb_image.h
	src/Game/Game.cpp
	src/Game/Game.h
	src/Render/VertexBuffer.cpp
	src/Render/VertexBuffer.h
	src/Render/VertexBufferLayout.h
	src/Render/VertexBufferLayout.cpp
	src/Render/VertexArray.h
	src/Render/VertexArray.cpp
	src/Render/IndexBuffer.cpp
	src/Render/IndexBuffer.h
	src/Render/Renderer.cpp
	src/Render/Renderer.h
	src/Render/SpriteAnimator.cpp
	src/Render/SpriteAnimator.h
	src/Game/GameObjects/Tank.h
	src/Game/GameObjects/Tank.cpp
	src/Game/GameObjects/IGameObject.cpp
	src/Game/GameObjects/IGameObject.h
	src/Game/GameObjects/BrickWall.cpp
	src/Game/GameObjects/BrickWall.h
	src/Game/GameObjects/BetonWall.cpp
	src/Game/GameObjects/BetonWall.h
	src/Game/Level.cpp
	src/Game/Level.h
	

)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)


include_directories(external/glm)

include_directories(external/repidjson/include)
include_directories(external/sfml/include)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)