#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "rtclock.h"
#include "mmm.h"

#define smoothvalue 3
/* globals (anything here would be shared with all threads) */
double **matrixOne;
double **matrixTwo;
double **P_matrixProduct;
double **S_matrixProduct;
int matrixSize;
int threadCount;
int seqORPar; //0 == seq, 1 = parallel

//argc is the number of arguments 0 being ./mmm
int main(int argc, char *argv[])
{
	//Make sure there the minimum number of arguments
	//Print out for now
    if(argc == 1){
		printf("Usage: ./mmm <mode> [num threads] <size>\n");
		return 1;
	}
//May need to add a check about if you ender the wronge S or P command
	if(!strcmp(argv[1], "S") || !strcmp(argv[1], "s")){
		
		//Checks to make sure input is correct for Sequental	
		if(argc < 3){
			printf("Error: too few arguments\n./mmm <mode> [num threads] <size>\n");
			return 1;
		}else if(argc > 3){
			printf("Error: too many arguments\n./mmm <mode> [num threads] <size>\n");
			return 1;
		}
			seqORPar = 0;//set to sequental path
			matrixSize = atoi(argv[2]); //set matrix size to the correct size

	}else if(!strcmp(argv[1], "P") || !strcmp(argv[1], "p")){
		
		//Checks to make sure input is correct
		if(argc < 4 ){
			printf("Error: parallel mode requires <size>\n./mmm <mode> [num threads] <size>\n");
			return 1;
		}else if(argc > 4){
			printf("Error: too many arguments\n./mmm <mode> [num threads] <size>\n");
		return 1;
		}
		//Set inital perameters:
		seqORPar = 1; //set to paralell path
		threadCount = atoi(argv[2]); //set thread count to the correct number
		matrixSize = atoi(argv[3]); //set matrix size to the correct size

		//TODO need to make both the paralell and sequental run and compare times and then compare
		
	}else if(seqORPar == 1){
		printf("\nError: your input of %c is not a valid input. Please only use inputs of (S or P)\nUsage: ./mmm <mode> [num threads] <size>\n", *argv[1]); //ASK print out as string reguardless?
		return 0;
	}
	
	//printf("Status thread count %d matrix size %d", threadCount, matr);

	mmm_init(); //always want to start things up should things get to this point!
	//printf("\nCRASH?\n"); //Will crash if this is not called!

	//Sequental Test!
	if(seqORPar == 0){
		mmm_seq(); //Warm up run
		mmm_reset(S_matrixProduct);
	
	printf("\n========\nmode: sequential\nthread count: 1\nsize: %d\n========\n",matrixSize);
	//Time the sequenal implementation
		double clockAve;
		double clockstart_S, clockend_S;
		int a;
		for(a = 0; a < smoothvalue; a++){
			clockstart_S = 0;
			clockend_S = 0;
			clockstart_S = rtclock(); // start clocking
			mmm_seq();
			clockend_S = rtclock(); // stop clocking
			clockAve += (clockend_S - clockstart_S);
		}
		clockAve = (clockAve/smoothvalue);
		printf("\nTime taken: %.6f sec\n", clockAve);
	
	mmm_freeup();
	
	}else{
		
		mmm_seq(); //Warm up run
		mmm_reset(S_matrixProduct);

		printf("\n========\nmode: parallel\nthread count: %d\nsize: %d\n========",threadCount,matrixSize);

	//Time test for Seq
		
		double clockAveS;
		double clockstart_S, clockend_S;
		int a;
		for(a = 0; a < smoothvalue; a++){
			clockstart_S = 0;
			clockend_S = 0;
			clockstart_S = rtclock(); // start clocking
			mmm_seq();
			clockend_S = rtclock(); // stop clocking
			clockAveS += (clockend_S - clockstart_S);
		}
		clockAveS = (clockAveS/smoothvalue);
		printf("\nSequential Time: %.6f sec", clockAveS);


	//Run the same test for Parallel
		parallel(); //Warm up run
		mmm_reset(P_matrixProduct);

		double clockAveP;
		double clockstart_P, clockend_P;
		//A already declared!
		for(a = 0; a < smoothvalue; a++){
			clockstart_P = 0;
			clockend_P = 0;
			clockstart_P = rtclock(); // start clocking
			parallel();
			clockend_P = rtclock(); // stop clocking
			clockAveP += (clockend_P - clockstart_P);
		}
		clockAveP = (clockAveP/smoothvalue);
		printf("\nParallel Time: %.6f sec", clockAveP);

		//Speed up!
		double speedup = (clockAveS/clockAveP);
		printf("\nSpeedup: %f",speedup);

		printf("\nVerifying... largest error between parallel and sequential matrix: %f\n", mmm_verify());
	
	mmm_freeup();

	}
	return 0;
}


