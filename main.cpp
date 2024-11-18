#include "class_punisher.h"
#include <unistd.h>
using namespace std;

int do_once(double r, double b, double g, int mod){
	printf("Now doing punisher with (r,beta,gamma,mod) = (%f,%f,%f,%d)\n",
		r,b,g,mod);
	char file_n[100];
	sprintf(file_n,"r_%04d_b_%04d_g_%04d_mod_%02d.dat",
			(int)((r + 0.000001) *100), (int)((b + 0.000001) *100),
			(int)((g + 0.000001) *100), mod
			);

	FILE *file;
  	file = fopen(file_n, "r");

	if (file) {
		fclose(file);
		printf("file:'%s' exists\n",file_n);
		usleep(100000);
		return 0;
	}

	file = fopen(file_n, "w");
	fclose(file);

	//1024: Make it for old
	//                           Grid, old, prep, high_D,patent
	punPGG gameOBJ(r,b,g,600,mod,false,false,false,false,true);
	gameOBJ.game(true,10000,100);

	return 0;
}


int main(int argc, char** argv){
	srand(time(NULL));

//	double r = 3.5;



	for(double r = 2.5; r < 5.01; r += 0.5 ){
		for(double b = 0; b < 1.01; b += 0.1){
			for (double g = 0.0; g < 1.01; g += 0.1){
					do_once(r,b,g,0);
			}
		}
	}


	return 0;
}
