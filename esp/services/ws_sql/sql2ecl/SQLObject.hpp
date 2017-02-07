/*
 * SQLObject.hpp
 *
 *  Created on: Feb 2, 2017
 *      Author: michael
 */

#ifndef ESP_SERVICES_WS_SQL_SQL2ECL_SQLOBJECT_HPP_
#define ESP_SERVICES_WS_SQL_SQL2ECL_SQLOBJECT_HPP_

#include <string>
#include <jiface.hpp>
#include <jscm.hpp>
#include <jstring.hpp>
#include <jlib.hpp>

typedef enum _SQLStatementType {
	Unknown=-1,
	Select,
	Call,
	CreateAndLoad
} SQLStatementType;

class SQLObject: public IInterface, public CInterface {
public:
	IMPLEMENT_IINTERFACE;
	SQLStatementType statementType;

private:
    StringBufferArray fieldList;
    StringBufferArray tableList;

public:
    SQLObject();
	virtual ~SQLObject();
	void addField(StringBuffer & s);
	void addField(const char * _fieldEntry);
	void addTable(StringBuffer & s);
	void addTable(const char * _tableEntry);
	void setType(SQLStatementType _type);
	StringBuffer toString();
};

#endif /* ESP_SERVICES_WS_SQL_SQL2ECL_SQLOBJECT_HPP_ */
