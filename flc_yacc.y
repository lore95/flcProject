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
%token TOK_DOT
%token TOK_OPERATOR


%token INTVAR
%token SIGNEDDIGIT
%token DIGIT
%token VAR

%start integral

%%
integral	:	INTEGRAL
				LIMITS
				TOK_BOPEN
				FUNCTION
				TOK_BCLOSE
				INTVAR
			|
				INTEGRAL
				TOK_BOPEN
				FUNCTION
				TOK_BCLOSE
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

INTERVALDECL:
				TOK_OPERATOR
				DIGIT
			|
				DIGIT
			;
		    
FUNCTION	:	
				FNCT
				TOK_BOPEN
				POLINOMIAL
				TOK_BCLOSE
				{
					printf("Integrating a function\n");
				}
			|
				POLINOMIAL
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

COEFFICIENT	:
				DIGIT
				{
					printf("found a DIGIT\n");
				}
			|
				DIGIT
				TOK_DOT
				DIGIT
				{
					printf("found a DIGIT, DOT, DIGIT\n");
				}
			;

POLITERM	:	
				COEFFICIENT
				{
					printf("POLITERM DIGIT\n");
				}
			|
				VAR
				{
					printf("POLITERM VAR only\n");
				}
			|
				COEFFICIENT
				VAR
				{
					printf("POLITERM DIGIT AND VAR\n");
				}
			|
				VAR
				TOK_POWER
				DIGIT
				{
					printf("POLITERM VAR AND DIGIT TO POWER\n");
				}
			|
				COEFFICIENT
				VAR
				TOK_POWER
				DIGIT
				{
					printf("POLITERM DIGIT, VAR AND DIGIT TO POWER\n");
				}
			;

POLINOMIAL	:
				POLITERM
			|
				POLITERM
				TOK_OPERATOR
				POLINOMIAL
			;	
%%
