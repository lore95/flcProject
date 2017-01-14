%{
#include <ctype.h>
#include <string.h>

#include "y.tab.h"
#ifndef	TRUE
#define	TRUE	1
#endif
#ifndef	FALSE
#define	FALSE	0
#endif
int a;
int iVal;
int fVal;
char StringBuffer[64*1024];

/* Read everything in lowercase	*/
#define YY_INPUT(buf,result,max_size) 					\
	if ((result = read (fileno(yyin), (char*) buf, max_size)) < 0) 	\
	    YY_FATAL_ERROR ("read() in flex scanner failed");

%}


%%

^[0-9]		{
			a = 0;
		}

^[ ]		{
			a = 1;
		}

[ ]		{
			a = 2;
		}

[\+\-]?[0-9]+[\,][0-9]* {
    fVal = atof (yytext);
    return(TOK_FLOAT);
}

[\+\-]?[0-9]+ {
    iVal = atol (yytext);
    return(TOK_INTEGER);	
}

\"\"[A-Z0-9]*\"\"	{
	memset( StringBuffer, '\0', sizeof( StringBuffer ) );
	sprintf( StringBuffer, "x%s", yytext + 1 );
	StringBuffer[strlen( StringBuffer ) - 1] = '\0';
	yytext = StringBuffer;
    return(TOK_STRING);	
}

"+"			{ return(TOK_PLUS); }
"-"			{ return(TOK_MINUS); }
"*"			{ return(TOK_ASTERISK); }
"/"			{ return(TOK_SLASH); }
"="			{ return(TOK_EQUAL); }
"$"			{ return(TOK_DOLLAR); }
","			{ return(TOK_COMMA); }
";"			{ return(TOK_SEMICOLON); }
"."			{ return(TOK_PERIOD); }
"("			{ return(TOK_LPAREN); }
")"			{ return(TOK_RPAREN); }
">="        		{ return(TOK_GREATER_EQ); }
"<="        		{ return(TOK_LESS_EQ); }
">"			{ return(TOK_GREATER); }
"<"			{ return(TOK_LESS); }

\n          { a++; }

%%

void StringToLowercase(char* string) {
    int i, StringLength, QuotedText = 0;

    StringLength = strlen(string);
    for (i = 0; i < StringLength; i++) {
        if (string[i] == '"')
	       QuotedText ^= 1;
        else if (!QuotedText)
           string[i] = tolower(string[i]);
    }
}
