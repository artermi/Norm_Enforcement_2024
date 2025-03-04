#include "class_punisher.h"
using namespace std;


//Perhaps I should use threading to implement the thing.

punPGG::punPGG(const double rate, const double Beta, const double Gamma, 
	const int l, const int Mod,bool Grid, bool Old,bool Prep,bool High_P,
	bool Pattern, bool Mutate, bool Strip, int repeat){
	L = l;
	LL = l * l;
	r = rate;
	beta = Beta;
	gamma = Gamma;
	mod = Mod;
	Repeat = repeat;
	grid = Grid;
	old = Old;
	mutate = Mutate;
	strip = Strip;
	//Add the pattern state into the initial value;
	prep = Prep;
	pattern = Pattern;
	high_P = High_P;

	//strcpy(dir_name,"Fixed");
	Strategy = new int[LL];
	Neighbour = new int *[LL];

	for(int i = 0; i < LL; i++)
		Neighbour[i] = new int[4];

	for(int i = 0; i < LL; i++){
		Neighbour[i][0] = (i - L + LL ) % LL; //North
		Neighbour[i][1] = (i + L) % LL;
		Neighbour[i][2] = (i + 1) % LL;
		Neighbour[i][3] = (i - 1 + LL) % LL;
	}//initialise the neighbour

//	initialise();

}

void punPGG::initialise(){
	if (prep){
		for(int i = 0; i<LL; i++){
			Strategy[i] = 0;
			int dimX = ( i % L >= L/2 )? 1:0;
			int dimY =  (i/L >= L/2)? 2:0;
			Strategy[i] += dimY + dimX; 
		}

	}
	else if(pattern){
		int pt_L = 20;
		int Pattern_Table[pt_L*pt_L];
		for(int i=0; i <pt_L*pt_L;i++){
			Pattern_Table[i] = rand()%4;
		}
		int b_s = L/pt_L; //block size
		for(int i=0;i<LL;i++)
			Strategy[i] = Pattern_Table[ i%L /b_s + (i/L)/(b_s)*pt_L];
		//i/L is the row num, i%L is column num;
		//


	}
	else if(strip){
		for (int i = 0; i < LL; ++i)
		{
			//P1 (2) -> D (0) -> P2 (3) -> C (1)
			int order_map[4] = {2,0,3,1};
			Strategy[(i + 25*L) % LL] = order_map[(i / L) / (L/4)];
		}
	}
	else{
		for(int i = 0; i < LL; i++){
			int rdnum = rand() % 4;
			Strategy[i] = rdnum;
		}
		if(high_P){
		for(int i = 0; i < LL; i++){
				int rdnum = rand() % 10;
			if(rdnum < 5)
				Strategy[i] = 0; //D
			else if (rdnum < 8) //C
				Strategy[i] = 1;
			else if (rdnum  < 9) //P1 or O
				Strategy[i] = 2;
			else
				Strategy[i] = 3; //P2 or E

		}

		}
	}

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

int punPGG::game(bool ptf,int rnd, int GAP){
	for (int i = 0; i < Repeat; ++i){
		initialise();
		game_inside(ptf,rnd,GAP);
	}
	return 0;
}


int punPGG::game_inside(bool ptf,int rnd, int GAP){
	FILE *file;
	if(ptf){
		char path[100];
		sprintf(path,"r_%04d_b_%04d_g_%04d_mod_%02d.dat",
			(int)((r + 0.000001) *100), (int)((beta + 0.000001) *100),
			(int)((gamma + 0.000001) *100), mod
			);

		file = fopen(path,"a+");
		printf("Now file:%s\n",path);
	}

	double total[4] = {0.0,0.0,0.0,0.0};
		for(int j = 0; j < LL; j++)
			total[Strategy[j]] += 1.0;
	double rate[4] = {0.0,0.0,0.0,0.0};
	double previous[5][4];

	bool stop_all_0 = true;
	bool b4_first_stop = true;
	int RND = (rnd/GAP) * GAP; //make sure rnd is GAP's multiplier

	for(int i = 0; i < RND + 1; i++){
		bool stop_all = true;
		if(i % GAP == 0){

			for (int j = 0; j < 4; j++)
				rate[j] = double (total[j]/double(LL));
			if(ptf && (Repeat == 1 || (Repeat > 1 && i == RND)) ){
				//Add a new request for the repeat case: on print the last one.
				//If threading, I need to have a mutex here?
				fprintf(file, "%06d %.3f %3f %3f %3f\n",i,rate[0],rate[1],rate[2],rate[3]);
				printf("%d %.3f %3f %3f %3f\n",i,rate[0],rate[1],rate[2],rate[3]);
			}
			double pert = 0.002;
			for(int j = 1; j < 5; j++)
				for(int k = 0; k < 4; k ++)
					previous[j-1][k] = previous[j][k];
			for(int k = 0; k < 4; k++)
				previous[4][k] = rate[k];

			if(i > rnd/2){
				stop_all_0 = true;

				for(int j = 0; j < 5; j++)
					for(int k = 0; k < 4; k ++)
						if(abs(rate[k] - previous[j][k]) > pert){
							stop_all_0 = false;
						}
			}
			else{
				stop_all_0 = false;
			}
		}
		if(i == rnd)
			continue;
		for (int j = 0; j < 4; j++)
			if(rate[j] - 0.00000001 >= 0 && rate[j] + 0.00000001 <= 1)
				stop_all = false;


		if(grid && i % GAP == 0 && b4_first_stop){
			char path2[100];

			sprintf(path2,"r_%04d_b_%04d_g_%04d_mod_%02d_i_%05d.dat",
				(int)((r + 0.000001) *100), (int)((beta + 0.000001) *100),
				(int)((gamma + 0.000001) *100), mod,i
				);

			FILE *gfile = fopen(path2,"w+");
			for(int j = 0; j < LL; j++){
				fprintf(gfile, "%d", Strategy[j]);
			}
			fclose(gfile);
			if(stop_all || stop_all_0)
				b4_first_stop = false;
		}

		if(stop_all || stop_all_0)
			continue;

		for(int j = 0; j < LL; j++){
			int x = rand() % LL;
			int y = Neighbour[x][rand() % 4 ];

			if (mutate){
				if( rand() % 1000000 == 0){
					total[Strategy[x]] --;
					Strategy[x] = rand() % 4;
					total[Strategy[x]] ++;
				}
			}
			if (Strategy[x] == Strategy[y])
				continue;
//			cout << x << ',' << y <<endl;
			double x_earn = centre_game(x);
			double y_earn = centre_game(y);

			if ((double)rand()/(double)RAND_MAX < 1.0/( 1.0 + exp((y_earn - x_earn)/K) ) ){
				total[Strategy[y]] --;
				Strategy[y] = Strategy[x];
				total[Strategy[y]] ++;
			}
		}
	}
	if(ptf)
		fclose(file);

	return 0;
}
