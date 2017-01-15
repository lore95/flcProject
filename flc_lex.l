%option noyywrap
%{
#include <stdlib.h>
#include <string.h>
%}

INTVAR			d[^e]
DIGITS	 		[0-9]+
SIGNEDIGITS		[-+]?{DIGITS}
VARID			[a-z]
COEFICCIENT		[-+]?[({DIGITS}(\.{DIGITS})?)({DIGITS}/{DIGITS})]
LIMITS			\[{SIGNEDIGITS}\,{SIGNEDIGITS}\]
FUNCTION		[{LOG}{COS}{SIN}{LN}]\({ARGUMENT}\)
ARGUMENT		{COEFICCIENT}{VARID}(\^{DIGITS})?
LOG				log
COS				cos
SIN				sin
LN				ln
INT				INT
%%

[ ]     { /* skip blanks */ }


{INT}    	{return INT;}
{FUNCTION}	{yylval.lexeme = strdup(yytext); return FUNCTION;}
{LIMITS}	{yylval.lexeme = strdup(yytext); return LIMITS;}
%%