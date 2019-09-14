CMAKE_MINIMUM_REQUIRED( VERSION 2.8)
project(brainfuck)

# Let cmake know that this is a release build.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_C_FLAGS "-Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O3")

# Include Directories.
include_directories(.)
include_directories(include)

if(GIT_COMMIT_STR)
	add_definitions(-DGIT_COMMIT_STR="${GIT_COMMIT_STR}")
endif()

add_executable(brainfuck src/stack.c
			 src/executor.c
			 src/parser.c
			 src/interpreter.c
			 src/main.c
			 include/stack.h
			 include/executor.h
			 include/parser.h
			 include/interpreter.h)

target_link_libraries(brainfuck PUBLIC edit)
target_include_directories(brainfuck PUBLIC . include)

install(
	TARGETS brainfuck
	RUNTIME DESTINATION bin
)
