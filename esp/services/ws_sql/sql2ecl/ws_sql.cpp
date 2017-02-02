#include <iostream>

#include "antlr4-runtime.h"
#include "HPCCSQLLexer.h"
#include "HPCCSQLParser.h"
#include "HPCCSQLListener.hpp"

using namespace antlr4;

int main(int,const char **)
{
	ANTLRInputStream input("select column1 from table1;");
	HPCCSQLLexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	
	tokens.fill();
	for (auto token : tokens.getTokens())
		std::cout << token->toString() << std::endl;

	HPCCSQLParser parser(&tokens);
	tree::ParseTree * tree = parser.select();
	
	std::cout << tree->toStringTree(&parser) << std::endl;

	return 0;
}
