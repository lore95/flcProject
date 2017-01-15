%{
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#ifndef YYSTYPE
#define YYSTYPE int
#endif
#define INTEGER 258
extern YYSTYPE yylval;
%}


%union {
       char* lexeme;			//identifier
       double value;			//value of an identifier of type NUM
       }

%token INT
%token <lexeme> LIMITS
%token <lexeme> FUNCTION
%token <lexeme> INTVAR

%start integral

%%
integral	: INT LIMITS FUNCTION INTVAR {printf("The input string is: %s %s %s \n", $2, $3, $4); exit(0);}      
      		| INT FUNCTION INTVAR {printf("The input string is: %s %s \n", $2, $3); exit(0);}
    		;	

%%
