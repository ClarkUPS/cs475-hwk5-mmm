#ifndef MMM_H_
#define MMM_H_

extern double **matrixOne;
extern double **matrixTwo;
extern double **matrixProduct;
extern int matrixSize;

void mmm_init();

void malMatrix(double **matrix); //to malloc the matricies 
void rNumToMatrix(double **matrix); //to populate the matricies

void mmm_reset(double **matrix);
void mmm_freeup();
void mmm_seq();
void *mmm_par(void *args);
double mmm_verify();

void printMatrix(double **matrix); //to test and print matricies

#endif /* MMM_H_ */
