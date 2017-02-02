#include "HPCCSQLParserBaseListener.h"
#include "jlib.hpp"

class HPCCSQLListener: public HPCCSQLParserBaseListener, public CInterface, public IInterface
{
public:
    IMPLEMENT_IINTERFACE;

public:
    void enterSelect(HPCCSQLParser::SelectContext * ctx);
};
