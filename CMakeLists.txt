cmake_minimum_required(VERSION 3.11)

# Set the project name. This is not the executable program's name!
project(dice)


# Here, the executable is declared with its sources. "main", or "main.exe" on windows will be the program's name
add_executable(
  dice
  src/main.c
)

target_include_directories(dice PUBLIC "./src")
