%{
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
void yyerror(char *s)
{
	fprintf(stderr, "** ERROR ** '%s'\n", s);
}
extern	char	*yytext;
%}


%union {
       char* lexeme;			//identifier
       double value;			//value of an identifier of type NUM
       }

%token INTEGRAL
%token<lexeme> LIMITS
%token<lexeme> FUNCTION
%token<lexeme> INTVAR

%start integral

%%
integral	: INTEGRAL 
		  { printf("INTEGRAL ");}
		  LIMITS 
		  { printf("LIMITS: '%s'", yytext);}
		  FUNCTION
		  { printf("FUNCTION: '%s'", yytext);}
		  INTVAR 
		  { printf("iNTVAR: '%s'\n", yytext); exit(0);}
    		;	

%%
