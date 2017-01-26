
lexer grammar WSSQLLexer;

// sql keywords
STATEMENT: _S_T_A_T_E_M_E_N_T;
FROM: _F_R_O_M;
WHERE: _W_H_E_R_E;
AS: _A_S;
IF: _I_F;
SQL_NULL: _N_U_L_L;

ID:	[a-zA-Z_-:\*];

WS: [ \t\r\n];

fragment _A: a|A;
fragment _B: b|B;
fragment _C: c|C;
fragment _D: d|D;
fragment _E: e|E;
fragment _F: f|F;
fragment _G: g|G;
fragment _H: h|H;
fragment _I: i|I;
fragment _J: j|J;
fragment _K: k|K;
fragment _L: l|L;
fragment _M: m|M;
fragment _N: n|N;
fragment _O: o|O;
fragment _P: p|P;
fragment _Q: q|Q;
fragment _R: r|R;
fragment _S: s|S;
fragment _T: t|T;
fragment _U: u|U;
fragment _V: v|V;
fragment _W: w|W;
fragment _X: x|X;
fragment _Y: y|Y;
fragment _Z: z|Z;
