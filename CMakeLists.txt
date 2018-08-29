cmake_minimum_required(VERSION 3.10)
project(lastchance C)

set(CMAKE_C_STANDARD 90)

add_executable(lastchance RunAssembler.c File.c File.h Globals.c Globals.h FirstPhase.c FirstPhase.h HashTable.c HashTable.h)