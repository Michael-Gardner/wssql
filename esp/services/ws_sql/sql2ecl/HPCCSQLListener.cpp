#include "HPCCSQLListener.hpp"
#include <iostream>

void HPCCSQLListener::enterStatement(HPCCSQLParser::StatementContext * ctx)
{
    std::cout << "in statement :: " << ctx->getText() << std::endl;
}

void HPCCSQLListener::enterSelect(HPCCSQLParser::SelectContext * ctx)
{
    std::cout << "in select :: " << ctx->getText() << std::endl;
}

void HPCCSQLListener::enterColumn(HPCCSQLParser::ColumnContext * ctx)
{
    std::cout << "in column :: " << ctx->getText() << std::endl;
}

void HPCCSQLListener::enterFrom(HPCCSQLParser::FromContext * ctx)
{
    std::cout << "in from :: " << ctx->getText() << std::endl;
}

void HPCCSQLListener::enterTable(HPCCSQLParser::TableContext * ctx)
{
    std::cout << "in table :: " << ctx->getText() << std::endl;
}
