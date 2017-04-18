/* File: recdec.h */

// Tokens
const int BEGINTOK = 1, ENDTOK = 2, ASSIGNTOK = 3, SEMITOK = 4, PLUSTOK = 5,
	  MINUSTOK = 6, MULTOK = 7, DIVTOK = 8, MODTOK = 9, LPARENTOK = 10,
	  RPARENTOK = 11, ID = 12, NUM = 13;

int yylex();  
