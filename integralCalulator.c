#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
void calcualtePolynomialIntegral(symbolTable);
{
	while(symbolTable.root.term.variable != null)
	{
		 
	}
}

void calculateLogIntegralPoly0(symbolTable)
{
	if symbolTable.upperbound != null
		(log (costante)*symbolTable.upperbound - log(costante)*symbolTable.lowerbound) +c; 
	else
		printf( il log(costante)*x +c);
}

void calculateLogIntegralPoly1(symbolTable)
{
	if symbolTable.upperbound != null
		printf( il ((symbolTable.upperbound*log(symbolTable.upperbound)-symbolTable.upperbound) - 
				(symbolTable.lowerbound*log(symbolTable.lowerbound)-symbolTable.lowerbound))+c);
		
	else	
		printf( il x*log(x)-x +c);
}

void calculateSinIntegralPoly0(symbolTable)
{
	if symbolTable.upperbound != null
		sin(costante)*symbolTable.upperbound - sin(costante)*symbolTable.lowerbound +c; 
	else
		printf( il x*sin(costante) +c);

}
void calculateSinIntegralPoly1(symbolTable)
{
	if symbolTable.upperbound != null
			(-cos(symbolTable.upperbound) + cos(symbolTable.lowerbound)) +c; 
	else
		printf(-cos(x) +c);
}
void calculateCosIntegralPoly0()
{
	if symbolTable.upperbound != null
		cos(costante)*symbolTable.upperbound - cos(costante)*symbolTable.lowerbound +c; 
	else
		printf( il x*cos(costante) +c);
	
}
void calculateCosIntegralPoly1()
{
	if symbolTable.upperbound != null
		(sin(symbolTable.upperbound) - sin(symbolTable.lowerbound)) +c; 
	else	
		printf(sin(x) +c);
	
}
void calculateExpIntegral()
{
	

}
