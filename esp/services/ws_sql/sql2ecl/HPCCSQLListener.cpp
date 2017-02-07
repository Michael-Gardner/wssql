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


void HPCCSQLListener::enterColumn_field_name(
		MySQLParser::Column_field_nameContext * ctx) {
	StringBufferItem sbi = StringBufferItem();
	if(ctx->schema_name())
		sbi.appendf("%s.",ctx->schema_name()->getText().c_str());
	if(ctx->table_name())
		sbi.appendf("%s.",ctx->table_name()->getText().c_str());
	if(ctx->ASTERISK())
		sbi.append("*");
	else
		sbi.appendf("%s",ctx->column_name()->getText().c_str());
	if(ctx->alias())
		sbi.appendf(" %s",ctx->alias()->getText().c_str());
	std::cout << "sbi == " << sbi << std::endl;
	sqlObject.addField(sbi);
}
