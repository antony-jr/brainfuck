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

add_executable(brainfuck src/main.c
			 include/stack.h
			 src/stack.c)

target_link_libraries(brainfuck PUBLIC m)
target_include_directories(brainfuck PUBLIC . include)

install(
	TARGETS brainfuck
	RUNTIME DESTINATION bin
)