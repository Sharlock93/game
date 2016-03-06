@echo off

set GLFW_L=-LC:\dev\lib\lib-mingw
set HEADER=-IC:\dev\lib\include
set GLEW_L=-LC:\dev\lib\lib-glew\Release\x64
set lib_names=-lglfw3 -lglew32s -lgdi32 -lopengl32
g++ src\main.cpp %HEADER% %GLFW_L% %GLEW_L% -o bin\main.exe %lib_names%
