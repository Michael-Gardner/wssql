#ifndef ESP_SERVICES_WS_SQL_SQL2ECL_HPCCSQLLISTENER_HPP_
#define ESP_SERVICES_WS_SQL_SQL2ECL_HPCCSQLLISTENER_HPP_

#include <SQLObject.hpp>
#include "MySQLParserBaseListener.h"
#include "jlib.hpp"

class HPCCSQLListener: public MySQLParserBaseListener, public CInterface, public IInterface
{
public:
    IMPLEMENT_IINTERFACE;

private:
    SQLObject sqlObject;

public:
    SQLObject getSQL();

    void enterSelect_statement(MySQLParser::Select_statementContext * ctx);
    void enterCall_statement(MySQLParser::Call_statementContext * ctx);
    void enterCreate_database_statement(MySQLParser::Create_database_statementContext * ctx);
    void enterDisplayed_column(MySQLParser::Displayed_columnContext * ctx);
    void enterTable_spec(MySQLParser::Table_specContext * ctx);

};
#endif /* ESP_SERVICES_WS_SQL_SQL2ECL_HPCCSQLLISTENER_HPP_ */
