#include "HPCCSQLListener.hpp"
#include <iostream>

void HPCCSQLListener::enterSelect_statement(MySQLParser::Select_statementContext * ctx)
{
    std::cout << "in statement :: " << ctx->getText() << std::endl;
}

void HPCCSQLListener::enterSelect_expression(MySQLParser::Select_expressionContext * ctx)
{
    std::cout << "in select expression :: " << ctx->getText() << std::endl;
}

void HPCCSQLListener::enterSelect_list(MySQLParser::Select_listContext * ctx)
{
    std::cout << "in select list :: " << ctx->getText() << std::endl;
}

void HPCCSQLListener::enterTable_references(MySQLParser::Table_referencesContext * ctx)
{
    std::cout << "in table references:: " << ctx->getText() << std::endl;
}
