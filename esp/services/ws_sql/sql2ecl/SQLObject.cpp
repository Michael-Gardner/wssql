/*
 * SQLObject.cpp
 *
 *  Created on: Feb 2, 2017
 *      Author: michael
 */

#include <SQLObject.hpp>
#include <iostream> //Debug only

SQLObject::SQLObject() {
	statementType = Unknown;
	fieldList.clear();
}


SQLObject::~SQLObject() {
#if defined _DEBUG
    fprintf(stderr, "\nDestroying sql object\n");
#endif
    fieldList.clear();
}

void SQLObject::addField(StringBufferItem& _fieldEntry) {
	std::cout << "addField((StringBufferItem&)" << _fieldEntry << ")" << std::endl;
	fieldList.appendUniq(_fieldEntry);
}

void SQLObject::addField(const char * _fieldEntry) {
	std::cout << "addField((const char *)" << _fieldEntry << ")" << std::endl;
	StringBufferItem val = StringBufferItem(_fieldEntry);
	addField(val);
}

void SQLObject::setType(SQLStatementType _type) {
	statementType = _type;
}

StringBuffer SQLObject::toString() {
	StringBuffer output = StringBuffer();
	output.append("statementType: ");
	switch(statementType) {
	case Unknown: 		output.append("Unknown\n");
						break;
	case Select:		output.append("Select\n");
						break;
	case Call:			output.append("Call\n");
						break;
	case CreateAndLoad:	output.append("CreateAndLoad\n");
						break;
	}
	output.appendf("fieldList: %i\n",fieldList.length());
	ForEachItemIn(idx,fieldList)
		output.appendf("\t%s\n",fieldList.item(idx).str());
	return output;
}
