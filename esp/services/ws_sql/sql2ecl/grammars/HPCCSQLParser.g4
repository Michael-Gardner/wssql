
parser grammar HPCCSQLParser;

options
   { tokenVocab = HPCCSQLLexer; }

statement:
	select from (conditional)?
	| insert into (conditional)?
;

select:	TOKEN_SELECT column;

insert:	TOKEN_INSERT column;

into: TOKEN_INTO table;
from: TOKEN_FROM table;

conditional: if_rule | where;
where: TOKEN_WHERE expression;
if_rule: TOKEN_IF expression;

expression:
    column (TOKEN_GREATER_THAN
            |TOKEN_LESS_THAN
            |TOKEN_GREATER_OR_EQUAL
            |TOKEN_LESS_OR_EQUAL
			|TOKEN_EQUAL)
    TOKEN_INT ((TOKEN_OR|TOKEN_AND) expression)?
;


table: TOKEN_ID;
column:	TOKEN_ID;
