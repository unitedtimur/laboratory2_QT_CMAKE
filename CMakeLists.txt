cmake_minimum_required(VERSION 3.15)

project(Laboratory2 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDART 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(project_headers 
	include/Unit.h
	include/ClassUnit.h
	include/MethodUnit.h
	include/PrintUnit.h
	include/Configuration.h
	include/Tests.h

	include/AbstractFactory.h
	
	# CPP
	include/CPP/CPP_ClassUnit.h
	include/CPP/CPP_MethodUnit.h
	include/CPP/CPP_PrintUnit.h
	include/CPP/CPP_AbstractFactory.h

	# CSHARP
	include/CSHARP/CSHARP_ClassUnit.h
	include/CSHARP/CSHARP_MethodUnit.h
	include/CSHARP/CSHARP_PrintUnit.h
	include/CSHARP/CSHARP_AbstractFactory.h

	# JAVA
	include/JAVA/JAVA_ClassUnit.h
	include/JAVA/JAVA_MethodUnit.h
	include/JAVA/JAVA_PrintUnit.h
	include/JAVA/JAVA_AbstractFactory.h
)

set(project_sources 
	src/main.cpp
	src/Tests.cpp
)

add_executable(${PROJECT_NAME}
	${project_headers}
	${project_sources}
)