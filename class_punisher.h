#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>


#define K 0.5

class punPGG{
public:
	long long rnd;
	double r;
	double beta;
	double gamma;
	int L;
	int LL;
	int mod;
	int Repeat;
	double grid;
	bool old;
	bool mutate;
	bool strip;
	//char dir_name[100];

	bool prep;
	bool pattern;
	bool high_P;

	int* Strategy; // 0 for Defactor, 1 for Cooperator, 2 for Punisher
	int** Neighbour;
	//int MST_N[LL];
	//int Next_MST_N[LL];
	//double probs[LL];
	//long long curr[LL];

	punPGG(const double rate, const double Beta, const double Gamma,
		const int l, const int Mod, bool Grid = false, bool old = false,
		bool Prep = false, bool High_P = false, bool Pattern = false,
		bool Mutate = false, bool Strip=false, int repeat = 1);
	void initialise();
	double unit_game(const int cent,const int to);
	double centre_game(const int cent);
	int game(bool ptf,int rnd, int GAP);
	int game_inside(bool ptf,int rnd, int GAP);
};