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
	StringBuffer s = StringBuffer();
	if(ctx->schema_name())
		s.appendf("%s.",ctx->schema_name()->getText().c_str());
	if(ctx->table_name())
		s.appendf("%s.",ctx->table_name()->getText().c_str());
	if(ctx->ASTERISK())
		s.append("*");
	else
		s.appendf("%s",ctx->column_name()->getText().c_str());
	if(ctx->alias())
		if(ctx->alias()->AS_SYM())
			s.appendf(" %s",ctx->alias()->AS_SYM()->getText().c_str());
		s.appendf(" %s",ctx->alias()->ID()->getText().c_str());
	sqlObject.addField(s.str());
}

void HPCCSQLListener::enterColumn_field_expr(
		MySQLParser::Column_field_exprContext * ctx) {
	StringBuffer s = StringBuffer();
	// TODO: bit expressions
	sqlObject.addField(s.str());
}

void HPCCSQLListener::enterTable_reference(
		MySQLParser::Table_referenceContext * ctx) {
	StringBuffer s = StringBuffer(ctx->table_atom()->table_spec()->getText().c_str());
	sqlObject.addTable(s);
}
