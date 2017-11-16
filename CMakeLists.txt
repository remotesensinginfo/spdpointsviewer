###############################################################################
#
# CMake build scripts for SPDPointsViewer
# 
# Created 2011/03/12 by Peter Bunting
#
# These scripts were initial based on those used for SPDLib
#
# History
# 2011/03/12 - Created by Peter Bunting
#
###############################################################################

###############################################################################
# Set Project name and version
project (SPDPointsViewer)

set (PROJECT_SOURCE_DIR src)
#set (PROJECT_HEADER_DIR include)

# The version number.
set (SPDPV_VERSION_MAJOR 3)
set (SPDPV_VERSION_MINOR 0)
set (SPDPV_VERSION_PATCH 0)
set (SPDPV_VERSION "${SPDPV_VERSION_MAJOR}.${SPDPV_VERSION_MINOR}.${SPDPV_VERSION_PATCH}")
set (SPDPV_PACKAGE_VERSION "${SPDPV_VERSION_MAJOR}.${SPDPV_VERSION_MINOR}.${SPDPV_VERSION_PATCH}")
set (SPDPV_PACKAGE_STRING "SPDPV ${SPDPV_VERSION_MAJOR}.${SPDPV_VERSION_MINOR}.${SPDPV_VERSION_PATCH}")
set (SPDPV_PACKAGE_BUGREPORT "spdlib-develop@lists.sourceforge.net")
set (SPDPV_PACKAGE "SPDPointsViewer")
set (SPDPV_PACKAGE "SPDPV")

set(SPDLIB_IO_INCLUDE_DIR /usr/local/include CACHE PATH "Include PATH for SPDLibIO")
set(SPDLIB_IO_LIB_PATH /usr/local/lib CACHE PATH "Library PATH for SPDLibIO")

set(HDF5_INCLUDE_DIR /usr/local/include CACHE PATH "Include PATH for HDF5")
set(HDF5_LIB_PATH /usr/local/lib CACHE PATH "Library PATH for HDF5")

set(BOOST_INCLUDE_DIR /usr/local/include CACHE PATH "Include PATH for Boost")
set(BOOST_LIB_PATH /usr/local/lib CACHE PATH "Library PATH for Boost")

set(GDAL_INCLUDE_DIR /usr/local/include CACHE PATH "Include PATH for GDAL")
set(GDAL_LIB_PATH /usr/local/lib CACHE PATH "Library PATH for GDAL")

#set(QT5_INCLUDE_DIR /usr/local/include CACHE PATH "Include PATH for GDAL")
#set(QT5_LIB_PATH /usr/local/lib CACHE PATH "Library PATH for GDAL")

set(SPDPV_APP SPDPointsViewer)
###############################################################################

###############################################################################
# CMake settings
cmake_minimum_required(VERSION 2.8.11)

IF(NOT CMAKE_BUILD_TYPE)
  #SET(CMAKE_BUILD_TYPE "DEBUG")
  SET(CMAKE_BUILD_TYPE "RELEASE")
  #SET(CMAKE_BUILD_TYPE "RELWITHDEBINFO")
  #SET(CMAKE_BUILD_TYPE "MINSIZEREL")
ENDIF()

set(CMAKE_COLOR_MAKEFILE ON)

# Allow advanced users to generate Makefiles printing detailed commands
mark_as_advanced(CMAKE_VERBOSE_MAKEFILE)

# Path to additional CMake modules
set(CMAKE_MODULE_PATH ./cmake/modules ${CMAKE_MODULE_PATH})

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
###############################################################################

###############################################################################
# Documentation
file(READ "doc/index.txt" README )
file(WRITE "README.txt" "${README}")
###############################################################################

###############################################################################
# Platform and compiler specific settings

if(WIN32)
    if (MSVC)
        if (MSVC80 OR MSVC90 OR MSVC10 OR MSVC14)
            add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
            add_definitions(-D_CRT_SECURE_NO_WARNINGS)
            add_definitions(-D_CRT_NONSTDC_NO_WARNING)
            add_definitions(-D_SCL_SECURE_NO_WARNINGS)
        endif()
        
        if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
            string(REGEX REPLACE "/W[0-4]" "/W2"
                   CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W2")
        endif()

        # Generate dot-user file with user-specific settings for Visual Studio project
        set(MSVC_ENVIRONMENT_PATH "" CACHE STRING
            "Custom PATH for Environment property in Visual Studio project configuration")
        mark_as_advanced(MSVC_ENVIRONMENT_PATH)
        set(VCPROJ_USER_ENVIRONMENT_PATH_DEBUG "${ENVIRONMENT_PATH}")
        mark_as_advanced(VCPROJ_USER_ENVIRONMENT_PATH_DEBUG)
		
		# Use cmake's MSVC_VERSION to work out the name of the Boost/CGAL DLL's 
        # to use (they use a different numbering scheme from cmake)
        set(MSVC_STRING_1500 "vc90")
        set(MSVC_STRING_1600 "vc100")
        set(MSVC_STRING_1700 "vc110")
        set(MSVC_STRING_1800 "vc120")
        set(MSVC_STRING_1900 "vc140")
        set(MSVC_STRING ${MSVC_STRING_${MSVC_VERSION}})
        message(STATUS "Using MSVC String " ${MSVC_STRING})
    endif()

else()
  # Recommended C++ compilation flags
  set(SPDPV_COMMON_CXX_FLAGS "-Wall -Wpointer-arith -Wcast-align -Wcast-qual -Wredundant-decls -Wno-long-long -DNDEBUG")
  if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC ${SPDPV_COMMON_CXX_FLAGS}") 
    if (CMAKE_COMPILER_IS_GNUCXX)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -D_GLIBCXX_USE_CXX11_ABI=0")
    endif()   
  elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" OR "${CMAKE_CXX_COMPILER}" MATCHES "clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SPDPV_COMMON_CXX_FLAGS}")
  endif()
endif(WIN32)

#IF( APPLE )
#    SET( PROGNAME SPDPointsViewer )
#	SET( MACOSX_BUNDLE_BUNDLE_NAME SPDPointsViewer)
#	SET( MACOSX_BUNDLE_INFO_STRING "SPD Points Viewer")
#    SET( MACOSX_BUNDLE_ICON_FILE SPDPointsViewer.icns )
#	SET( MACOSX_FILE_ICON_FILE SPD.icns )
#    SET( MACOSX_BUNDLE_SHORT_VERSION_STRING 2.01-beta1 )
#    SET( MACOSX_BUNDLE_BUNDLE_VERSION 2.01-beta1 )
#    SET( MACOSX_BUNDLE_LONG_VERSION_STRING Version 2.01-beta1 )
#    SET( CMAKE_OSX_ARCHITECTURES x86_64 ) #Comment out if not universal binary
#	SET( MACOSX_BUNDLE_COPYRIGHT "Copyright Pete Bunting")
#	SET( MACOSX_BUNDLE_GUI_IDENTIFIER "org.spdlib.spdpointsviewer") 
#  ELSE( APPLE )
#    SET( PROGNAME SPDPointsViewer )
#  ENDIF( APPLE )
SET( PROGNAME SPDPointsViewer)
###############################################################################

###############################################################################
# Check the required libraries are present

if (MSVC)
    # Under Windows, the boost libs are strangely named - use glob to find them
    file(GLOB BOOST_FS_LIB ${BOOST_LIB_PATH}/libboost_filesystem-${MSVC_STRING}-*.lib )
    if(NOT BOOST_FS_LIB)
        message(FATAL_ERROR "Could not find boost_filesystem lib")
    endif()
    file(GLOB BOOST_SYS_LIB ${BOOST_LIB_PATH}/libboost_system-${MSVC_STRING}-*.lib )
    if(NOT BOOST_SYS_LIB)
        message(FATAL_ERROR "Could not find boost_system lib")
    endif()
    message(STATUS "Found boost libraries " ${BOOST_FS_LIB} ${BOOST_SYS_LIB})
    set(BOOST_LIBRARIES -LIBPATH:${BOOST_LIB_PATH} ${BOOST_FS_LIB} ${BOOST_SYS_LIB})
else()
    set(BOOST_LIBRARIES -L${BOOST_LIB_PATH} -lboost_filesystem -lboost_system)
endif(MSVC)

include_directories(${GDAL_INCLUDE_DIR})
if (MSVC)
  set(GDAL_LIBRARIES -LIBPATH:${GDAL_LIB_PATH} gdal_i.lib)
else()
  set(GDAL_LIBRARIES -L${GDAL_LIB_PATH} -lgdal)
endif(MSVC)

include_directories(${HDF5_INCLUDE_DIR})
if (MSVC)
    set(HDF5_LIBRARIES -LIBPATH:${HDF5_LIB_PATH} hdf5dll.lib hdf5_cppdll.lib)
else()
    set(HDF5_LIBRARIES -L${HDF5_LIB_PATH} -lhdf5 -lhdf5_hl -lhdf5_cpp)
endif(MSVC)

include_directories(${SPDLIB_IO_INCLUDE_DIR})
if(MSVC)
    set(SPDLIB_LIBRARY -LIBPATH:${SPDLIB_IO_LIB_PATH} libspdio.lib)
else()
    set(SPDLIB_LIBRARY -L${SPDLIB_IO_LIB_PATH} -lspdio )
endif(MSVC)

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
	include_directories(${OPENGL_INCLUDE_DIR})
endif(OPENGL_FOUND)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)

# Add the include directories for the Qt 5 modules to the compile lines.
include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Gui_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5OpenGL_INCLUDE_DIRS})

# Use the compile definitions defined in the Qt 5 modules
add_definitions(${Qt5Core_DEFINITIONS})
add_definitions(${Qt5Gui_DEFINITIONS})
add_definitions(${Qt5Widgets_DEFINITIONS})
add_definitions(${Qt5OpenGL_DEFINITIONS})

###############################################################################

###############################################################################
# Build Application

SET( SPDPV_SRCS
	./src/main.cpp 
	./src/SPDPointsViewerException.cpp 
	./src/SPDPointsViewer.cpp 
	./src/SPDPointsViewerColourTable.cpp
	./src/SPDPointsViewerCreateOverviewImage.cpp 
	./src/SPDPointsViewerApplication.cpp 
	./src/SPDPointsViewerOverviewWidget.cpp 
	./src/SPDPointsViewer3DWidget.cpp 
	./src/SPDPointsViewerPreferences.cpp 
	./src/SPDPointsViewerDisplayProfile.cpp 
	./src/SPDPointsViewerConvertDialog.cpp 
	./src/SPDPointsViewerControl.cpp 
	./src/SPDPointsViewerReadPTXTMeshFile.cpp 
	./src/SPDPointsViewerLoadOverviewImage.cpp 
	./src/SPDPointsViewerLoad3DData.cpp 
	./src/SPDPointsViewerSubsetDialog.cpp
)

SET( SPDPV_HDRS
	./src/SPDPointsViewerCommon.h
    ./src/SPDPointsViewerException.h
	./src/SPDPointsViewerCreateOverviewImage.h 
	./src/SPDPointsViewerReadPTXTMeshFile.h
	./src/SPDPointsViewerColourTable.h
	./src/SPDPointsViewer.h 
	./src/SPDPointsViewerApplication.h 
	./src/SPDPointsViewerOverviewWidget.h 
	./src/SPDPointsViewer3DWidget.h 
	./src/SPDPointsViewerPreferences.h 
	./src/SPDPointsViewerDisplayProfile.h 
	./src/SPDPointsViewerConvertDialog.h 
	./src/SPDPointsViewerControl.h 
	./src/SPDPointsViewerLoadOverviewImage.h 
	./src/SPDPointsViewerLoad3DData.h 
	./src/SPDPointsViewerSubsetDialog.h
)

INCLUDE_DIRECTORIES( ${CMAKE_BINARY_DIR} )

IF(WIN32)
  # make GUI rather than console (suppresses console window) and add icon
  ADD_EXECUTABLE( ${PROGNAME} WIN32 ${SPDPV_SRCS} ./src/SPDPointsViewer.rc)
ELSE()
  ADD_EXECUTABLE( ${PROGNAME} ${SPDPV_SRCS} ${SPDPV_HDRS} )
ENDIF( WIN32 )

TARGET_LINK_LIBRARIES( ${PROGNAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::OpenGL ${SPDLIB_LIBRARY} ${GDAL_LIBRARIES} ${BOOST_LIBRARIES} ${GLUT_LIBRARY} ${OPENGL_LIBRARY})

###############################################################################
# Installation
install(TARGETS ${PROGNAME} DESTINATION bin PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)