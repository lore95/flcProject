/*
 * utilities.c
 *
 *  Created on: Jan 15, 2017
 *      Author: lorenzo
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FNCT_LOG				1000000000000000
#define FNCT_EXP				0100000000000000
#define FNCT_SIN				0010000000000000
#define FNCT_COS				0001000000000000
#define FNCT_MASK				1111000000000000
#define POLY_GRADE_0			0000000100000000
#define POLY_GRADE_1			0000001000000000
#define POLY_GRADE_2			0000010000000000
#define POLY_GRADE_3			0000100000000000
#define POLY_GRADE_MASK			0000111100000000
#define POLY_GRADE_MASK_GT_1	0000110000000000

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
short integralArgs = 0;

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
	if (strcmp(yytext, "LOG") == 0)
	{
		integralArgs |= FNCT_LOG;
	}
	else if (strcmp(yytext, "EXP") == 0)
	{
		integralArgs |= FNCT_EXP;
	}

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
		if (atoi(power) > 3)
		{
			printf("The argument of the integral should be at maximum 3\n");
			exit(-1);
		}
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
	currentPolyTerm->next = NULL;
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

	/*
	 * Check if a function is specified and the argument is a polynomial with grade greater than 1
	 */
	if (((integralArgs & FNCT_MASK) != 0) && ((integralArgs & POLY_GRADE_MASK_GT_1) != 0))
	{
		pritnf("The grade of the polynomial argument is greater than 1. Sorry I'm not able to solve it!\n");
		exit(0);
	}

	switch((integralArgs & FNCT_MASK))
	{
	case 0:
		// No function specified
		calcualtePolynomialIntegral(symbolTable);
		break;

	case FNCT_LOG:
		if (integralArgs & POLY_GRADE_MASK == POLY_GRADE_0)
			calculateLogIntegralPoly0(symbolTable);
		else if(integralArgs & POLY_GRADE_MASK == POLY_GRADE_1)
			calculateLogIntegralPoly1(symbolTable);
		else
			printf("plz no more, rito plz");
		break;
	case FNCT_SIN:
		if (integralArgs & POLY_GRADE_MASK == POLY_GRADE_0)
					calculateSinIntegralPoly0(symbolTable);
		else if(integralArgs & POLY_GRADE_MASK == POLY_GRADE_1)
				calculateSinIntegralPoly1(symbolTable);
		else
			printf("plz no more, rito plz");
		break;
	case FNCT_COS:
		if (integralArgs & POLY_GRADE_MASK == POLY_GRADE_0)
				calculateCosIntegralPoly0(symbolTable);
		else if(integralArgs & POLY_GRADE_MASK == POLY_GRADE_1)
			calculateCosIntegralPoly1(symbolTable);
		else
			printf("plz no more, rito plz");
		break;
	case FNCT_EXP
		break;

	}
	printf("\n");
	exit(0);
}
