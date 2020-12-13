cmake_minimum_required(VERSION 3.9)

project(KP)

#set(CMAKE_CXX_FLAGS "-Wall -fPIC -std=c++17")  for Qt5
set(CMAKE_CXX_STANDARD 17)            
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR YES)
set(CMAKE_AUTOMOC ON)

find_package(SFML REQUIRED COMPONENTS system window graphics)
find_package(Qt5Gui CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)



if(WIN32)
   find_package(Tesseract CONFIG REQUIRED)
endif(WIN32)
   
if(UNIX AND NOT APPLE)
   #find_package(SFML REQUIRED COMPONENTS system window graphics)
   #find_package(Qt5Gui CONFIG REQUIRED)
   #find_package(Qt5Widgets CONFIG REQUIRED)
   find_package(Qt5Core CONFIG REQUIRED)
endif(UNIX AND NOT APPLE)


add_executable(main
${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/ui.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/drawer.cpp)


target_include_directories(main
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

################### Linux  ###############################
if(UNIX AND NOT APPLE)
 target_compile_options(main PRIVATE -fPIC)
 include_directories(${Tesseract_INCLUDE_DIRS})
 include_directories(${Qt5Gui_INCLUDE_DIRS})
 include_directories(${Qt5Widgets_INCLUDE_DIRS})
 include_directories(${Qt5Core_INCLUDE_DIRS})
 include_directories(sfml-system sfml-window sfml-graphics)

 target_link_libraries(main PRIVATE ${Leptonica_LIBRARIES})
 target_link_libraries(main PRIVATE ${Tesseract_LIBRARIES})
 target_link_libraries(main PRIVATE ${SFML_LIBRARIES})
 target_link_libraries(main -llept -ltesseract -lQt5Widgets -lQt5Gui -lQt5Core -lsfml-graphics -lsfml-window -lsfml-system)
 endif(UNIX AND NOT APPLE)

################### WIN ##################################

if(WIN32) 
 target_link_libraries(main PRIVATE libtesseract)
 target_link_libraries(main PRIVATE sfml-system sfml-window sfml-graphics)
 target_link_libraries(main PRIVATE ${Qt5Widgets_LIBRARIES})
 ##?#target_link_libraries(main PRIVATE ${Qt5Gui_LIBRARIES})
 target_link_libraries(main PRIVATE ${Qt5Gui_LIBRARIES})

endif(WIN32)