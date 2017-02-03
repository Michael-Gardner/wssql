#include "MySQLParserBaseListener.h"
#include "jlib.hpp"

class HPCCSQLListener: public MySQLParserBaseListener, public CInterface, public IInterface
{
public:
    IMPLEMENT_IINTERFACE;

public:
    void enterSelect_statement(MySQLParser::Select_statementContext * ctx);
    void enterSelect_expression(MySQLParser::Select_expressionContext * ctx);
    
    void enterSelect_list(MySQLParser::Select_listContext * ctx);
    void enterTable_references(MySQLParser::Table_referencesContext * ctx);




};
