#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "rtclock.h"
#include "mmm.h"

/* globals (anything here would be shared with all threads) */
double **matrixOne;
double **matrixTwo;
double **P_matrixProduct;
double **S_matrixProduct;
int matrixSize;
int threadCount;
int seqORPar; //0 == seq, 1 = paraless

//argc is the number of arguments 0 being ./mmm
int main(int argc, char *argv[])
{
	//Make sure there the minimum number of arguments
	//Print out for now
	int i;
	for (int i = 0; i < argc; ++i){
		printf("%d :%s\n" ,i,argv[i]);
	}
        

//May need to add a check about if you ender the wronge S or P command
	if(!strcmp(argv[1], "S") || !strcmp(argv[1], "s")){
		printf("\nS!\n"); //REMOVE
		
		//Checks to make sure input is correct for Sequental	
		if(argc < 3){
			printf("Error: too few arguments\n");
			return 1;
		}else if(argc > 3){
			printf("Error: too many arguments\n");
			return 1;
		}
			seqORPar = 0;//set to sequental path
			matrixSize = atoi(argv[2]); //set matrix size to the correct size

	}else if(!strcmp(argv[1], "P") || !strcmp(argv[1], "p")){
		printf("\nP!\n"); //REMOVE
		
		//Checks to make sure input is correct
		if(argc < 4 ){
			printf("Error: parallel mode requires <size>\n");
			return 1;
		}else if(argc > 4){
			printf("Error: too many arguments\n");
		return 1;
		}
		//Set inital perameters:
		seqORPar = 1; //set to paralell path
		threadCount = atoi(argv[2]); //set thread count to the correct number
		matrixSize = atoi(argv[3]); //set matrix size to the correct size

		//TODO need to make both the paralell and sequental run and compare times and then compare
		
	}else{
		printf("\nError: your input of %c is not a valid input. Please only use inputs of (S or P)\nUsage: ./mmm <mode> [num threads] <size>\n", *argv[1]); //ASK print out as string reguardless?
		return 0;
	}
	
	mmm_init(); //always want to start things up!

	mmm_seq();
	printf("\nMatrix Product Seq\n");
	printMatrix(S_matrixProduct);
	parallel();
	printf("\nMatrix Product Par\n");
	printMatrix(P_matrixProduct);

	printf("\n\nThe error difference between Seq and Par was: %f\n",mmm_verify());

	
	// printf("\nMatrix 1\n");
	// printMatrix(matrixOne);
	// printf("\nMatrix 2\n");
	// printMatrix(matrixTwo);

	// printf("\nMatrix Product\n");
	// printMatrix(S_matrixProduct);
	// mmm_seq();
	// printf("\nMatrix Product After\n");
	// printMatrix(S_matrixProduct);
	// //reset test
	// mmm_reset(S_matrixProduct);

	//matrixSize = argv[1];

	//How to use the command line argements(where do I need to do the check?)

	// double clockstart, clockend;
	// clockstart = rtclock(); // start clocking

	// start: stuff I want to clock
	

	// end: stuff I want to clock

	// clockend = rtclock(); // stop clocking
	// printf("\nTime taken: %.6f sec\n", (clockend - clockstart));

	return 0;
}


