/*
 * utilities.c
 *
 *  Created on: Jan 15, 2017
 *      Author: osvaldo
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct _polyTerm {
	char *variable;
	float coefficient;
	char *coefficientString;
	int power;
};

struct _polynomial {
	struct _polyTerm term;
	struct _polynomial *next;
};

struct _symbolTable {
	char *upperBound;
	char *lowerBound;
	char *function;
	struct _polynomial *root;
	char integrationVar;
} symbolTable;

struct _polynomial *currentPolyTerm;

void init()
{
	symbolTable.lowerBound = "INF";
	symbolTable.upperBound = "INF";
	symbolTable.function = NULL;
	symbolTable.root = NULL;
}

void setLowerBound(char *yytext)
{
	symbolTable.lowerBound = strdup(yytext);
}

void setUpperBound(char *yytext)
{
	symbolTable.upperBound = strdup(yytext);
}

void setFunctionName(char *yytext)
{
	symbolTable.function = strdup(yytext);
}

void initPolynomial()
{
	symbolTable.root = (struct _polynomial *) malloc(sizeof(struct _polynomial));
	currentPolyTerm = symbolTable.root;
}

void setPolyTerm(char *operator, char *coefficient, char *varName, char *power)
{
	if (coefficient != NULL)
	{
		currentPolyTerm->term.coefficient = atof(coefficient);
		if ((operator != NULL) && (*operator == '-'))
		{
			currentPolyTerm->term.coefficient *= -1;
		}
		char *locCoefficient = coefficient;
		while(!isdigit(*locCoefficient))
			locCoefficient++;
		currentPolyTerm->term.coefficientString = strdup(locCoefficient);
	}
	if (varName != NULL)
	{
		currentPolyTerm->term.variable = strdup(varName);
	}
	if (power != NULL)
	{
		currentPolyTerm->term.power = atoi(power);
	}
}

void addPolyTerm()
{
	if (symbolTable.root == NULL)
	{
		initPolynomial();
	}
	currentPolyTerm->next = (struct _polynomial *) malloc(sizeof(struct _polynomial));
	currentPolyTerm = currentPolyTerm->next;
	currentPolyTerm->term.coefficient = 1.0;
	currentPolyTerm->term.power = 0;
}

void setIntegrationVar(char varName)
{
	symbolTable.integrationVar = varName;
}

void calculate()
{
	printf("Doing the dirty job....\n");
	printf("Integrating on variable %c\n", symbolTable.integrationVar);
	printf("Limits: lower %s; upper %s\n", symbolTable.lowerBound,
										   symbolTable.upperBound);
	if (symbolTable.function != NULL)
	{
		printf("The integral function is: %s\n", symbolTable.function);
		printf("the argument is ");
	}
	else
	{
		printf("Integrating the polynomial ");
	}
	currentPolyTerm = symbolTable.root->next;
	char operator;
	while(currentPolyTerm != NULL)
	{
		if (currentPolyTerm->term.coefficient < 0)
		{
			operator = '-';
		}
		else
		{
			if (currentPolyTerm != symbolTable.root->next)
			{
				operator = '+';
			}
			else
			{
				operator = ' ';
			}
		}
		printf("%c %s%s", operator,
						   (currentPolyTerm->term.coefficient != 1.0 ? currentPolyTerm->term.coefficientString : ""),
						   (currentPolyTerm->term.variable != NULL ? currentPolyTerm->term.variable : ""));
		if (currentPolyTerm->term.power != 0)
		{
			printf("^%d", currentPolyTerm->term.power);
		}
		printf(" ");
		currentPolyTerm = currentPolyTerm->next;
	}
	printf("\n");
	exit(0);
}
