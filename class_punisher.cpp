#include "class_punisher.h"
using namespace std;

punPGG::punPGG(const double rate, const double Beta, const double Gamma, 
	const int l, const int Mod,bool Grid, bool P2){
	L = l;
	LL = l * l;
	r = rate;
	beta = Beta;
	gamma = Gamma;
	mod = Mod;
	grid = Grid;
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

	if(P2 == false){
		for(int i = 0; i < LL; i++){
			int rdnum = rand() % 4;
			if(rdnum == 0)
				Strategy[i] = 0; //D
			else if (rdnum == 1) //C
				Strategy[i] = 1;
			else if (rdnum == 2) //P1
				Strategy[i] = 2;
			else
				Strategy[i] = 3; //P2

		}
	}
	else{
		for(int i = 0; i < LL; i++){
			int rdnum = rand() % 3;
			if(rdnum == 0)
				Strategy[i] = 0; //D
			else if (rdnum == 1) //C
				Strategy[i] = 1;
			else //P1
				Strategy[i] = 2;

		}
	}
}

double punPGG::unit_game(const int cent,const int to){

	double set_strat[4] = {0.0,0.0,0.0, 0.0}; 
	//0 Nd, 1 Nc, 2 Np1 3 Np2; Only neighbours
	set_strat[Strategy[cent]] += 1.0;
	for(int i = 0; i < 4; i++)
		set_strat[Strategy[Neighbour[cent][i]]] += 1.0;

	double m = (set_strat[1] * 2 >= 5) ? 2.0:1.0;
	if (mod == 1)// reverse mode
		m = 3-m;

	if(Strategy[to] == 1)
		return (r * set_strat[1] + set_strat[3] + set_strat[2]) / 5.0 - 1.0;
	if(Strategy[to] == 0)
		return (r * set_strat[1] + set_strat[3] + set_strat[2]) / 5.0 - 
				beta * (set_strat[2] + m * set_strat[3]);
	if(Strategy[to] == 2)
		return  (r * set_strat[1] + set_strat[3] + set_strat[2]) / 5.0 - 1.0 - 
				gamma * set_strat[0];

	return (r * set_strat[1] + set_strat[3] + set_strat[2]) / 5.0 - 1.0 - 
				m * gamma * set_strat[0];
}

double punPGG::centre_game(const int cent){
	double profit = unit_game(cent,cent);
	for(int i = 0; i < 4; i++){
		profit += unit_game(Neighbour[cent][i],cent);
	}

	return profit;
}


int punPGG::game(bool ptf,int rnd, int GAP){
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


	for(int i = 0; i < rnd + 1; i++){
		bool stop_all = true;
		if(i % GAP == 0){

			for (int j = 0; j < 4; j++)
				rate[j] = double (total[j]/double(LL));
			if(ptf)
				fprintf(file, "%06d %.3f %3f %3f %3f\n",i,rate[0],rate[1],rate[2],rate[3]);
			printf("%d %.3f %3f %3f %3f\n",i,rate[0],rate[1],rate[2],rate[3]);

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

		if(stop_all || stop_all_0)
			continue;

		if(grid && i % GAP == 0){
			char path2[100];

			sprintf(path2,"r_%04d_b_%04d_g_%04d_mod_%02d_i_%05d.dat",
				(int)((r + 0.000001) *100), (int)((beta + 0.000001) *100),
				(int)((gamma + 0.000001) *100), mod,i
				);

			FILE *gfile = fopen(path2,"a+");
			for(int j = 0; j < LL; j++){
				fprintf(gfile, "%d", Strategy[j]);
			}
			fclose(gfile);
		}

		for(int j = 0; j < LL; j++){
			int x = rand() % LL;
			int y = Neighbour[x][rand() % 4 ];
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