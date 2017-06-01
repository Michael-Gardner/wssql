################################################################################
#    HPCC SYSTEMS software Copyright(C) 2013 HPCC Systems.
#
#    Licensed under the Apache License, Version 2.0(the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
################################################################################
#
# - Try to find the ANTLR 3 c library
# Once done this will define
#
#  ANTLR3C_INCLUDE_DIR - The ANTLR3C include directory
#  ANTLR3C_LIBRARIES   - The libraries needed to use ANTLR3C
################################################################################

if(WIN32)
    set(ANTLR3C_LIB "antlr3c.lib")
else()
    set(ANTLR3C_LIB "libantlr3c.so")
endif()
message(STATUS "Building ${ANTLR3C_LIB}")

if(NOT ANTLR3C_VER)
    set(ANTLR3C_VER "3.4")
endif()
message(STATUS "Target ANTLR3C Version: ${ANTLR3C_VER}")

set(ANTLR3C_CONFIGURE_COMMAND_PARAMS "--silent" "--disable-antlrdebug")

if(UNIX)
    if(${ARCH64BIT} EQUAL 1)
        set(ANTLR3C_CONFIGURE_COMMAND_PARAMS ${ANTLR3C_CONFIGURE_COMMAND_PARAMS} "--enable-64bit")
        set(OSDIR "x86_64-linux-gnu")
    else()
        set(OSDIR "i386-linux-gnu")
    endif()
elseif(WIN32)
    set(OSDIR "lib")
else()
    set(OSDIR "unknown")
endif()

set(ANTLR3C_PACKAGENAME "libantlr3c-${ANTLR3C_VER}")
set(ANTLR3C_PACKAGE ${ANTLR3C_PACKAGENAME}.tar.gz)
set(ANTLR3_URL "http://www.antlr3.org")
set(ANTLR3C_DOWNLOAD_URL ${ANTLR3_URL}/download/C/${ANTLR3C_PACKAGE})
set(ANTLR3C_SOURCE_DIR ${CMAKE_BINARY_DIR}/ANTLRC)
set(ANTLR3C_LIBRARY_DIR ${ANTLR3C_SOURCE_DIR}/.lib)
set(ANTLR3C_INCLUDE_DIR ${ANTLR3C_SOURCE_DIR}/include CACHE PATH "libantr3c header files" FORCE)
set(ANTLR3C_LICENSE_URL "https://raw.github.com/antlr/antlr4/master/LICENSE.txt")

include(ExternalProject)
ExternalProject_Add(
    libantlr3c-generate
    URL ${ANTLR3C_DOWNLOAD_URL}
    DOWNLOAD_NO_PROGRESS 0
    SOURCE_DIR ${ANTLR3C_SOURCE_DIR}
    CONFIGURE_COMMAND ./configure ${ANTLR3C_CONFIGURE_COMMAND_PARAMS} --prefix=${ANTLR3C_SOURCE_DIR}
    BUILD_COMMAND $(MAKE)
    BUILD_IN_SOURCE 1
    INSTALL_COMMAND ""
    )
ExternalProject_Add_Step(
    libantlr3c-generate
    libantlr3c-license
    COMMAND wget --no-check-certificate -O ${ANTLR3C_SOURCE_DIR}/ANTLR-LICENSE.txt ${ANTLR3C_LICENSE_URL}
    DEPENDEES build
    BYPRODUCTS ${ANTLR3C_SOURCE_DIR}/ANTLR-LICENSE.txt
    WORKING_DIRECTORY ${ANTLR3C_SOURCE_DIR}
    )

add_library(libantlr3c SHARED IMPORTED GLOBAL)
set_property(TARGET libantlr3c PROPERTY IMPORTED_LOCATION ${ANTLR3C_LIBRARY_DIR}/libantlr3c.so)
add_dependencies(libantlr3c libantlr3c-generate)
set(ANTLR3C_LIBRARY libantlr3c CACHE STRING "libantlr3c library target" FORCE)

install(FILES ${ANTLR3C_SOURCE_DIR}/ANTLR-LICENSE.txt DESTINATION libs COMPONENT Runtime)
install(FILES ${ANTLR3C_LIBRARY_DIR}/libantlr3c.so DESTINATION libs COMPONENT Runtime)
