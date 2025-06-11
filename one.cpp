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

	bool Grid,Old,Prep,High_D,Patent,Mutate,Strip;
	Grid = true;
	Old = true;
	Prep = true;
	High_D = true;
	Patent = true;
	Mutate = true;
	Strip = true;
	int grid_size = 1200;
	int repeat = 10;

#ifndef GRID
	Grid = false;
#endif
#ifndef OLD
	Old = false;
#endif
#ifndef PREP
	Prep = false;
#endif
#ifndef HIGHD
	High_D = false;
#endif
#ifndef PATENT
	Patent = false;
#endif
#ifndef MUTATE
	Mutate = false;
#endif
#ifndef STRIP
	Strip = false;
#endif

#ifndef BIGGRID
	grid_size = 400;
#endif

#ifndef REPEAT
	repeat = 1;
#endif


	//1024: Make it for old
	//                                 Grid,   old, prep, high_D,patent mutate strip,rep
	punPGG gameOBJ(r,b,g,grid_size,mod,Grid, Old, Prep, High_D,Patent,Mutate,Strip,repeat);
	printf("grid_size:%d, Grid:%d, Old:%d, Prep:%d, High_D:%d, Patent:%d,Mutate:%d\n",
		grid_size, Grid,Old,Prep,High_D,Patent,Mutate);
	//                           grid,old, prep, high ,patched 
	gameOBJ.game(true,4000,50);
	return 0;
}


int main(int argc, char** argv){
	srand(time(NULL));
	double r = 4;
	double b = .5;
	double g = .9;

	do_once(r,b,g,0);
	do_once(r,b,g,1);



	return 0;
}
