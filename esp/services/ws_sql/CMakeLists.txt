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
    ${SQL2ECL}/ws_sql.cpp
	${SQL2ECL}/HPCCSQLListener.cpp
    ${ANTLR4_GENERATED_SOURCE}
    )

message(STATUS "SOURCES                 = ${SRCS}")

set(INCLUDES
    ${ANTLR4_GENRATED_HEADER}
    )

include_directories(
    #added for build-config.h
    ${CMAKE_BINARY_DIR}
    #added for build-config.h
    ${CMAKE_BINARY_DIR}/oss
    ${HPCC_SOURCE_DIR}/esp/bindings
    ${HPCC_SOURCE_DIR}/esp/bindings/SOAP/xpp
    ${HPCC_SOURCE_DIR}/esp/smc/SMCLib
    ${HPCC_SOURCE_DIR}/esp/platform
    ${HPCC_SOURCE_DIR}/esp/services
    ${HPCC_SOURCE_DIR}/esp/services/ws_ecl
    ${HPCC_SOURCE_DIR}/esp/services/ws_workunits
    ${HPCC_SOURCE_DIR}/esp/services/ws_dfu
    ${HPCC_SOURCE_DIR}/system/xmllib
    ${HPCC_SOURCE_DIR}/system/include
    ${HPCC_SOURCE_DIR}/system/jlib
    ${HPCC_SOURCE_DIR}/system/security/shared
    ${HPCC_SOURCE_DIR}/system/security/securesocket
    ${HPCC_SOURCE_DIR}/system/security/zcrypt
    ${HPCC_SOURCE_DIR}/system/mp
    ${HPCC_SOURCE_DIR}/dali/dfu
    ${HPCC_SOURCE_DIR}/dali/base/
    ${HPCC_SOURCE_DIR}/common/workunit
    ${HPCC_SOURCE_DIR}/common/remote
    ${HPCC_SOURCE_DIR}/common/environment
    ${HPCC_SOURCE_DIR}/common/wuwebview
    ${HPCC_SOURCE_DIR}/common/fileview2
    ${HPCC_SOURCE_DIR}/common/dllserver
    ${HPCC_SOURCE_DIR}/common/deftype
    ${HPCC_SOURCE_DIR}/ecl/hql
	${SQL2ECL}
    ${ANTLR4CPP_INCLUDE_DIRS}
    )

add_definitions(-D_USRDLL)

add_executable(ws_sql ${SRCS} ${INCLUDES})
install(TARGETS ws_sql
    RUNTIME DESTINATION ${EXEC_DIR}
    LIBRARY DESTINATION ${LIB_DIR}
    COMPONENT Runtime
    )

add_dependencies(ws_sql
    antlr-generated-listener
    )

target_link_libraries(ws_sql
    jlib
	${ANTLR4CPP_LIBRARIES}
    )
