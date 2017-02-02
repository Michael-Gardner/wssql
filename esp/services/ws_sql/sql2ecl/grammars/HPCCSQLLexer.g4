
lexer grammar HPCCSQLLexer;

// sql keywords
TOKEN_SELECT: S E L E C T;
TOKEN_INSERT: I N S E R T;
TOKEN_FROM: F R O M;
TOKEN_WHERE: W H E R E;
TOKEN_AS: A S;
TOKEN_IF: I F;
TOKEN_INTO: I N T O;
TOKEN_NULL: N U L L;

// logical operators
TOKEN_GREATER_THAN: '>';
TOKEN_GREATER_OR_EQUAL: '>=';
TOKEN_LESS_THAN: '<';
TOKEN_LESS_OR_EQUAL: '<=';
TOKEN_EQUAL: '==';
TOKEN_NOT_EQUAL: '!=';
TOKEN_AND: A N D | '&&';
TOKEN_OR: O R | '||';
TOKEN_ASTERISK: '*';
TOKEN_PLUS: '+';
TOKEN_MINUS: '-';
TOKEN_MOD: '%';
TOKEN_DIVIDE: '/';
TOKEN_NOT: N O T;
TOKEN_IN: I N;

TOKEN_SEMICOLON: ';';

TOKEN_ID:	('a'..'z'|'A'..'Z') ('a'..'z'|'A'..'Z'|'_'|'-'|':'|'*')*;
TOKEN_INT: ('1'..'9') ('0'..'9')*;

TOKEN_WS: [ \t\n\r]+ -> skip;

fragment A: [aA];
fragment B: [bB];
fragment C: [cC];
fragment D: [dD];
fragment E: [eE];
fragment F: [fF];
fragment G: [gG];
fragment H: [hH];
fragment I: [iI];
fragment J: [jJ];
fragment K: [kK];
fragment L: [lL];
fragment M: [mM];
fragment N: [nN];
fragment O: [oO];
fragment P: [pP];
fragment Q: [qQ];
fragment R: [rR];
fragment S: [sS];
fragment T: [tT];
fragment U: [uU];
fragment V: [vV];
fragment W: [wW];
fragment X: [xX];
fragment Y: [yY];
fragment Z: [zZ];
