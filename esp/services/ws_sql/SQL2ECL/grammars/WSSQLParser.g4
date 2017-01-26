
parser grammar WSSQLParser;

options
   { tokenVocab = WSSQLLexer; }

statement:
	select from (conditional)?
	| insert into (conditional)?
;

select:	SELECT column;
column: ID;

insert:	INSERT column;
column:	ID;
