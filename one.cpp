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


	punPGG gameOBJ(r,b,g,200,mod,true,false,false,false,true);
	//                           grid,old, prep, high ,patched 
	gameOBJ.game(true,40000,400);
	return 0;
}


int main(int argc, char** argv){
	srand(time(NULL));
	double r = 2.5;
	double b = .47;
	double g = .4;

	do_once(r,b,g,0);



	return 0;
}
