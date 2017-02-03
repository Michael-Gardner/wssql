/*
 * SQLObject.hpp
 *
 *  Created on: Feb 2, 2017
 *      Author: michael
 */

#ifndef ESP_SERVICES_WS_SQL_SQL2ECL_SQLOBJECT_HPP_
#define ESP_SERVICES_WS_SQL_SQL2ECL_SQLOBJECT_HPP_

#include <jiface.hpp>
#include <jscm.hpp>
#include <jstring.hpp>
#include <jlib.hpp>

class SQLObject: public IInterface, public CInterface {
	class SQLStatement;

public:
	IMPLEMENT_IINTERFACE;
private:
    IArrayOf<SQLStatement> selectList;

public:
	SQLObject();
	virtual ~SQLObject();
	bool addStatement(StringBuffer _type, StringBuffer _statement);


private:
	class SQLStatement {
	private:
		typedef enum _SQLStatementType {
			Unknown=-1,
			Select,
			Call,
			CreateAndLoad
		} SQLStatementType;

		SQLStatementType type;
		StringBuffer original;
		StringBuffer normalization;

	public:
		SQLStatement(StringBuffer _type, StringBuffer _original) {
			original = _original;
			if(!strcmp(_type,"Select"))
				type = Select;
			else if(!strcmp(_type,"Call"))
				type = Call;
			else if(!strcmp(_type,"CreateAndLoad"))
				type = CreateAndLoad;
			else
				type = Unknown;
			normalization = SQLStatement::Normalization(original);
		}
	private:
		static StringBuffer Normalization(StringBuffer _original) {
			return _original;
		}
	};
};

#endif /* ESP_SERVICES_WS_SQL_SQL2ECL_SQLOBJECT_HPP_ */
