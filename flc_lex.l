%option noyywrap
%{
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
extern  int yylex();
%}

INTVAR			d[^e]
DIGITS	 		[0-9]+
SIGNEDIGITS		[-+]?{DIGITS}
VARID			[a-z]
COEFICCIENT		[-+]?[({DIGITS}(\.{DIGITS})?)({DIGITS}/{DIGITS})]
LIMITS			\[{SIGNEDIGITS}\,{SIGNEDIGITS}\]
FUNCTION		[{LOG}{COS}{SIN}{LN}]\({ARGUMENT}\)
ARGUMENT		[{COEFICCIENT}]{VARID}(\^{DIGITS})?
LOG				log
COS				cos
SIN				sin
LN				ln
INTEGRAL		INT
%%

{INTEGRAL}	{return INTEGRAL;}
{FUNCTION}	{yylval.lexeme = strdup(yytext); return FUNCTION;}
{LIMITS}	{yylval.lexeme = strdup(yytext); return LIMITS;}
{INTVAR}	{yylval.lexeme = strdup(yytext); return INTVAR;}
%%
