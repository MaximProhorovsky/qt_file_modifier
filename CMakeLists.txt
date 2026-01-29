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
  src/main.cpp
  src/file_worker.cpp include/file_worker.h
  include/widgets/control_widget.h src/widgets/control_widget.cpp
  include/main_window.h src/main_window.cpp
  include/widgets/process_widget.h src/widgets/process_widget.cpp
  include/widgets/dir_input_widget.h src/widgets/dir_input_widget.cpp
  include/widgets/text_input_widget.h src/widgets/text_input_widget.cpp
  include/setting.h
)
target_link_libraries(qt_file_modifier PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(qt_file_modifier PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(qt_file_modifier PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/src
)

include(GNUInstallDirs)
install(TARGETS qt_file_modifier
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
