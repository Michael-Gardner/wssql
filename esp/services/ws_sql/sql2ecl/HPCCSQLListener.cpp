#include "HPCCSQLListener.hpp"
#include <iostream>

void HPCCSQLListener::enterSelect(HPCCSQLParser::SelectContext * ctx)
{
    std::cout << "in select statement" << std::endl;
}
