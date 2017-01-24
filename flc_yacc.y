%{
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
extern	char	*yytext;
char *coefficient;
char *operator;
char *varName;
char *power;
void yyerror(char *s)
{
	printf("** ERROR ** '%s' on token '%s'\n", s, yytext);
}
%}


%token INTEGRAL
%token TOK_EXP
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
%token FLOAT
%token EXPONENT
%token VAR

%token MANUAL
%token EXAMPLES

%start integralInit

%%
integralInit:	{
					init();
				}
				integral
				{
					calculate();
				}			
			|
				MANUAL
				{
					printManual();
				}
			|
				EXAMPLES
				{
					printExamples();
				}
			;
				
integral	:	INTEGRAL
				LIMITS
				TOK_BOPEN
				FUNCTION
				TOK_BCLOSE
				INTVAR
				{
					setIntegrationVar(*(yytext+1));
				}
			|
				INTEGRAL
				TOK_BOPEN
				FUNCTION
				TOK_BCLOSE
				INTVAR
				{
					setIntegrationVar(*(yytext+1));
				}
		    ;
		    
LIMITS		:	TOK_SBOPEN
				INTERVALDECL
				{
					setLowerBound(yytext, operator);
				}
				TOK_COMMA
				INTERVALDECL
				{
					setUpperBound(yytext, operator);
				}
		    	TOK_SBCLOSE
		    ;

INTERVALDECL:
				TOK_OPERATOR
				{
					operator = strdup(yytext);
				}
				DIGIT
			|
				DIGIT
				{
					operator = NULL;
				}
			;
		    
FUNCTION	:	
				FNCT
				{
					setFunctionName(yytext);
				}
				TOK_BOPEN
				POLYINIT
				TOK_BCLOSE
			|
				POLYINIT
			;
			
FNCT		:	
				TOK_EXP
			|	
				TOK_LN
			|	
				TOK_COS
			|	
				TOK_SIN
			;

COEFFICIENT	:
				DIGIT
				{
					coefficient = strdup(yytext);
				}
			|
				FLOAT
				{
					coefficient = strdup(yytext);
				}
			;

VARRECNAME	:
				VAR
				{
					varName = strdup(yytext);
				}
			;
			
POLITERM	:	
				COEFFICIENT
			|
				VARRECNAME
			|
				COEFFICIENT
				VARRECNAME
			|
				VARRECNAME
				EXPONENT
				{
					power = strdup((yytext + 1));
				}
			|
				COEFFICIENT
				VARRECNAME
				EXPONENT
				{
					power = strdup((yytext + 1));
				}
			;

POLYINIT	:
				{
					addPolyTerm();
				}
				POLYNOMIAL
			;	

POLYNOMIAL	:
				POLITERM
				{
					setPolyTerm(operator, coefficient, varName, power);
					if (coefficient != NULL) 
					{
						free(coefficient);
						coefficient = NULL;
					}
					if (varName != NULL) 
					{
						free(varName);
						varName = NULL;
					}
					if (power != NULL) 
					{
						free(power);
						power = NULL;
					}
					if (operator != NULL) 
					{
						free(operator);
						operator = NULL;
					}
				}
			|
				POLITERM
				{
					setPolyTerm(operator, coefficient, varName, power);
					if (coefficient != NULL) 
					{
						free(coefficient);
						coefficient = NULL;
					}
					if (varName != NULL) 
					{
						free(varName);
						varName = NULL;
					}
					if (power != NULL) 
					{
						free(power);
						power = NULL;
					}
					if (operator != NULL) 
					{
						free(operator);
						operator = NULL;
					}
				}
				TOK_OPERATOR
				{
					operator = strdup(yytext);
				}
				POLYINIT
			;	

%%