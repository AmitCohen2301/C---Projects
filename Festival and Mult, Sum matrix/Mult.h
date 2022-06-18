#ifndef MULT_H

//prototypes and defines

#define MULT_H
#define N 10

int calcCell(int *matA, int *matB, int rowInA, int colInB, int sizeOfMat);	//Calc the cell value
void multMatrix(int *matA, int *matB, int *matC, int sizeOfMat);			//Mult two matrix
void doMultMat();															//Do mult in two matrix

#endif