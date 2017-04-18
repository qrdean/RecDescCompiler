%{
#include "../include/recdec.h"
#include <stdio.h>
char *yylstring;
int yylval;
%}
/* Regular Definitions */
letter		[A-Za-z_]
digit		[0-9]
id		{letter}*({letter}{digit})*
number		{digit}+
%%
[ \t\n]*	/* do nothing */
begin		{ return BEGINTOK; }
end		{ return ENDTOK; }
":="		{ return ASSIGNTOK; }
";"		{ return SEMITOK; }
"+"		{ return PLUSTOK; }
"-"		{ return MINUSTOK; }
"*"		{ return MULTOK; }
"/"		{ return DIVTOK; }
"%"		{ return MODTOK; }
"("		{ return LPARENTOK; }
")"		{ return RPARENTOK; }
{id}		{ yylstring = strdup(yytext); return(ID);}
{number}	{ sscanf( yytext, "%d", &yylval ); return(NUM); }
%%
