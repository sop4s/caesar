cmake_minimum_required(VERSION 3.10)

project(
  caesar
  VERSION 0.1
  LANGUAGES C
)

set(SOURCES 
  src/main.c)

add_executable(${PROJECT_NAME} ${SOURCES})
