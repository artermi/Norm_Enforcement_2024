/*
20250305: I ask ChatGPT to modify this file for me
The main changes are:
1. Threading for game() to run multiple games in parallel.
2. Refactored game_inside() with modular helper functions.
3. Thread-safe file writing using std::mutex.
4. Separate function for file handling (open_game_file()).


However, I need to add the using namespace back.

I haven't try running this code. But I shall do it sometimes.
*/


#include "class_punisher.h"
using namespace std;

#include <unistd.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <fcntl.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <iomanip>

//mutex punPGG::file_mutex;

punPGG::punPGG(double rate, double Beta, double Gamma, int l, int Mod, bool Grid, bool Old, bool Prep, bool High_P,
               bool Pattern, bool Mutate, bool Strip, int repeat)
    : r(rate), beta(Beta), gamma(Gamma), L(l), LL(l * l), mod(Mod), Repeat(repeat),
      grid(Grid), old(Old), mutate(Mutate), strip(Strip), prep(Prep), pattern(Pattern), high_P(High_P) {
    
    Strategy = new int[LL];
    Neighbour = new int*[LL];

    for (int i = 0; i < LL; i++)
        Neighbour[i] = new int[4];

    for (int i = 0; i < LL; i++) {
        Neighbour[i][0] = (i - L + LL) % LL;
        Neighbour[i][1] = (i + L) % LL;
        Neighbour[i][2] = (i + 1) % LL;
        Neighbour[i][3] = (i - 1 + LL) % LL;
    }
}

void punPGG::initialise() {
    if (prep) {
        for (int i = 0; i < LL; i++) {
            Strategy[i] = 0;
            int dimX = (i % L >= L / 2) ? 1 : 0;
            int dimY = (i / L >= L / 2) ? 2 : 0;
            Strategy[i] += dimY + dimX;
        }
    } else if (pattern) {
        int pt_L = 20;
        int Pattern_Table[pt_L * pt_L];
        for (int i = 0; i < pt_L * pt_L; i++) {
            Pattern_Table[i] = rand() % 4;
        }
        int b_s = L / pt_L;
        for (int i = 0; i < LL; i++)
            Strategy[i] = Pattern_Table[i % L / b_s + (i / L) / (b_s) * pt_L];
    } else if (strip) {
        for (int i = 0; i < LL; ++i) {
            int order_map[4] = {2, 0, 3, 1};
            Strategy[(i + 25 * L) % LL] = order_map[(i / L) / (L / 4)];
        }
    } else {
        for (int i = 0; i < LL; i++) {
            int rdnum = rand() % 4;
            Strategy[i] = rdnum;
        }
        if (high_P) {
            for (int i = 0; i < LL; i++) {
                int rdnum = rand() % 10;
                if (rdnum < 5)
                    Strategy[i] = 0;
                else if (rdnum < 8)
                    Strategy[i] = 1;
                else if (rdnum < 9)
                    Strategy[i] = 2;
                else
                    Strategy[i] = 3;
            }
        }
    }
}

void punPGG::initialize_game_state(double total[]) {
    for (int j = 0; j < LL; j++)
        total[Strategy[j]] += 1.0;
}

double punPGG::unit_game(const int cent,const int to){

	double set_strat[4] = {0.0,0.0,0.0, 0.0}; 
	//0 Nd, 1 Nc, 2 Np1 3 Np2; Only neighbours
	set_strat[Strategy[cent]] += 1.0;
	for(int i = 0; i < 4; i++)
		set_strat[Strategy[Neighbour[cent][i]]] += 1.0;

	double m = (set_strat[0] * 2 >= 5) ? 1.0:2.0;
	if (mod == 1)// reverse mode
		m = 3-m;

	double fNO = (set_strat[2] > 0) ? 1.0:0.0;
	
	if(old){
		m = 1;
	}

	double Pc = r * (set_strat[1] + set_strat[2] + set_strat[3]) / 5.0 -1.0;


	if(Strategy[to] == 0)
		return (old)? 
		Pc + 1 - beta * (fNO + m * set_strat[3])
		: Pc + 1 - beta * (set_strat[2] + m * set_strat[3]);

	if(Strategy[to] == 1)
		return Pc;

	if(Strategy[to] == 2) //P1 or O
		return  (old) ? Pc - gamma : Pc - gamma * set_strat[0];

	return Pc - m * gamma * set_strat[0]; //P2 or E
}

double punPGG::centre_game(const int cent){
	double profit = unit_game(cent,cent);
	for(int i = 0; i < 4; i++){
		profit += unit_game(Neighbour[cent][i],cent);
	}

	return profit;
}

void punPGG::update_strategy(double total[]) {
    for (int j = 0; j < LL; j++) {
        int x = rand() % LL;
        int y = Neighbour[x][rand() % 4];

        if (mutate && (rand() % 1000000 == 0)) {
            total[Strategy[x]]--;
            Strategy[x] = rand() % 4;
            total[Strategy[x]]++;
        }
        if (Strategy[x] == Strategy[y])
            continue;

        double x_earn = centre_game(x);
        double y_earn = centre_game(y);

        if ((double)rand() / (double)RAND_MAX < 1.0 / (1.0 + exp((y_earn - x_earn) / K))) {
            total[Strategy[y]]--;
            Strategy[y] = Strategy[x];
            total[Strategy[y]]++;
        }
    }
}

bool punPGG::check_stopping_condition(double rate[], double previous[5][4], int i, int rnd) {
    double pert = 0.002;
    bool stop_all_0 = true;
    bool stop_all = true;

    for (int j = 1; j < 5; j++)
        for (int k = 0; k < 4; k++)
            previous[j - 1][k] = previous[j][k];

    for (int k = 0; k < 4; k++)
        previous[4][k] = rate[k];

    if (i > rnd / 2) {
        for (int j = 0; j < 5; j++)
            for (int k = 0; k < 4; k++)
                if (fabs(rate[k] - previous[j][k]) > pert)
                    stop_all_0 = false;
    } else {
        stop_all_0 = false;
    }

    for (int j = 0; j < 4; j++)
        if (rate[j] - 0.00000001 >= 0 && rate[j] + 0.00000001 <= 1)
            stop_all = false;

    return stop_all || stop_all_0;
}


void punPGG::write_to_file(int i) {
	FILE* file = open_game_file(true, i, true);
    //lock_guard<mutex> lock(file_mutex);
    for (int i = 0; i < LL; ++i)
        {fprintf(file,"%d",Strategy[i]);
    }
    
    fclose(file);
}

void punPGG::print_to_screen(int i, double rate[]){
	printf("%d %.3f %.3f %.3f %.3f\n", i, rate[0], rate[1], rate[2], rate[3]);
}


FILE* punPGG::open_game_file(bool ptf, int i = -1, bool snap = false) {
    if (!ptf) return nullptr;

    char path[100];
    if(snap){
        sprintf(path, "r_%04d_b_%04d_g_%04d_mod_%02d_i_%05d.dat",
            (int)((r + 0.000001) * 100), (int)((beta + 0.000001) * 100),
            (int)((gamma + 0.000001) * 100), mod,i);

    }
    else
        sprintf(path, "r_%04d_b_%04d_g_%04d_mod_%02d.dat",
                (int)((r + 0.000001) * 100), (int)((beta + 0.000001) * 100),
                (int)((gamma + 0.000001) * 100), mod);

    //lock_guard<mutex> lock(file_mutex);
    FILE* file = fopen(path, "a+");
    if (!file) {
        printf("Failed to open file: %s\n", path);
        return nullptr;
    }

    return file;
}

int punPGG::game_inside(bool ptf, int rnd, int GAP, stringstream& buffer) {
    if (ptf) {
        printf("Now working: (%f,%f,%f,%d)\n", r,beta,gamma,mod);
    }

    double total[4] = {0.0, 0.0, 0.0, 0.0};
    initialize_game_state(total);

    double rate[4] = {0.0, 0.0, 0.0, 0.0};
    double previous[5][4] = {0};

    for (int i = 0; i < rnd; i++) {
        if (i % GAP == 0) {
            for (int j = 0; j < 4; j++)
                rate[j] = total[j] / double(LL);

#ifdef DEBUG
            print_to_screen(i, rate);
#endif

            // === Case 1: Final write if Repeat == 1 or i == rnd
            if (ptf && (Repeat == 1 || (Repeat > 1 && i == rnd))) {
                buffer << setw(6) << setfill('0') << i << " "
                       << fixed << setprecision(3)
                       << rate[0] << " " << rate[1] << " "
                       << rate[2] << " " << rate[3] << "\n";
                print_to_screen(i, rate);

#ifdef GRID
                write_to_file(i);
#endif
            }

            // === Case 2: Early stopping condition → still output
            if (check_stopping_condition(rate, previous, i, rnd)) {
                if (ptf && Repeat > 1) {
                    buffer << setw(6) << setfill('0') << i << " "
                           << fixed << setprecision(3)
                           << rate[0] << " " << rate[1] << " "
                           << rate[2] << " " << rate[3] << "\n";
                    print_to_screen(i, rate);
#ifdef GRID
                    write_to_file(i);
                    //printf("Buffer: %s\n", buffer.str().c_str());
#endif
                }
                break;
            }
        }

        update_strategy(total);
    }

    return 0;
}
    

int punPGG::game(bool ptf, int rnd, int GAP) {
    const int MAX_PROCS = 10;
    int num_procs = std::min(Repeat, MAX_PROCS);
    int games_per_proc = Repeat / num_procs;
    int extra = Repeat % num_procs;

    std::vector<pid_t> children;

    for (int i = 0; i < num_procs; ++i) {
        int runs = games_per_proc + (i < extra ? 1 : 0);
        pid_t pid = fork();

        if (pid == 0) {
            // --- CHILD PROCESS ---
            srand(time(NULL) ^ getpid());  // Ensure different seeds per child
            std::stringstream buffer;
            for (int j = 0; j < runs; ++j) {
                punPGG local_game(*this);
                local_game.initialise();
                local_game.game_inside(ptf, rnd, GAP, buffer);
            }

            // --- Write to final file with file lock ---
            if (ptf) {
#ifdef DEBUG
                    printf("Final Buffer: %s\n", buffer.str().c_str());
#endif  
                FILE* final_file = open_game_file(true);
                if (final_file) {
                    int fd = fileno(final_file);
                    flock(fd, LOCK_EX); // Acquire lock           
                    fputs(buffer.str().c_str(), final_file);               
                    fflush(final_file);
                    flock(fd, LOCK_UN); // Release lock
                    fclose(final_file);
                }
            }

            _exit(0); // Safely exit child
        }
        else if (pid > 0) {
            children.push_back(pid);
        }
        else {
            perror("fork failed");
            return 1;
        }

        // Throttle: wait if too many children
        while ((int)children.size() >= MAX_PROCS) {
            int status;
            wait(&status);
            children.pop_back();
        }
    }

    // Wait for remaining children
    for (pid_t pid : children) {
        waitpid(pid, nullptr, 0);
    }

    return 0;
}
