%{

#include <stdio.h>
#include <string.h>

#ifndef TRUE
#define TRUE		1
#endif

#ifndef FALSE
#define FALSE		0
#endif

int 	yyerror (char * msg);

extern	char	*yytext;
extern char StringBuffer[];

%}

%token TOK_FLOAT
%token TOK_INTEGER
%token TOK_STRING
%token TOK_PLUS
%token TOK_MINUS
%token TOK_ASTERISK
%token TOK_SLASH
%token TOK_EQUAL
%token TOK_DOLLAR
%token TOK_COMMA
%token TOK_SEMICOLON
%token TOK_PERIOD
%token TOK_LPAREN
%token TOK_RPAREN
%token TOK_GREATER_EQ
%token TOK_LESS_EQ
%token TOK_GREATER
%token TOK_LESS
%%

tok_float:	TOK_FLOAT;
%%

int yyerror (char * msg)
{
    fprintf(stderr, "%s, (%d, %s, %s)", 
			msg, yychar, StringBuffer, yytext );
    return (0);
}

