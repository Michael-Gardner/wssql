################################################################################
#    HPCC SYSTEMS software Copyright (C) 2015 HPCC Systems.
#
#    Licensed under the Apache License, Version 2.0 (the "License")
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
# - Try to find the ANTLR 3 c library
# Once done this will define
#
#  ANTLR3C_FOUND       - System has the ANTLR3C library
#  ANTLR3C_INCLUDE_DIR - The ANTLR3C include directory
#  ANTLR3C_LIBRARY     - The libraries needed to use ANTLR3C
################################################################################


if(WIN32)
    set(LIB_NAME "antlr3c.lib")
    set(HEADER_NAME "antlr3.h")
else()
    set(LIB_NAME "antlr3c")
    set(HEADER_NAME "antlr3.h")
endif()

if(UNIX)
    if(${ARCH64BIT} EQUAL 1)
        set(OSDIR "x86_64-linux-gnu")
    else()
        set(OSDIR "i386-linux-gnu")
    endif()
elseif(WIN32)
    set(OSDIR "lib")
else()
    set(OSDIR "unknown")
endif()

find_path(ANTLR3C_INCLUDE_DIR NAMES ${HEADER_NAME} PATHS /usr/include)
find_library(ANTLR3C_LIBRARY NAMES ${LIB_NAME} PATHS /usr/lib /usr/lib/${OSDIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    ANTLR3C DEFAULT_MSG
    ANTLR3C_LIBRARY
    ANTLR3C_INCLUDE_DIR
    )

mark_as_advanced(ANTLR3C_INCLUDE_DIR ANTLR3C_LIBRARY)
