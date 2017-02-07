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
	tableList.clear();
}

SQLObject::~SQLObject() {
#if defined _DEBUG
    fprintf(stderr, "\nDestroying sql object\n");
#endif
    fieldList.clear();
    tableList.clear();
}

void SQLObject::addField(StringBuffer& s) {
	fieldList.append(*new StringBufferItem(s));
}

void SQLObject::addField(const char * _fieldEntry) {
	StringBuffer field = StringBuffer(_fieldEntry);
	addField(field);
}

void SQLObject::addTable(StringBuffer& s) {
	tableList.append(*new StringBufferItem(s));
}

void SQLObject::addTable(const char * _tableEntry) {
	StringBuffer table = StringBuffer(_tableEntry);
	addField(table);
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
	ForEachItemIn(fdx,fieldList) {
		output.appendf("\t%s\n",fieldList.tos(fdx).str());
	}

	output.appendf("tableList: %i\n",tableList.length());
	ForEachItemIn(tdx,tableList) {
		output.appendf("\t%s\n",tableList.tos(tdx).str());
	}

	return output;
}
