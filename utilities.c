/*
 * utilities.c
 *
 *  Created on: Jan 15, 2017
 *      Author: lorenzo
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "flc.h"

struct _symbolTable symbolTable;
struct _polynomial *currentPolyTerm;
unsigned short integralArgs = 0;

void init()
{
//	symbolTable.lowerBound = NULL;
//	symbolTable.upperBound = NULL;
	symbolTable.function = NULL;
	symbolTable.root = NULL;
	printf("Insert an integral to be calculated or type MAN (for manual) or EXS (for examples)\n");
}

void setLowerBound(char *yytext, char *operator)
{
	sprintf(symbolTable.lowerBound, "%s%s", (operator == NULL ? "" : operator), yytext);
}

void setUpperBound(char *yytext, char *operator)
{
	sprintf(symbolTable.upperBound, "%s%s", (operator == NULL ? "" : operator), yytext);
	if (atoi(symbolTable.upperBound) < atoi(symbolTable.lowerBound))
	{
		printf("The integration bounds set are incorrect!!!\n");
		exit(-1);
	}
}

void strToUpper(char *str)
{
	while(*str != '\0')
	{
		*str = toupper(*str);
		str++;
	}
}
void setFunctionName(char *yytext)
{
	strToUpper(yytext);
	symbolTable.function = strdup(yytext);
	if (strcmp(yytext, "LN") == 0)
	{
		integralArgs |= FNCT_LN;
	}
	else if (strcmp(yytext, "SIN") == 0)
		{
			integralArgs |= FNCT_SIN;
		}
	else if (strcmp(yytext, "COS") == 0)
		{
			integralArgs |= FNCT_COS;
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
	if (power == NULL)
	{
		if (varName != NULL)
		{
			power = "1";
		}
		else
		{
			power = "0";
		}
	}
	currentPolyTerm->term.power = atoi(power);

	switch(currentPolyTerm->term.power)
	{
	case 0:
		integralArgs |= POLY_GRADE_0;
		break;

	case 1:
		integralArgs |= POLY_GRADE_1;
		break;

	case 2:
		integralArgs |= POLY_GRADE_2;
		break;

	case 3:
		integralArgs |= POLY_GRADE_3;
		break;

	default:
		printf("The argument of the integral should be at maximum 3\n");
		exit(-1);
	}

	currentPolyTerm->term.power = atoi(power);
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
	currentPolyTerm->term.coefficientString = "";
	currentPolyTerm->term.power = 0;
	currentPolyTerm->term.variable = "";
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
	/*
	 * Check if a function is specified and the argument is a polynomial with grade greater than 1
	 */
	if (((integralArgs & FNCT_MASK) != 0) && ((integralArgs & POLY_GRADE_MASK_GT_1) != 0))
	{
		printf("The grade of the polynomial argument is greater than 1. Sorry I'm not able to solve it!\n");
		exit(0);
	}
	unsigned short grade = (unsigned short)(integralArgs & POLY_GRADE_MASK);
	switch((integralArgs & FNCT_MASK))
	{
	case 0:
		// No function specified
		calcualtePolynomialIntegral(symbolTable);
		break;

	case FNCT_LN:
		calculateLogIntegralPoly(symbolTable, grade);
		break;
	case FNCT_SIN:
		calculateSinIntegralPoly(symbolTable, grade);
		break;
	case FNCT_COS:
		calculateCosIntegralPoly(symbolTable, grade);
		break;
	case FNCT_EXP:
		calculateExpIntegralPoly(symbolTable, grade);
		break;

	}
	printf("\n");
	exit(0);
}

void printManual(){
	printf("In order to be correctly executed, integrals must be in this format:\n"
			"INT[lowerbound,upperbound](function(polinomy))intvar\n\n"
			"INT: defines the integral function.\n"
			"[lowerbound, upperbound]: optional directive, returns surface value.\n"
			"function(): sin(), cos(), log(), exp() (both log and exp are e-relative), or also none.\n"
			"polinomy: at most of grade 1 for previous functions or 3 for the no-function option.\n"
			"intvar: the integration variable (ex. dx)\n\n"
			"Function calculator will allow only to calculate first grade polinomies without constants.\n");
}

void printExamples(){
	printf("Some examples that will work using our calculator:\n"
			"INT[-2,3](sin(3x))dx\n"
			"INT(cos(47))dx\n"
			"INT(x^2+4x-2)dx\n"
			"INT[4,6](log(4x))dx\n\n"
			"Some non-accepted inputs:\n"
			"INT[3,1](x^2)dx (lower bound greater than upper bound)\n"
			"INT(sin(x+4))dx (first grade polinomy with constant)\n"
			"INT(log(4x^2))dx (second grade polinomy)\n\n");
}
