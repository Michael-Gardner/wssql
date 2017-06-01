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
find_package(ANTLR REQUIRED)
find_package(ANTLR3C)

# TODO: currently ANTLR3c to ANTLR3C will cause issues
if(NOT ANTLR3C_FOUND)
    message(STATUS "Antlr3c not found")
    include(${HPCC_WSSQL_SOURCE_DIR}/cmake_modules/BuildANTLR3C.cmake)
endif()

include(${HPCC_WSSQL_SOURCE_DIR}/esp/scm/additional.cmake)
set(o_PLATFORM ${PLATFORM})
set(PLATFORM OFF)
include(${HPCC_SOURCE_DIR}/esp/scm/espscm.cmake)
set(PLATFORM ${o_PLATFORM})
unset(o_PLATFORM)
set(HPCC_SQL_PARSER_LOCATION ${HPCC_WSSQL_SOURCE_DIR}/esp/services/ws_sql/SQL2ECL)
set(HPCC_SQL_PARSER_GRAMMAR_PATH ${HPCC_SQL_PARSER_LOCATION}/ANTLR3c)
set(HPCC_SQL_PARSER_GRAMMAR_NAME HPCCSQL.g)

#sample command
#java -jar antlr-3.4-complete.jar -o /home/hpccuser/GIT/HPCC-Platform/esp/services/ws_sql/SQL2ECL/ -report -traceTreeParser /usr/local/eclipse/workspaces/antlr/mysql/HPCCSQL.g

#The actual java command to generate lexer and parser
set(ANTLR3_COMMAND ${Java_JAVA_EXECUTABLE} "-jar" ${ANTLR_BUILDTIME_JAR} ${HPCC_SQL_PARSER_GRAMMAR_PATH}/${HPCC_SQL_PARSER_GRAMMAR_NAME} "-o" ${HPCC_SQL_PARSER_LOCATION})

#The lexer and parser targets
set(ANTLR_GENERATED_LEXER  ${HPCC_SQL_PARSER_LOCATION}/HPCCSQLLexer.c)
set(ANTLR_GENERATED_PARSER ${HPCC_SQL_PARSER_LOCATION}/HPCCSQLParser.c)
set_property(SOURCE ${ANTLR_GENERATED_LEXER} ${ANTLR_GENERATED_PARSER} PROPERTY GENERATED TRUE)

#Create the ANTLR generated c targeted lexer and parser
add_custom_command(
    OUTPUT ${ANTLR_GENERATED_LEXER} ${ANTLR_GENERATED_PARSER}
    COMMAND ${ANTLR3_COMMAND}
    )
add_custom_target(generate-lexer-parser
    DEPENDS ${ANTLR_GENERATED_LEXER} ${ANTLR_GENERATED_PARSER}
    )

set(SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/ws_sqlPlugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ws_sqlService.cpp
    ${ESPSCM_GENERATED_DIR}/common_esp.cpp
    ${ESPSCM_GENERATED_DIR}/ws_sql_esp.cpp
    ${ESPSCM_GENERATED_DIR}/ws_workunits_esp.cpp
    ${ESPSCM_GENERATED_DIR}/ws_topology_esp.cpp
    ${HPCC_SOURCE_DIR}/esp/services/ws_ecl/ws_ecl_wuinfo.cpp
    ${HPCC_SOURCE_DIR}/esp/services/ws_workunits/ws_workunitsHelpers.cpp
    ${HPCC_SQL_PARSER_LOCATION}/HPCCFileCache.cpp
    ${HPCC_SQL_PARSER_LOCATION}/HPCCFile.cpp
    ${HPCC_SQL_PARSER_LOCATION}/ECLFunction.cpp
    ${HPCC_SQL_PARSER_LOCATION}/ECLEngine.cpp
    ${HPCC_SQL_PARSER_LOCATION}/SQLColumn.cpp
    ${HPCC_SQL_PARSER_LOCATION}/SQLTable.hpp
    ${HPCC_SQL_PARSER_LOCATION}/SQLExpression.cpp
    ${HPCC_SQL_PARSER_LOCATION}/SQLJoin.cpp
    ${HPCC_SQL_PARSER_LOCATION}/HPCCSQLTreeWalker.cpp
    ${ANTLR_GENERATED_LEXER}
    ${ANTLR_GENERATED_PARSER}
    )

include_directories(
    ##added for build-config.h
    ${CMAKE_BINARY_DIR}
    ##added for build-config.h
    ${CMAKE_BINARY_DIR}/oss
    ${HPCC_WSSQL_SOURCE_DIR}/esp/services/ws_sql/SQL2ECL
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
    ${HPCC_SOURCE_DIR}/system/security/LdapSecurity
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
    ${ANTLR3C_INCLUDE_DIR}
    ${ESPSCM_GENERATED_DIR}
    )

add_definitions(-D_USRDLL)
add_library(ws_sql SHARED ${SRCS})
add_dependencies(ws_sql espscm wssqlespscm generate-lexer-parser)
target_link_libraries(
    ws_sql
    ws_dfu
    jlib
    xmllib
    esphttp
    securesocket
    dalibase
    ${ANTLR3C_LIBRARY}
    wuwebview    
    )

if(NOT ANTLR3C_FOUND)
    add_dependencies(ws_sql libantlr3c-generate)
    install(CODE "set(ENV{LD_LIBRARY_PATH} \"\$ENV{LD_LIBRARY_PATH}:${PROJECT_BINARY_DIR}:${CMAKE_BINARY_DIR}/ANTLR3C/.libs\")")
endif()

install(TARGETS ws_sql RUNTIME DESTINATION ${EXEC_DIR} LIBRARY DESTINATION ${LIB_DIR} COMPONENT Runtime)
