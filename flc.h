/*
 * flc.h
 *
 *  Created on: Jan 22, 2017
 *      Author: osvaldo
 */

#ifndef FLC_H_
#define FLC_H_

#define FNCT_LN					32768 // 1000000000000000
#define FNCT_EXP				16384 // 0100000000000000
#define FNCT_SIN				 8192 // 0010000000000000
#define FNCT_COS				 4096 // 0001000000000000
#define FNCT_MASK				(FNCT_LN | FNCT_EXP | FNCT_COS | FNCT_SIN) // 1111000000000000
#define POLY_GRADE_0			  256 // 0000000100000000
#define POLY_GRADE_1			  512 // 0000001000000000
#define POLY_GRADE_2			 1024 // 0000010000000000
#define POLY_GRADE_3			 2048 // 0000100000000000
#define POLY_GRADE_MASK			(POLY_GRADE_0 | POLY_GRADE_1 | POLY_GRADE_2 | POLY_GRADE_3) // 0000111100000000
#define POLY_GRADE_MASK_GT_1	(POLY_GRADE_2 | POLY_GRADE_3) // 0000110000000000

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
};

#endif /* FLC_H_ */
