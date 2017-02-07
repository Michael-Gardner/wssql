#include <iostream>

#include "antlr4-runtime.h"
#include "MySQLLexer.h"
#include "MySQLParser.h"
#include "HPCCSQLListener.hpp"
#include "SQLObject.hpp"

using namespace antlr4;

int main(int,const char **)
{
	std::string query = "select my.own.food as dinner, amanda.rose.kalmutz gardner from tab, bob, foo;";
	ANTLRInputStream input(query);
	MySQLLexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	
	tokens.fill();
	for (auto token : tokens.getTokens())
		std::cout << token->toString() << std::endl;

	MySQLParser parser(&tokens);
	HPCCSQLListener * listener = new HPCCSQLListener();

	tree::ParseTree * tree = parser.select_statement();
	tree::ParseTreeWalker::DEFAULT.walk(listener,tree);
	
	std::cout << tree->toStringTree(&parser) << std::endl;

	SQLObject sqlObject = listener->getSQL();

	if(!sqlObject.isAlive())
		std::cout << "Warning! sqlObject doesn't exist" << std::endl;
	std::cout << "printing out sqlObject" << std::endl;
	std::cout << sqlObject.toString() << std::endl;
	std::cout << "finishing" << std::endl;

	return 0;
}
