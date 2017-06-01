################################################################################
# Copyright(C)2013 HPCC Systems.
#
# All rights reserved. This program is free software: you can redistribute it
# and/or modify it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or(at your option)any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
################################################################################
#
# ANTLR_FOUND         - ANTLR found in local system
# ANTLR_BUILDTIME_JAR - needed to build/generate ANTLR Lexers and Parsers
# ANTLR_RUNTIME_JAR   - needed to build/generate ANTLR Lexers and Parsers
################################################################################


option(ANTLR_VER "ANTLR runtime and buildtime version.")
if(NOT ANTLR_VER)
    set(ANTLR_VER 3.4)
endif()

option(ANTLR_BUILDTIME_DEP "ANTLR buildtime jar file name.")
if(NOT ANTLR_BUILDTIME_DEP)
    set(ANTLR_BUILDTIME_DEP "antlr-${ANTLR_VER}-complete")
endif()

option(ANTLR_RUNTIME_DEP "ANTLR runtime jar file name.")
if(NOT ANTLR_RUNTIME_DEP)
    set(ANTLR_RUNTIME_DEP "antlr-runtime-${ANTLR_VER}")
endif()

option(ANTLR_PATH "Location of ANTLR runtime and buildtime jar files.")
if(NOT ANTLR_PATH)
    set(ANTLR_PATH "/usr/local/ANTLR/${ANTLR_VER}")
endif()

include(UseJava)
find_jar(ANTLR_RUNTIME_JAR ${ANTLR_RUNTIME_DEP} PATHS ${ANTLR_PATH})
find_jar(ANTLR_BUILDTIME_JAR ${ANTLR_BUILDTIME_DEP} PATHS ${ANTLR_PATH})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    ANTLR DEFAULT_MSG
    ANTLR_BUILDTIME_JAR
    ANTLR_RUNTIME_JAR
    )
mark_as_advanced(ANTLR_BUILDTIME_JAR ANTLR_RUNTIME_JAR)
