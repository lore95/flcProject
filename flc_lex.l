%option noyywrap
%{
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
extern  int yylex(); 
%}

INTVAR			d[^e]
DIGIT	 		[0-9]+
FLOAT			[0-9]+\.[0-9]*
EXPONENT		\^[0-9]+
INTEGRAL		INT
MANUAL			MAN
EXAMPLES		EXS
%%

{INTEGRAL}				{return INTEGRAL;}
{INTVAR}				{return INTVAR;}
{DIGIT}					{return DIGIT;}
{EXPONENT}				{return EXPONENT;}
{FLOAT}					{return FLOAT;}
{MANUAL}				{return MANUAL;}
{EXAMPLES}				{return EXAMPLES;}
(exp)|(EXP)				{return TOK_EXP;}
(ln)|(LN)				{return TOK_LN;}
(cos)|(COS)				{return TOK_COS;}
(sin)|(SIN)				{return TOK_SIN;}
\(						{return TOK_BOPEN;}
\)						{return TOK_BCLOSE;}
\[						{return TOK_SBOPEN;}
\]						{return TOK_SBCLOSE;}
","						{return TOK_COMMA;}
[\+\-\/\*]				{return TOK_OPERATOR;}
"."						{return TOK_DOT;}
"^"						{return TOK_POWER;}
[a-z]					{return VAR;}

%%