################################################################################
#    HPCC SYSTEMS software Copyright (C) 2014 HPCC Systems.
#
#    Licensed under the Apache License, Version 2.0 (the "License");
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
# Component: ws_sql
#####################################################
# Description:
# ------------
#    Cmake Input File for ws_sql
#####################################################

project(ws_sql)

# Java and ANTLR needed for generating lexer and parser
find_package(Java REQUIRED)
find_package(ANTLR4CPP REQUIRED)
find_package(ANTLR REQUIRED)

#include(${HPCC_WSSQL_SOURCE_DIR}/esp/scm/additional.cmake)

include(${CMAKE_MODULE_PATH}/generateLexerAndParser.cmake)
set(SQL2ECL "${CMAKE_CURRENT_SOURCE_DIR}/sql2ecl")

message(STATUS "ANTLR4_GENERATED_SOURCE = ${ANTLR4_GENERATED_SOURCE}")
message(STATUS "ANTLR4_GENERATED_HEADER = ${ANTLR4_GENERATED_HEADER}")
message(STATUS "ANTLR4CPP_INCLUDE_DIRS  = ${ANTLR4CPP_INCLUDE_DIRS}")
message(STATUS "ANTLR4CPP_LIBRARIES     = ${ANTLR4CPP_LIBRARIES}")

set(SRCS
    ${SQL2ECL}/wssql_test.cpp
    ${SQL2ECL}/HPCCSQLListener.cpp
    ${SQL2ECL}/SQLObject.cpp
    ${ANTLR4_GENERATED_SOURCE}
    )

message(STATUS "SOURCES                 = ${SRCS}")

set(INCLUDES
    ${ANTLR4_GENRATED_HEADER}
    )

include_directories(
    ${HPCC_SOURCE_DIR}/system/include
    ${HPCC_SOURCE_DIR}/system/jlib
    ${SQL2ECL}
    ${ANTLR4CPP_INCLUDE_DIRS}
    )


add_definitions(-D_USRDLL)

add_executable(wssql_test ${SRCS} ${INCLUDES})
install(TARGETS wssql_test
    RUNTIME DESTINATION ${EXEC_DIR}
    LIBRARY DESTINATION ${LIB_DIR}
    COMPONENT Runtime
    )

add_dependencies(wssql_test
    antlr-generated-listener
    )

target_link_libraries(wssql_test
    jlib
    ${ANTLR4CPP_LIBRARIES}
    )
