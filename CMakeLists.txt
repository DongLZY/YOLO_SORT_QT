project( Test_libtorch )
cmake_minimum_required( VERSION 3.0 )
set ( CMAKE_BUILD_TYPE Release )
# add_definitions ( -Wall )

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Gui Core REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# find opencv
find_package(OpenCV 4.4.0 REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
message(${OpenCV_INCLUDE_DIRS})


set ( HDRS
        widget.h
        cthread_video.h
        cv_detector.h
        tracker.h
        track.h
        munkres.h
        kalman_filter.h
        utils.h
        )

set ( SRCS
        main.cpp
        widget.cpp
        cthread_video.cpp
        cv_detector.cpp
        tracker.cpp
        track.cpp
        munkres.cpp
        kalman_filter.cpp
        )

set ( UIS
        widget.ui
        )


add_executable ( sort_qt  ${SRCS} ${CURRENT_SOURCE} ${CURRENT_HEADERS} ${UIS} ${TRS} ${MOCS} )
target_link_libraries ( sort_qt Qt5::Widgets Qt5::Core Qt5::Gui ${OpenCV_LIBS})


set_property(TARGET sort_qt PROPERTY CXX_STANDARD 14)
