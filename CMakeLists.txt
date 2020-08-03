 cmake_minimum_required(VERSION 2.8.12)
 project(openml)

 add_definitions("-std=c++11")

 include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
 conan_basic_setup()
 #set(CMAKE_BUILD_TYPE Debug)
 set(CMAKE_BUILD_TYPE RelWithDebInfo)

 #compiling to static library
 ADD_LIBRARY( OpenMLlib STATIC OpenML.h )
 
 SET_TARGET_PROPERTIES(OpenMLlib PROPERTIES LINKER_LANGUAGE CXX)
 target_link_libraries(OpenMLlib ${CONAN_LIBS})
 
 set( APP_EXE testing )
 add_executable(${APP_EXE} main.cc)
 target_link_libraries(${APP_EXE} OpenMLlib)
