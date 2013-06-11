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
set (SPDPV_VERSION_MAJOR 2)
set (SPDPV_VERSION_MINOR 2)
set (SPDPV_VERSION_PATCH 0)
set (SPDPV_VERSION "${SPDPV_VERSION_MAJOR}.${SPDPV_VERSION_MINOR}.${SPDPV_VERSION_PATCH}")
set (SPDPV_PACKAGE_VERSION "${SPDPV_VERSION_MAJOR}.${SPDPV_VERSION_MINOR}.${SPDPV_VERSION_PATCH}")
set (SPDPV_PACKAGE_STRING "SPDPV ${SPDPV_VERSION_MAJOR}.${SPDPV_VERSION_MINOR}.${SPDPV_VERSION_PATCH}")
set (SPDPV_PACKAGE_BUGREPORT "spdlib-develop@lists.sourceforge.net")
set (SPDPV_PACKAGE "SPDPointsViewer")
set (SPDPV_PACKAGE "SPDPY")

set(SPDLIB_IO_INCLUDE_DIR /usr/local/include CACHE PATH "Include PATH for SPDLibIO")
set(SPDLIB_IO_LIB_PATH /usr/local/lib CACHE PATH "Library PATH for SPDLibIO")

set(HDF5_INCLUDE_DIR /usr/local/include CACHE PATH "Include PATH for HDF5")
set(HDF5_LIB_PATH /usr/local/lib CACHE PATH "Library PATH for HDF5")

set(SPDPV_APP SPDPointsViewer)
###############################################################################

###############################################################################
# CMake settings
cmake_minimum_required(VERSION 2.6.0)

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
        if (MSVC80 OR MSVC90 OR MSVC10)
            add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
            add_definitions(-D_CRT_SECURE_NO_WARNINGS)
            add_definitions(-D_CRT_NONSTDC_NO_WARNING)
            add_definitions(-D_SCL_SECURE_NO_WARNINGS)
        endif()
        
        if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
            string(REGEX REPLACE "/W[0-4]" "/W4"
                   CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
        endif()

        # Generate dot-user file with user-specific settings for Visual Studio project
        set(MSVC_ENVIRONMENT_PATH "" CACHE STRING
            "Custom PATH for Environment property in Visual Studio project configuration")
        mark_as_advanced(MSVC_ENVIRONMENT_PATH)
        set(VCPROJ_USER_ENVIRONMENT_PATH_DEBUG "${ENVIRONMENT_PATH}")
        mark_as_advanced(VCPROJ_USER_ENVIRONMENT_PATH_DEBUG)

    endif()

	set(CMAKE_INCLUDE_PATH c:/osgeo4w/include;$ENV{CMAKE_INCLUDE_PATH})
    set(CMAKE_LIBRARY_PATH c:/osgeo4w/lib;$ENV{CMAKE_LIBRARY_PATH})
else()
  # Recommended C++ compilation flags
  # -Weffc++
  set(SPDPV_COMMON_CXX_FLAGS
	"-pipe -ansi -Wall -Wpointer-arith -Wcast-align -Wcast-qual -Wredundant-decls -Wno-long-long")
	#"-pedantic -ansi -Wall -Wpointer-arith -Wcast-align -Wcast-qual -Wfloat-equal -Wredundant-decls -Wno-long-long")

  if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC ${SPDPV_COMMON_CXX_FLAGS}")
    if (CMAKE_COMPILER_IS_GNUCXX)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98")
    endif()

  elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" OR "${CMAKE_CXX_COMPILER}" MATCHES "clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SPDPV_COMMON_CXX_FLAGS}")
  endif()
endif(WIN32)

IF( APPLE )
    SET( PROGNAME SPDPointsViewer )
	SET( MACOSX_BUNDLE_BUNDLE_NAME SPDPointsViewer)
	SET( MACOSX_BUNDLE_INFO_STRING "SPD Points Viewer")
    SET( MACOSX_BUNDLE_ICON_FILE SPDPointsViewer.icns )
	SET( MACOSX_FILE_ICON_FILE SPD.icns )
    SET( MACOSX_BUNDLE_SHORT_VERSION_STRING 2.01-beta1 )
    SET( MACOSX_BUNDLE_BUNDLE_VERSION 2.01-beta1 )
    SET( MACOSX_BUNDLE_LONG_VERSION_STRING Version 2.01-beta1 )
    SET( CMAKE_OSX_ARCHITECTURES x86_64 ) #Comment out if not universal binary
	SET( MACOSX_BUNDLE_COPYRIGHT "Copyright Pete Bunting")
	SET( MACOSX_BUNDLE_GUI_IDENTIFIER "org.spdlib.spdpointsviewer") 
  ELSE( APPLE )
    SET( PROGNAME SPDPointsViewer )
  ENDIF( APPLE )
###############################################################################

###############################################################################
# Check the required libraries are present

FIND_PACKAGE(Boost)
IF(Boost_FOUND)
  INCLUDE_DIRECTORIES("${Boost_INCLUDE_DIRS}")
  SET(Boost_USE_STATIC_LIBS OFF)
  SET(Boost_USE_MULTITHREADED ON)
  SET(Boost_USE_STATIC_RUNTIME OFF)
ELSEIF(NOT Boost_FOUND)
  MESSAGE(FATAL_ERROR "Unable to find correct Boost version. Did you set BOOST_ROOT?")
ENDIF()

find_package( GDAL 1.6.0 REQUIRED )
if (GDAL_FOUND)
	include_directories (${GDAL_INCLUDE_DIR})
endif(GDAL_FOUND)

set(QT_USE_OPENGL TRUE)

FIND_PACKAGE( Qt4 REQUIRED )
if (QT4_FOUND)
	include_directories (${QT4_INCLUDE_DIR})
endif(QT4_FOUND)

if(QT_QTOPENGL_FOUND)
	set(OPENGL_FOUND)
	#set(QTLocal_OPENGL_INCLUDE_DIR ${QT_OPENGL_INCLUDE_DIR})
	include_directories (${QT_QTOPENGL_INCLUDE_DIR})
	#set(QTLocal_OPENGL_LIBRARIES ${QT_QTOPENGL_LIBRARY})
else (QT_QTOPENGL_FOUND)
	FindPackage(OpenGL)
endif (QT_QTOPENGL_FOUND)

INCLUDE( ${QT_USE_FILE} )

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
	include_directories (${OPENGL_INCLUDE_DIR})
endif(OPENGL_FOUND)

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

SET( SPDPV_MOC_HDRS
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

QT4_WRAP_CPP( SPDPV_MOC_SRCS ${SPDPV_MOC_HDRS} )

INCLUDE_DIRECTORIES( ${CMAKE_BINARY_DIR} )

IF( APPLE )
  ADD_EXECUTABLE( ${PROGNAME} MACOSX_BUNDLE ${SPDPV_SRCS} ${SPDPV_HDRS} ${SPDPV_MOC_SRCS} )
#  ADD_CUSTOM_COMMAND( TARGET ${PROGNAME} POST_BUILD
#    COMMAND mkdir ARGS ${CMAKE_CURRENT_BINARY_DIR}/Debug/${PROGNAME}.app/Contents/Resources
#    COMMAND cp ARGS ${MACOSX_BUNDLE_ICON_FILE} ${CMAKE_CURRENT_BINARY_DIR}/Debug/${PROGNAME}.app/Contents/Resources
#    COMMAND cp ARGS ${MACOSX_FILE_ICON_FILE} ${CMAKE_CURRENT_BINARY_DIR}/Debug/${PROGNAME}.app/Contents/Resources )
elseif(WIN32)
  ADD_EXECUTABLE( ${PROGNAME} WIN32 ${SPDPV_SRCS} ${SPDPV_HDRS} ${SPDPV_MOC_SRCS} )
ELSE()
  ADD_EXECUTABLE( ${PROGNAME} ${SPDPV_SRCS} ${SPDPV_HDRS} ${SPDPV_MOC_SRCS} )
ENDIF( APPLE )

TARGET_LINK_LIBRARIES( ${PROGNAME} ${QT_LIBRARIES} ${QT_QTOPENGL_LIBRARY} ${SPDLIB_LIBRARY} ${GDAL_LIBRARY} ${GLUT_LIBRARY} ${OPENGL_LIBRARY})

###############################################################################
# Installation
install(TARGETS ${PROGNAME} DESTINATION bin PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

###############################################################################
# Create Distribution
SET(CPACK_SOURCE_GENERATOR "TGZ;ZIP;TBZ2")
SET(CPACK_CMAKE_GENERATOR "Unix Makefiles")

set(CPACK_SOURCE_PACKAGE_FILE_NAME
  "${CMAKE_PROJECT_NAME}-${SPDPV_VERSION_MAJOR}.${SPDPV_VERSION_MINOR}.${SPDPV_VERSION_PATCH}")

# Set files to ignore
list(APPEND CPACK_SOURCE_IGNORE_FILES "_CPack_Packages")
list(APPEND CPACK_SOURCE_IGNORE_FILES ".gz")
list(APPEND CPACK_SOURCE_IGNORE_FILES ".bz2")
list(APPEND CPACK_SOURCE_IGNORE_FILES ".zip")
list(APPEND CPACK_SOURCE_IGNORE_FILES ".svn")
list(APPEND CPACK_SOURCE_IGNORE_FILES "README")
list(APPEND CPACK_SOURCE_IGNORE_FILES "HOWTORELEASE.txt")
list(APPEND CPACK_SOURCE_IGNORE_FILES "CMakeCache.txt")
list(APPEND CPACK_SOURCE_IGNORE_FILES "CPackConfig.cmake")
list(APPEND CPACK_SOURCE_IGNORE_FILES "schemas")

include(CPack)

add_custom_target(dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)
###############################################################################
