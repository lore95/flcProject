#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
void calcualtePolynomialIntegral(symbolTable)
{
	currentPolyTerm = symbolTable.root->next;
	char operator;
	char result[4096];
	if(symbolTable.upperbound == NULL)
	{
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
			strcat(result,(operator,
						((currentPolyTerm->term.coefficient != 1.0 ? currentPolyTerm->term.coefficientString)/
						(currentPolyTerm->term.power != 0 ? (currentPolyTerm->term.power +1))*
						(currentPolyTerm->term.variable != NULL ? currentPolyTerm->term.variable)^
						(currentPolyTerm->term.power != 0 ? (currentPolyTerm->term.power +1));
			currentPolyTerm = currentPolyTerm->next;
		}
	}
	else
	{
		currentPolyTerm = symbolTable.root->next;
		char operator;
		char result[4096];
		if(symbolTable.upperbound == NULL)
		{
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
				strcat(result,(operator,
							(((currentPolyTerm->term.coefficient != 1.0 ? currentPolyTerm->term.coefficientString)/
							(currentPolyTerm->term.power != 0 ? (currentPolyTerm->term.power +1))*
							(symbolTable.upperbound)^
							(currentPolyTerm->term.power != 0 ? (currentPolyTerm->term.power +1)) -
							((currentPolyTerm->term.coefficient != 1.0 ? currentPolyTerm->term.coefficientString)/
							(currentPolyTerm->term.power != 0 ? (currentPolyTerm->term.power +1))*
							(symbolTable.lowerbound)^
							(currentPolyTerm->term.power != 0 ? (currentPolyTerm->term.power +1));
				currentPolyTerm = currentPolyTerm->next;
			}
		}
	}
}

void calculateLogIntegralPoly(symbolTable, grade)
{
	if (symbolTable.upperbound != null)
		{
			if (grade == POLY_GRADE_0)
				(log (costante)*symbolTable.upperbound - log(costante)*symbolTable.lowerbound) +c; 
			else	
				printf(((symbolTable.upperbound*log(symbolTable.upperbound)-symbolTable.upperbound) - 
				(symbolTable.lowerbound*log(symbolTable.lowerbound)-symbolTable.lowerbound))+c);
		}
	else
	{
		if (grade == POLY_GRADE_0)
			printf( log(costante)*x +c);	
		else 
			printf( x*log(x)-x +c);
	}
}

void calculateSinIntegralPoly(symbolTable, grade)
{
	if (symbolTable.upperbound != null)
	{
		if (grade == POLY_GRADE_0)
			sin(costante)*symbolTable.upperbound - sin(costante)*symbolTable.lowerbound +c;
		else
			(-cos(symbolTable.upperbound) + cos(symbolTable.lowerbound)) +c;  
	}
	else
	{
		if (grade == POLY_GRADE_0)
			printf(x*sin(costante) +c);
		else
			printf(-cos(x) +c);
	}
}
void calculateCosIntegralPoly(symbolTable, grade)
{
	if symbolTable.upperbound != null
	{
		if (grade == POLY_GRADE_0)
			cos(costante)*symbolTable.upperbound - cos(costante)*symbolTable.lowerbound +c; 
		else
			(sin(symbolTable.upperbound) - sin(symbolTable.lowerbound)) +c; 
	}
	
	else
	{
		if(grade == POLY_GRADE_0)
			printf( x*cos(costante) +c);
		else	
			printf(sin(x) +c);
	}
}
void calculateExpIntegral()
{
	

}
