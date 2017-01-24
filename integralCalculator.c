#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "flc.h"

char *polyTermToString(char operator, struct _polyTerm term,
		char integrationVar) {
	static char result[128];
	char integratedCoeffcient[64];
	memset(integratedCoeffcient, '\0', sizeof(integratedCoeffcient));
	sprintf(integratedCoeffcient, "(%s/%d)",
			(term.coefficient != 1.0 ? term.coefficientString : "1"),
			(term.power + 1));

	sprintf(result, "%c %s%c", operator, integratedCoeffcient, integrationVar);
	if (term.power > 0) {
		char power[8];
		sprintf(power, "^%d", (term.power + 1));
		strcat(result, power);
	}
	strcat(result, " ");
	return (result);
}

void calcualtePolynomialIntegral(struct _symbolTable symbolTable) {
	struct _polynomial *currentPolyTerm;

	currentPolyTerm = symbolTable.root->next;
	char operator;
	char result[4096];

	float integralResult = 0;

	while (currentPolyTerm != NULL) {
		if (currentPolyTerm->term.coefficient < 0) {
			operator = '-';
		} else {
			if (currentPolyTerm != symbolTable.root->next) {
				operator = '+';
			} else {
				operator = ' ';
			}
		}
		if (currentPolyTerm->term.variable[0] != symbolTable.integrationVar) {
			char term[64];
			sprintf(term, "%c %s%s%c ", operator,
					currentPolyTerm->term.coefficientString,
					currentPolyTerm->term.variable, symbolTable.integrationVar);
			strcat(result, term);
		} else {
			strcat(result,
					polyTermToString(operator, currentPolyTerm->term,
							symbolTable.integrationVar));
			if (symbolTable.upperBound != NULL) {
				float termResult = currentPolyTerm->term.coefficient
						/ (currentPolyTerm->term.power + 1);
				integralResult += (termResult
						* pow((double) atoi(symbolTable.upperBound),
								(currentPolyTerm->term.power + 1)))
						- (termResult
								* pow((double) atoi(symbolTable.lowerBound),
										(currentPolyTerm->term.power + 1)));
			}
		}
		currentPolyTerm = currentPolyTerm->next;
	}
	printf("The integrated function is '%s+ C'\n", result);
	if (symbolTable.upperBound != NULL) {
		printf("The integrated function value is '%f'\n", integralResult);
	}
}

void calculateLogIntegralPoly(struct _symbolTable symbolTable,
		unsigned short grade) {
	struct _polynomial *currentPolyTerm;
	float integralResult = 0;

	currentPolyTerm = symbolTable.root->next;

	if (symbolTable.upperBound != NULL) {
		int uBound = atoi(symbolTable.upperBound);
		int lBound = atoi(symbolTable.lowerBound);

		if (grade == POLY_GRADE_0) {
			float termResult = log(currentPolyTerm->term.coefficient);
			integralResult += (termResult * uBound) - (termResult * lBound);
		} else {
			integralResult = (uBound
					* log(currentPolyTerm->term.coefficient * uBound) - uBound)
					- (lBound * log(currentPolyTerm->term.coefficient * lBound)
							- lBound);
		}
	}
	printf("The integrated function is '%cln(%s%s) ",
			symbolTable.integrationVar, currentPolyTerm->term.coefficientString,
			currentPolyTerm->term.variable);

	if (grade == POLY_GRADE_1) {
		printf("- %c + C'\n", symbolTable.integrationVar);
	} else {
		printf("+ C'\n");
	}
	if (symbolTable.upperBound != NULL) {
		printf(
				"The integrated function value over the specified limits is '%f'\n",
				integralResult);
	}
}

void calculateExpIntegralPoly(struct _symbolTable symbolTable,
		unsigned short grade) {
	struct _polynomial *currentPolyTerm;
	float integralResult = 0;

	currentPolyTerm = symbolTable.root->next;

	if (symbolTable.upperBound != NULL) {
		int uBound = atoi(symbolTable.upperBound);
		int lBound = atoi(symbolTable.lowerBound);

		if (grade == POLY_GRADE_0) {
			float termResult = exp(currentPolyTerm->term.coefficient);
			integralResult += (termResult * uBound) - (termResult * lBound);
		} else {
			integralResult = ((1 / currentPolyTerm->term.coefficient)
					* (exp((currentPolyTerm->term.coefficient * uBound))
							- exp(currentPolyTerm->term.coefficient * lBound)));
		}
	}
	if (grade == POLY_GRADE_1) {
		printf("The integrated function is (1/%s)exp(%s%s) +C\n",
				currentPolyTerm->term.coefficientString,
				currentPolyTerm->term.coefficientString,
				currentPolyTerm->term.variable);
	} else {
		printf("The integrated function is %cexp(%s) +C\n",
				symbolTable.integrationVar,
				currentPolyTerm->term.coefficientString);
	}
	if (symbolTable.upperBound != NULL) {
		printf(
				"The integrated function value over the specified limits is '%f'\n",
				integralResult);
	}
}

void calculateSinIntegralPoly(struct _symbolTable symbolTable,
		unsigned short grade) {
	struct _polynomial *currentPolyTerm;
	float integralResult = 0;

	currentPolyTerm = symbolTable.root->next;

	if (symbolTable.upperBound != NULL) {
		int uBound = atoi(symbolTable.upperBound);
		int lBound = atoi(symbolTable.lowerBound);

		if (grade == POLY_GRADE_0) {
			float termResult = sin(currentPolyTerm->term.coefficient);
			integralResult += (termResult * uBound) - (termResult * lBound);
		} else {
			integralResult = (1 / currentPolyTerm->term.coefficient)
					* (-cos(uBound * currentPolyTerm->term.coefficient)
							+ cos(lBound * currentPolyTerm->term.coefficient));
		}
	}
	if (grade == POLY_GRADE_1) {
		if (currentPolyTerm->term.coefficient == 1)
			printf("The integrated function is '-cos(%c) + C \n",
					symbolTable.integrationVar);
		else
			printf("The integrated function is '(1/%s (-cos(%s%c))) + C \n",
					currentPolyTerm->term.coefficientString,
					currentPolyTerm->term.coefficientString,
					symbolTable.integrationVar);
	} else {
		printf(" %c sin(%f) + C'\n", symbolTable.integrationVar,
				currentPolyTerm->term.coefficient);
	}
	if (symbolTable.upperBound != NULL) {
		printf(
				"The integrated function value over the specified limits is '%f'\n",
				integralResult);
	}
}
void calculateCosIntegralPoly(struct _symbolTable symbolTable,
		unsigned short grade) {
	struct _polynomial *currentPolyTerm;
	float integralResult = 0;

	currentPolyTerm = symbolTable.root->next;

	if (symbolTable.upperBound != NULL) {
		int uBound = atoi(symbolTable.upperBound);
		int lBound = atoi(symbolTable.lowerBound);

		if (grade == POLY_GRADE_0) {
			float termResult = cos(currentPolyTerm->term.coefficient);
			integralResult += (termResult * uBound) - (termResult * lBound);
		} else {
			integralResult = (((1 / currentPolyTerm->term.coefficient)
					* sin(currentPolyTerm->term.coefficient * uBound))
					- ((1 / currentPolyTerm->term.coefficient)
							* sin(currentPolyTerm->term.coefficient * lBound)));
		}
	}

	if (grade == POLY_GRADE_0)
		printf("%c * cos(%s) + c \n", symbolTable.integrationVar,
				currentPolyTerm->term.coefficientString);
	else {
		if (currentPolyTerm->term.coefficient == 1)
			printf("sin(%c) + c \n", symbolTable.integrationVar);
		else
			printf("((1/%s)sin(%s%c)) + c\n",
					currentPolyTerm->term.coefficientString,
					currentPolyTerm->term.coefficientString,
					symbolTable.integrationVar);
	}
	if (symbolTable.upperBound != NULL) {
		printf(
				"The integrated function value over the specified limits is '%f'\n",
				integralResult);
	}

}

