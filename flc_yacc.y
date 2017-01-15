%{
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

extern	char	*yytext;

void yyerror(char *s)
{
	printf("** ERROR ** '%s' on token '%s'\n", s, yytext);
}
%}

%union {
       char* lexeme;			//identifier
       double value;			//value of an identifier of type NUM
       }

%token INTEGRAL
%token TOK_LOG
%token TOK_LN
%token TOK_COS
%token TOK_SIN
%token TOK_BOPEN
%token TOK_BCLOSE
%token TOK_SBOPEN
%token TOK_SBCLOSE
%token TOK_COMMA
%token TOK_POWER

%token INTVAR
%token SIGNEDDIGIT
%token DIGIT
%token COEFFICIENT
%token VAR

%start integral

%%
integral	:	INTEGRAL
				LIMITS
				FUNCTION
				INTVAR
			|
				INTEGRAL
				FUNCTION
				INTVAR
		    ;
		    
LIMITS		:	TOK_SBOPEN
				INTERVALDECL
					{
						setLowerInterval(yytext);
					}
				TOK_COMMA
				INTERVALDECL
					{
						setUpperInterval(yytext);
					}
		    	TOK_SBCLOSE
		    ;

INTERVALDECL:	SIGNEDDIGIT
			|
				DIGIT
			;
		    
FUNCTION	:	TOK_BOPEN
				FNCT
				TOK_BOPEN
				VARTOPOWER
				TOK_BCLOSE
				TOK_BCLOSE
				{
					printf("Integrating a function\n");
				}
			;
			
FNCT		:	TOK_LOG
				{
					printf("Integrating a LOG\n");
				}
			|	TOK_LN
				{
					printf("Integrating a LN\n");
				}
			|	TOK_COS
				{
					printf("Integrating a COS\n");
				}
			|	TOK_SIN
				{
					printf("Integrating a SIN\n");
				}
			;

VARTOPOWER	:	VAR
			|
				COEFFICIENT
				VAR
			|
				VAR
				TOK_POWER
				DIGIT
			|
				COEFFICIENT
				VAR
				TOK_POWER
				DIGIT
			;
			
%%
