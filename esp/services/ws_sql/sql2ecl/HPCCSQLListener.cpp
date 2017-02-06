#include "HPCCSQLListener.hpp"
#include "MySQLLexer.h"
#include "MySQLParser.h"
#include <iostream>

using namespace antlr4;

SQLObject HPCCSQLListener::getSQL() {
	return sqlObject;
}

void HPCCSQLListener::enterSelect_statement(
		MySQLParser::Select_statementContext * ctx) {
    sqlObject.statementType = Select;
}

void HPCCSQLListener::enterCall_statement(
		MySQLParser::Call_statementContext* ctx) {
	sqlObject.statementType = Call;
}

void HPCCSQLListener::enterCreate_database_statement(
		MySQLParser::Create_database_statementContext* ctx) {
	sqlObject.statementType = CreateAndLoad;
}

void HPCCSQLListener::enterTable_spec(MySQLParser::Table_specContext * ctx) {
	tree::ParseTree * pctx = ctx->parent;
	std::cout << "tspec -> " << pctx->toString() << std::endl;
}

void HPCCSQLListener::enterDisplayed_column(
		MySQLParser::Displayed_columnContext* ctx) {
	if(ctx->ASTERISK())
		std::cout << "TODO:: enterDisplayed_column().asterisk() :: " << ctx->getText() << std::endl;
	else if(ctx->column_spec()) {
		sqlObject.addField(ctx->column_spec()->getText().c_str());
	} else if(ctx->table_spec())
		std::cout << "Table_spec found " << ctx->table_spec()->getText() << std::endl;
	else if (ctx->alias())
		std::cout << "Alias found " << ctx->alias()->getText() << std::endl;
	else if (ctx->bit_expr())
		std::cout << "bit_expr found " << ctx->bit_expr()->getText() << std::endl;
	else
		std::cout << "ERROR: found nothing at " << ctx->getText() << std::endl;
}
