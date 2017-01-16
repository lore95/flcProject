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
%token TOK_PLUS
%token TOK_MINUS
%token TOK_DIVIDE
%token TOK_MULTIPLY


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

INTERVALDECL:	SIGNEDDIGIT
			|
				DIGIT
			;
		    
FUNCTION	:	
				FNCT
				TOK_BOPEN
				VARTOPOWER
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

COEFFICIENT	:
				SIGNEDDIGIT
			|
				DIGIT
			|
				SIGNEDDIGIT
				TOK_DOT
				DIGIT
			;
			
VARTOPOWER	:	
				VAR
				{
					printf("VAR only\n");
				}
			|
				COEFFICIENT
				VAR
				{
					printf("COEFFICIENT AND VAR\n");
				}
			|
				VAR
				TOK_POWER
				DIGIT
				{
					printf("VAR AND DIGIT TO POWER\n");
				}
			|
				COEFFICIENT
				VAR
				TOK_POWER
				DIGIT
				{
					printf("COEFFICIENT, VAR AND DIGIT TO POWER\n");
				}
			;
			
%%
