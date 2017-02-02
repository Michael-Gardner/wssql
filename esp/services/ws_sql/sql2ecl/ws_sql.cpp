#include <iostream>

#include "antlr4-runtime.h"
#include "HPCCSQLLexer.h"
#include "HPCCSQLParser.h"
#include "HPCCSQLListener.hpp"

using namespace antlr4;

int main(int,const char **)
{
	ANTLRInputStream input("select col from tab;");
	HPCCSQLLexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	
	tokens.fill();
	for (auto token : tokens.getTokens())
		std::cout << token->toString() << std::endl;

	HPCCSQLParser parser(&tokens);
	HPCCSQLListener * listener = new HPCCSQLListener();

	tree::ParseTree * tree = parser.statement();
	tree::ParseTreeWalker::DEFAULT.walk(listener,tree);
	
	//std::cout << tree->toStringTree(&parser) << std::endl;

	return 0;
}
