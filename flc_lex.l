%option noyywrap
%{
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
extern  int yylex();
%}

INTVAR			d[^e]
DIGIT	 		[0-9]+
SIGNEDDIGIT		[-+]{DIGIT}
INTEGRAL		INT
%%

{INTEGRAL}				{printf("integral\n"); return INTEGRAL;}
{INTVAR}				{printf("intVar '%s'\n", yytext); return INTVAR;}
{DIGIT}					{printf("digit '%s'\n", yytext); return DIGIT;}
{SIGNEDDIGIT}			{printf("signedDigit '%s'\n", yytext); return SIGNEDDIGIT;}
(log)|(LOG)				{printf("function LOG\n"); return TOK_LOG;}
(ln)|(LN)				{printf("function LN\n"); return TOK_LN;}
(cos)|(COS)				{printf("function COS\n"); return TOK_COS;}
(sin)|(SIN)				{printf("function SIN\n"); return TOK_SIN;}
\(						{printf("symbol '('\n"); return TOK_BOPEN;}
\)						{printf("symbol ')'\n"); return TOK_BCLOSE;}
\[						{printf("symbol '['\n"); return TOK_SBOPEN;}
\]						{printf("symbol ']'\n"); return TOK_SBCLOSE;}
","						{printf("symbol ','\n"); return TOK_COMMA;}
[\+\-\/\*]				{printf("operator '%s'\n", yytext); return TOK_OPERATOR;}
"."						{printf("symbol '.'\n"); return TOK_DOT;}
"^"						{printf("symbol '^'\n"); return TOK_POWER;}
[a-z]					{printf("var '%s'\n", yytext); return VAR;}

%%

