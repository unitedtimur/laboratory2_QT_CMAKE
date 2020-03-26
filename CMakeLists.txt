cmake_minimum_required(VERSION 3.15)

project(Laboratory2 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDART 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#Чтобы найти пакеты Qt5
set(CMAKE_PREFIX_PATH "C:\\Qt\\5.13.0\\msvc2017_64")

find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(project_headers 
	include/ClassUnit.h
	include/MethodUnit.h
	include/PrintUnit.h
	include/Configuration.h
	include/Unit.h

	include/CPP/CPP_ClassUnit.h
)

set(project_sources 
	src/main.cpp
	src/ClassUnit.cpp
	src/MethodUnit.cpp
	src/PrintUnit.cpp

	include/CPP/CPP_ClassUnit.cpp
)

add_executable(${PROJECT_NAME}
	${project_headers}
	${project_sources}
)

target_link_libraries(${PROJECT_NAME} 
	PUBLIC 
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
)