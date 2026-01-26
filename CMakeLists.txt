cmake_minimum_required(VERSION 3.16)

project(qt_file_modifier LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_executable(qt_file_modifier
  main.cpp
  fm_worker.cpp fm_worker.h

  fm_control_widget.h fm_control_widget.cpp

  file_modifier.h file_modifier.cpp
  fm_file_process_widget.h fm_file_process_widget.cpp

)
target_link_libraries(qt_file_modifier PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(qt_file_modifier PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

include(GNUInstallDirs)
install(TARGETS qt_file_modifier
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
