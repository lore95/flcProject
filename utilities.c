/*
 * utilities.c
 *
 *  Created on: Jan 15, 2017
 *      Author: osvaldo
 */

#include <stdio.h>

struct _poliTerm {
	float coefficient;
	int power;
};


void setLowerInterval(char *yytext)
{
	printf("lower interval is %d\n", atoi(yytext));
}

void setUpperInterval(char *yytext)
{
	printf("upper interval is %d\n", atoi(yytext));
}
