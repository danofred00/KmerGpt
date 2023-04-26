cmake_minimum_required(VERSION 3.16)

# create project
project(KmerGpt
    VERSION 0.1
    LANGUAGES CXX
    DESCRIPTION "Your Ai based on ChatGpt3.5 API"
)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# find packages
find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

# add executables files
qt_add_executable(appKmerGpt
    main.cpp
    resources.qrc
)

set_target_properties(appKmerGpt PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# link differents lib to our project
target_link_libraries(appKmerGpt
    PRIVATE Qt6::Quick
)

# install the app
install(TARGETS appKmerGpt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
