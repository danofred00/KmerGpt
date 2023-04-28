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
find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Core)
find_package(CURL REQUIRED)

option(CURL_STATIC_LINKING "Set to ON to build libcurl with static linking."  ON)

if(CURL_STATIC_LINKING)
    message("-DCURL_STATICLIB [added]")
    add_definitions(-DCURL_STATICLIB)
endif()

add_definitions(-DJSON_USE_IMPLICIT_CONVERSIONS=0)

qt_standard_project_setup()

set(SOURCES
    main.cpp openai.cpp
    logger.cpp chatrequest.cpp
)

set(HEADERS
    include/openai.h
    include/logger.h
    include/chatrequest.h
)

# add executables files
qt_add_executable(AppKmerGpt
    ${SOURCES} ${HEADERS}
    resources.qrc
)

# add 3rdparty files
target_include_directories(AppKmerGpt PUBLIC include)

#add curl
include_directories(${CURL_INCLUDE_DIRS})
target_link_libraries(AppKmerGpt PRIVATE ${CURL_LIBRARIES})
message("Using CURL Lib ${CURL_VERSION_STRING}")


set_target_properties(AppKmerGpt PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# link differents lib to our project
target_link_libraries(AppKmerGpt
    PRIVATE Qt6::Quick Qt6::Core
)

# install the app
install(TARGETS AppKmerGpt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
