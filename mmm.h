#ifndef MMM_H_
#define MMM_H_


extern double **matrixOne;
extern double **matrixTwo;
extern double **S_matrixProduct; //for the sequental result
extern double **P_matrixProduct; //for the paralell result
extern int matrixSize;
extern int threadCount;

typedef struct thread_args
 {
	 int tid;
	 int firstRow;
	 int LastRow;
 }thread_args;

void mmm_init();


void malMatrix(double **matrix); //to malloc the matricies 
void rNumToMatrix(double **matrix); //to populate the matricies

void mmm_reset(double **matrix);
void mmm_freeup();
void mmm_seq();
void *mmm_par();

void parallel();

double mmm_verify();

void printMatrix(double **matrix); //to test and print matricies

#endif /* MMM_H_ */
