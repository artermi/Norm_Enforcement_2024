#include "class_punisher.h"
#include <unistd.h>
using namespace std;

int do_once(double r, double b, double g, int mod, bool isRandom){
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

	bool pat = not isRandom;


	punPGG gameOBJ0(r,b,g,600,mod,true,true,false,false,pat);
	punPGG gameOBJ1(r,b+0.1,g,600,mod,true,true,false,false,pat);
	punPGG gameOBJ2(r,b-0.1,g,600,mod,true,true,false,false,pat);
	punPGG gameOBJ3(r,b,g+0.1,600,mod,true,true,false,false,pat);
	punPGG gameOBJ4(r,b,g-0.1,600,mod,true,true,false,false,pat);

	//                           grid,old, prep, high ,patched 
	gameOBJ0.game(true,2001,250);
	gameOBJ1.game(true,2001,250);
	gameOBJ2.game(true,2001,250);
	gameOBJ3.game(true,2001,250);
	gameOBJ4.game(true,2001,250);

	return 0;
}


int main(int argc, char** argv){
	srand(time(NULL));
	double r = 2;
	double b = 2.2;
	double g = .8;
	int mode = 1;

	bool Israndom = true;
if(Israndom){ 
	do_once(2.5,.5,.4, mode,Israndom);
	do_once(3,.4,.4, mode,Israndom);
	do_once(3.5,.4,.5, mode,Israndom);
	do_once(4,.4,.6, mode,Israndom);
	do_once(4.5,.4,.7, mode,Israndom);
	do_once(5,.3,.7, mode,Israndom);
}
else{
	do_once(2.5,.6,.5, mode,Israndom);
	do_once(3,.5,.5, mode,Israndom);
	do_once(3.5,.2,.3, mode,Israndom);
	do_once(4,.3,.5, mode,Israndom);
	do_once(4.5,.3,.6, mode,Israndom);
	do_once(5,.2,.6, mode,Israndom);

}





	return 0;
}
