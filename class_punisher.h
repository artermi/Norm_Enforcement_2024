/*
20250305: I ask ChatGPT to modify this file for me
The main changes are:
1. Threading for game() to run multiple games in parallel.
2. Refactored game_inside() with modular helper functions.
3. Thread-safe file writing using std::mutex.
4. Separate function for file handling (open_game_file()).


*/


#ifndef CLASS_PUNISHER_H
#define CLASS_PUNISHER_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>
#include <thread>
#include <mutex>

#define K 0.5

class punPGG {
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
    bool prep;
    bool pattern;
    bool high_P;

    int* Strategy;
    int** Neighbour;

    static std::mutex file_mutex;

    punPGG(double rate, double Beta, double Gamma, int l, int Mod, bool Grid = false, bool old = false,
           bool Prep = false, bool High_P = false, bool Pattern = false, bool Mutate = false, bool Strip = false, int repeat = 1);
    
    void initialise();
    double unit_game(int cent, int to);
    double centre_game(int cent);
    int game(bool ptf, int rnd, int GAP);
    int game_inside(bool ptf, int rnd, int GAP);
    
private:
    FILE* open_game_file(bool ptf);
    void write_to_file(FILE* file, int i, double rate[]);
    void initialize_game_state(double total[]);
    void update_strategy(double total[]);
    bool check_stopping_condition(double rate[], double previous[5][4], int i, int rnd);
};

#endif // CLASS_PUNISHER_H



/*
20250305: I ask ChatGPT to modify this file for me


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
*/