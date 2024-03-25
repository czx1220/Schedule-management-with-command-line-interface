cmake_minimum_required(VERSION 3.10)
project(schedule)
add_executable(schedule main.cpp mainstructure.h mainstructure.cpp account.h account.cpp tasksave.h tasksave.cpp) 
target_link_libraries(schedule libpthread.so)
