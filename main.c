/*
 * main.c
 *
 *  Created on: Jan 8, 2017
 *  Author: Lorenzo
 */
#include <stdio.h>
int a = 1;

int main(int argc, char **argv)
{
	printf("Insert an integral to be calculated or type MAN (for manual) or EXS (for examples):\n");
	yyparse();
}
