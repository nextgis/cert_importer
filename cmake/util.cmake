################################################################################
# Project:  NextGIS GIS libraries
# Purpose:  CMake build scripts
# Author:   Dmitry Baryshnikov, polimax@mail.ru
################################################################################
# Copyright (C) 2015-2019, NextGIS <info@nextgis.com>
# Copyright (C) 2015-2019 Dmitry Baryshnikov
#
# This script is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# This script is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this script.  If not, see <http://www.gnu.org/licenses/>.
################################################################################

function(check_version major minor patch)
    set(VERSION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/util.cmake)

    set(VER_MAJOR 1)
    set(VER_MINOR 0)
    set(VER_PATCH 0)

    set(${major} ${VER_MAJOR} PARENT_SCOPE)
    set(${minor} ${VER_MINOR} PARENT_SCOPE)
    set(${patch} ${VER_PATCH} PARENT_SCOPE)

    # Store version string in file for installer needs
    file(TIMESTAMP ${VERSION_FILE} VERSION_DATETIME "%Y-%m-%d %H:%M:%S" UTC)
    set(VERSION ${VER_MAJOR}.${VER_MINOR}.${VER_PATCH})
    get_cpack_filename(${VERSION} PROJECT_CPACK_FILENAME)
    file(WRITE ${CMAKE_BINARY_DIR}/version.str "${VERSION}\n${VERSION_DATETIME}\n${PROJECT_CPACK_FILENAME}")
endfunction(check_version)


function(report_version name ver)

    string(ASCII 27 Esc)
    set(BoldYellow  "${Esc}[1;33m")
    set(ColourReset "${Esc}[m")

    message("${BoldYellow}${name} version ${ver}${ColourReset}")

endfunction()

function(get_prefix prefix IS_STATIC)
  if(IS_STATIC)
    set(STATIC_PREFIX "static-")
      if(ANDROID)
        set(STATIC_PREFIX "${STATIC_PREFIX}android-${ANDROID_ABI}-")
      elseif(IOS)
        set(STATIC_PREFIX "${STATIC_PREFIX}ios-${IOS_ARCH}-")
      endif()
    endif()
  set(${prefix} ${STATIC_PREFIX} PARENT_SCOPE)
endfunction()


function(get_cpack_filename ver name)
    get_compiler_version(COMPILER)
    
    if(NOT DEFINED BUILD_STATIC_LIBS)
      set(BUILD_STATIC_LIBS OFF)
    endif()

    get_prefix(STATIC_PREFIX ${BUILD_STATIC_LIBS})

    set(${name} ${PROJECT_NAME}-${ver}-${STATIC_PREFIX}${COMPILER} PARENT_SCOPE)
endfunction()

function(get_compiler_version ver)
    ## Limit compiler version to 2 or 1 digits
    string(REPLACE "." ";" VERSION_LIST ${CMAKE_C_COMPILER_VERSION})
    list(LENGTH VERSION_LIST VERSION_LIST_LEN)
    if(VERSION_LIST_LEN GREATER 2 OR VERSION_LIST_LEN EQUAL 2)
        list(GET VERSION_LIST 0 COMPILER_VERSION_MAJOR)
        list(GET VERSION_LIST 1 COMPILER_VERSION_MINOR)
        set(COMPILER ${CMAKE_C_COMPILER_ID}-${COMPILER_VERSION_MAJOR}.${COMPILER_VERSION_MINOR})
    else()
        set(COMPILER ${CMAKE_C_COMPILER_ID}-${CMAKE_C_COMPILER_VERSION})
    endif()

    if(WIN32)
        if(CMAKE_CL_64)
            set(COMPILER "${COMPILER}-64bit")
        endif()
    endif()

    # Debug
    # set(COMPILER Clang-9.0)

    set(${ver} ${COMPILER} PARENT_SCOPE)
endfunction()
