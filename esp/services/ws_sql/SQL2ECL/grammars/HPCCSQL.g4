grammar HPCCSQL;

options
{
  language=Cpp;
}

statement
:
	SELECT id FROM location
;

id
:
	ID_CHAR+
;

location
:
	LOC_CHAR+
;

SELECT
:
	'select'
;

FROM
:
	'from'
;

ID_CHAR
:
	[a-zA-Z]
;

LOC_CHAR
:
	[a-zA-Z_\\-:]
;

WS: [ \t\n\r] -> skip;
