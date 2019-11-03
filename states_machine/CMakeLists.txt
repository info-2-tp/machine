cmake_minimum_required(VERSION 3.10)

# set the project name
project(StatesMachine)

# add the executable
add_executable(Machine src/main.c src/actions.c src/states.c src/events.c)