#include "HPCCSQLParserBaseListener.h"
#include "jlib.hpp"

class HPCCSQLListener: public HPCCSQLParserBaseListener, public CInterface, public IInterface
{
public:
    IMPLEMENT_IINTERFACE;

public:
    void enterStatement(HPCCSQLParser::StatementContext * ctx);

    void enterSelect(HPCCSQLParser::SelectContext * ctx);
    void enterColumn(HPCCSQLParser::ColumnContext * ctx);
    
    void enterFrom(HPCCSQLParser::FromContext * ctx);
    void enterTable(HPCCSQLParser::TableContext * ctx);




};
