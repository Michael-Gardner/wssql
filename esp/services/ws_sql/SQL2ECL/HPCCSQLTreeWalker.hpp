/*##############################################################################

HPCC SYSTEMS software Copyright (C) 2014 HPCC Systems.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
############################################################################## */

#ifndef HPCCSQLTREEWALKER_HPP_
#define HPCCSQLTREEWALKER_HPP_
#include <stdlib.h>
#include "ws_sql.hpp"

/* undef SOCKET definitions to avoid collision in Antlrdefs.h*/
#ifdef INVALID_SOCKET
    //#pragma message("UNDEFINING INVALID_SOCKET - Will be redefined by ANTLRDEFS.h" )
    #undef INVALID_SOCKET
#endif
#ifdef SOCKET
    //#pragma message( "UNDEFINING SOCKET - Will be redefined by ANTLRDEFS.h" )
    #undef SOCKET
#endif
/* undef SOCKET definitions to avoid collision in Antlrdefs.h*/

#include "HPCCSQLLexer.h"
#include "HPCCSQLParser.h"
#include "HPCCSQLParserBaseVisitor.h"

#include "antlr4-runtime.h"
#include "SQLColumn.hpp"
#include "SQLTable.hpp"
#include "SQLExpression.hpp"
#include "HPCCFile.hpp"
#include "HPCCFileCache.hpp"
#include "ECLFunction.hpp"
#include "SQLJoin.hpp"

using namespace antlr4;
using namespace antlr4::tree;

typedef enum _SQLQueryType
{
    SQLTypeUnknown=-1,
    SQLTypeSelect,
    SQLTypeCall,
    SQLTypeCreateAndLoad
} SQLQueryType;

class jlib_decl HPCCSQLTreeWalker: 	public HPCCSQLParserBaseVisitor,
									public CInterface,
									public IInterface
{
public:
    IMPLEMENT_IINTERFACE;

private:
    HPCCSQLParser::Root_statementContext * rootTree;
    SQLQueryType sqlType;
    IArrayOf<ISQLExpression> selectList;
    IArrayOf<ISQLExpression> groupbyList;
    IArrayOf<ISQLExpression> orderbyList;
    IArrayOf<SQLTable>       tableList;

    int parameterizedCount;
    int limit;
    int offset;
    bool selectDistinct;
    bool overwrite;

    StringBuffer indexhint;
    Owned<ISQLExpression> whereClause;
    Owned<ISQLExpression> havingClause;
    Owned<HPCCFileCache>  tmpHPCCFileCache;

    StringBuffer procedureName;
    StringBuffer querySetName;
    IArrayOf<ISQLExpression> paramList;
    StringBuffer tableName;
    StringBuffer sourceDataTableName;
    StringBuffer comment;
    StringBuffer sourceDataType;
    StringBuffer landingZoneIP;
    StringBuffer landingZonePath;
    StringBuffer recordDefinition;
    StringBuffer normalizedSQL;

    void sqlTreeWalker();
    void selectStatementTreeWalker(HPCCSQLParser::Select_statementContext * ctx);
    void callStatementTreeWalker(HPCCSQLParser::Call_statementContext * ctx);
    void createAndLoadStatementTreeWalker(HPCCSQLParser::Create_load_table_statementContext * ctx);
    void columnListTreeWalker(HPCCSQLParser::Column_listContext * ctx, IArrayOf<SQLColumn>& collist);
    ISQLExpression* expressionTreeWalker(HPCCSQLParser::ExpressionContext * ectx, ParseTree * pctx);
    void fromTreeWalker(HPCCSQLParser::From_portionContext * ctx);
    void limitTreeWalker(HPCCSQLParser::Limit_clauseContext * ctx);
    void processAllColumns(HpccFiles *  availableFiles);
    void verifyColumn(SQLFieldValueExpression * col );
    void verifyColAndDisambiguateName();
    void verifyAndDisambiguateNameFromList(IArrayOf<ISQLExpression> * explist);
    void assignParameterIndexes();

    //override visitor elements
	antlrcpp::Any visitSelect_statement(HPCCSQLParser::Select_statementContext * ctx);
	antlrcpp::Any visitTable_reference(HPCCSQLParser::Table_referenceContext * ctx);
	antlrcpp::Any visitSelect_item(HPCCSQLParser::Select_itemContext * ctx);
	antlrcpp::Any visitExpressionList(HPCCSQLParser::ExpressionListContext * ctx);
	antlrcpp::Any visitBinaryExpression(HPCCSQLParser::BinaryExpressionContext * ctx);
	antlrcpp::Any visitUnaryExpression(HPCCSQLParser::UnaryExpressionContext * ctx);
	antlrcpp::Any visitRelational_op(HPCCSQLParser::Relational_opContext * ctx);
	antlrcpp::Any visitLiteralValueExpression(HPCCSQLParser::LiteralValueExpressionContext * ctx);
	antlrcpp::Any visitLiteral_value(HPCCSQLParser::Literal_valueContext * ctx);
	antlrcpp::Any visitString_literal(HPCCSQLParser::String_literalContext * ctx);
	antlrcpp::Any visitBoolean_literal(HPCCSQLParser::Boolean_literalContext * ctx);
	antlrcpp::Any visitNumber_literal(HPCCSQLParser::Number_literalContext * ctx);
	antlrcpp::Any visitHex_literal(HPCCSQLParser::Hex_literalContext * ctx);
	antlrcpp::Any visitExpression(HPCCSQLParser::ExpressionContext * ctx);
	antlrcpp::Any visitColumnSpecExpression(HPCCSQLParser::ColumnSpecExpressionContext * ctx);
	antlrcpp::Any visitColumn_spec(HPCCSQLParser::Column_specContext * ctx);
	antlrcpp::Any visitOrderby_item(HPCCSQLParser::Orderby_itemContext * ctx);

public:

    bool isParameterizedCall();
    void setQuerySetName(const char * qsname)
    {
        querySetName.set(qsname);
    }

    const char * getQuerySetName()
    {
        return querySetName.str();
    }

    const char * getStoredProcName()
    {
        return procedureName.str();
    }

    int getStoredProcParamListCount()
    {
        return paramList.length();
    }

    IArrayOf<ISQLExpression>* getStoredProcParamList()
    {
        return &paramList;
    }

    void getWhereClauseString(StringBuffer & str);
    void getHavingClauseString(StringBuffer & str);
    ISQLExpression * getHavingClause();

    void expandWildCardColumn();
    HPCCSQLTreeWalker();
    HPCCSQLTreeWalker(HPCCSQLParser::Root_statementContext * tree, IEspContext &context);
    virtual ~HPCCSQLTreeWalker();

    int getParameterizedCount() const
    {
        return parameterizedCount;
    }

    const IArrayOf<SQLTable>* getTableList() const
    {
        return const_cast <const IArrayOf<SQLTable>*> (&tableList);
    }

    const IArrayOf<ISQLExpression>* getSelectList() const
    {
        return const_cast <const IArrayOf<ISQLExpression>*> (&selectList);
    }

    const IArrayOf<ISQLExpression>* getParamList() const
    {
        return const_cast <const IArrayOf<ISQLExpression>*> (&paramList);
    }

    int getLimit() const
    {
        return limit;
    }

    void setLimit(int limit)
    {
        this->limit = limit;
    }

    void setRootTree(HPCCSQLParser::Root_statementContext * tree)
    {
    	this->rootTree = tree;
    }

    int getOffset() const
    {
        return offset;
    }

    void setOffset(int _offset)
    {
        offset = _offset;
    }

    void setSqlType(SQLQueryType type)
    {
        sqlType = type;
    }

    SQLQueryType getSqlType()
    {
        return sqlType;
    }

    bool hasGroupByColumns()
    {
        return !groupbyList.empty();
    }

    bool hasOrderByColumns()
    {
        return !orderbyList.empty();
    }

    bool hasHavingClause()
    {
        return havingClause != NULL;
    }

    bool hasWhereClause()
    {
        return whereClause != NULL;
    }

    bool isSelectDistinct()
    {
        return selectDistinct;
    }

    void getOrderByString(StringBuffer & str)
    {
        getOrderByString(',', str);
    }

    void getOrderByString(char delimiter, StringBuffer & str)
    {
        int orderbycount = orderbyList.length();
        for (int i = 0; i < orderbycount; i++)
        {
            ISQLExpression* ordercol = &orderbyList.item(i);
            SQLFieldValueExpression* colexp = dynamic_cast<SQLFieldValueExpression*>(ordercol);
            str.append(colexp->isAscending() ? "" : "-");
            str.append(colexp->getNameOrAlias());
            if (i != orderbycount - 1)
                str.append(delimiter);
        }
    }

    void getGroupByString(StringBuffer & str)
    {
        getGroupByString(',', str);
    }

    void getGroupByString(char delimiter, StringBuffer & str)
    {
        int groupbycount = groupbyList.length();
        for (int i = 0; i < groupbycount; i++)
        {
            ISQLExpression * ordercol =  &groupbyList.item(i);
            SQLFieldValueExpression * colexp = dynamic_cast<SQLFieldValueExpression *>(ordercol);
            str.append(colexp->getName());
            if (i != groupbycount - 1)
                str.append(delimiter);
        }
    }

    ISQLExpression * getWhereClause()
    {
        return whereClause.get();
    }

    HPCCFileCache * queryHPCCFileCache()
    {
        return tmpHPCCFileCache.get();
    }

    const char* getNormalizedSQL();

    const char * getRecordDefinition()
    {
        return recordDefinition.str();
    }

    void setRecordDefinition(const char * _recordDefinition)
    {
        recordDefinition.set(_recordDefinition);
    }

    const char *  getComment() const
    {
        return comment.str();
    }

    void setComment(const char * _comment)
    {
        comment.set(_comment);
    }

    const char * getLandingZoneIp() const
    {
        return landingZoneIP.str();
    }

    void setLandingZoneIp(const char * _landingZoneIp)
    {
        landingZoneIP.set(_landingZoneIp);
    }

    const char * getLandingZonePath() const
    {
        return landingZonePath.str();
    }

    void setLandingZonePath(const char * _landingZonePath)
    {
        landingZonePath.set(_landingZonePath);
    }

    const char * getSourceDataType() const
    {
        return sourceDataType.str();
    }

    void setSourceDataType(const char * _sourceDataType)
    {
        sourceDataType.set(_sourceDataType);
    }

    bool isOverwrite() const
    {
        return overwrite;
    }

    void setOverwrite(bool _overwrite)
    {
        overwrite = _overwrite;
    }

    const char * getSourceDataTableName() const
    {
        return sourceDataTableName.str();
    }

    void setSourceDataTableName(const char * _sourceDataTableName)
    {
        sourceDataTableName.set(_sourceDataTableName);
    }

    const char * getTableName() const
    {
        return tableName.str();
    }

    void setTableName(const char * _tableName)
    {
        tableName.set(_tableName);
    }

private:

    bool normalizeSQL();
};

#endif /* HPCCSQLTREEWALKER_HPP_ */
