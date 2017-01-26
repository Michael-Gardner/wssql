set(GRAMMAR_DIR "${CMAKE_SOURCE_DIR}/esp/services/ws_sql/SQL2ECL/grammars")
set(OUTPUT_DIR "${CMAKE_SOURCE_DIR}/esp/services/ws_sql/SQL2ECL")
set(ANTLR4_GRAMMAR_LEXER "SQLLexer.g4")
set(ANTLR4_GRAMMAR_PARSER "SQLParser.g4")

set(ANTLR4_GENERATED_SOURCE
	MySQLLexer.cpp
	MySQLParser.cpp
	MySQLParserBaseListener.cpp
	MySQLParserListener.cpp
)
set(ANTLR4_GENERATED_HEADER
	MySQLLexer.h
	MySQLParser.h
	MySQLParserBaseListener.h
	MySQLParserListener.h
)

set(ANTLR4_GENERATED_MISC
	MySQLParser.tokens
	MySQLLexer.tokens
)

find_package(Java REQUIRED)
find_package(ANTLR REQUIRED)
	
add_custom_command(OUTPUT ${ANTLR4_GENERATED_SOURCE} ${ANTLR4_GENERATED_HEADER} ${ANTLR4_GENERATED_MISC}
	COMMAND ${Java_JAVA_EXECUTABLE} "-jar" ${ANTLR_BUILDTIME_JAR} "-Dlanguage=Cpp" ${GRAMMAR_DIR}/${ANTLR4_GRAMMAR_LEXER} ${GRAMMAR_DIR}/${ANTLR4_GRAMMAR_PARSER} "-o" ${OUTPUT_DIR}
	COMMENT "Generating ANTLR4 Lexer, Parser, and Listeners from grammars"
)
add_custom_target(antlr-generated-listener
	DEPENDS ${ANTLR4_GENERATED_SOURCE} ${ANTLR4_GENERATED_HEADER} ${ANTLR4_GENERATED_MISC}
)

mark_as_advanced(ANTLR4_GENERATED_SOURCE ANTLR4_GENERATED_HEADER ANTLR4_GENERATED_MISC)
