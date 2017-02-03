/*
 * SQLObject.cpp
 *
 *  Created on: Feb 2, 2017
 *      Author: michael
 */

#include <SQLObject.hpp>

SQLObject::SQLObject() {
}


SQLObject::~SQLObject() {
#if defined _DEBUG
    fprintf(stderr, "\nDestroying sql object\n");
#endif
}
