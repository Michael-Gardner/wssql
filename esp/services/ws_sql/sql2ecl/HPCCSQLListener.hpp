#ifndef ESP_SERVICES_WS_SQL_SQL2ECL_HPCCSQLLISTENER_HPP_
#define ESP_SERVICES_WS_SQL_SQL2ECL_HPCCSQLLISTENER_HPP_

#include <SQLObject.hpp>
#include "MySQLParserBaseListener.h"
#include "tree/ParseTreeProperty.h"
#include "jlib.hpp"

using namespace antlr4;
using namespace antlr4::tree;

class HPCCSQLListener: public MySQLParserBaseListener, public CInterface, public IInterface
{
public:
    IMPLEMENT_IINTERFACE;

private:
    ParseTreeProperty<StringBuffer> ptreeBuffer; // map w/ contexts as keys
    SQLObject sqlObject;


public:
    SQLObject getSQL();

    void enterSelect_statement(MySQLParser::Select_statementContext * ctx);
    void enterCall_statement(MySQLParser::Call_statementContext * ctx);
    void enterCreate_database_statement(MySQLParser::Create_database_statementContext * ctx);
    void enterColumn_field_name(MySQLParser::Column_field_nameContext * ctx);
    void enterColumn_field_expr(MySQLParser::Column_field_exprContext * ctx);
    void enterTable_reference(MySQLParser::Table_referenceContext * ctx);
};
#endif /* ESP_SERVICES_WS_SQL_SQL2ECL_HPCCSQLLISTENER_HPP_ */
