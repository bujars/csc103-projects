#include <cstdio>
#include <stdlib.h> 
#include <getopt.h> 
#include <unistd.h> 
#include <vector>
#include <iostream>
using std::vector;
#include <string>
using std::string;
using std::cout;
static const char* usage =
"Usage: %s [OPTIONS]...\n"
"Text-based version of Conway's game of life.\n\n"
"   --seed,-s     FILE     read start state from FILE.\n"
"   --world,-w    FILE     store current world in FILE.\n"
"   --fast-fw,-f  NUM      evolve system for NUM generations and quit.\n"
"   --help,-h              show this message and exit.\n";

size_t max_gen = 0;
string wfilename =  "/tmp/gol-world-current";
FILE* fworld = 0;
string initfilename = "/tmp/gol-world-current";


size_t nbrCount(size_t i, size_t j, const vector<vector<bool> >& g); 
void update(); 
int initFromFile(const string& fname);
void mainLoop(); 
void dumpState(FILE* f);


char text[3] = ".O";

vector<vector<bool> > world;

int main(int argc, char *argv[]) {
		static struct option long_opts[] = {
					{"seed",    required_argument, 0, 's'},
							{"world",   required_argument, 0, 'w'},
									{"fast-fw", required_argument, 0, 'f'},
											{"help",    no_argument,       0, 'h'},
													{0,0,0,0}
						};
			char c;
				int opt_index = 0;

					while ((c = getopt_long(argc, argv, "hs:w:f:", long_opts, &opt_index)) != -1) {
								switch (c) {
												case 'h': 
																	printf(usage,argv[0]);
																					return 0;
																								case 's': 
																									initfilename = optarg; 
																													break;
																																case 'w':
																																	wfilename = optarg;
																																					break;
																																								case 'f':
																																									max_gen = atoi(optarg);
																																													break;
																																																case '?':
																																																	printf(usage,argv[0]);
																																																					return 1;
																																																							}
									}

						initFromFile(initfilename);
							mainLoop();
								


	for(size_t i = 0; i < world.size(); i++){
				for(size_t j = 0; j < world[i].size(); j++){
								if(world[i][j])
													cout << 'O';
											else
																cout << '.';
													}
						cout << "\n";
							}
		return 0;
}

int initFromFile(const string& fname){
		FILE* f = fopen(fname.c_str(),"rb");
		if(!f) exit(1);
		world.push_back(vector<bool>()); 
		size_t rows = 0; 
		vector<bool> row;
		char c;
		while(((fread(&c,1,1,f)))) {
		if (c == '\n'){
			 rows++;
		 world.push_back(row);
	} else if (c == '.'){ 			
		world[rows].push_back(false);
	} else {
		world[rows].push_back(true); 
		}
	}
	world.pop_back(); 
		fclose(f);
			

			return 0;
			}

void update(){
//#if 0
	vector<vector<bool> > newState = world;
	for(size_t i = 0; i < newState.size(); i++){
		for(size_t j = 0; j < newState[i].size(); j++){
			size_t n = nbrCount(i, j, world); //must be world bc want neighbors before changing them
				if(world[i][j] && (n < 2 || n > 3))
						newState[i][j] = false; 
				else if(world[i][j] == false && n == 3)
						newState[i][j] = true;	
				}	
			}
	world = newState;	
	
	
//#endif	

#if 0
	vector<vector<bool> > changed; 
			for(size_t i = 0; i< world.size(); i++){
						vector<bool> row;
								for(size_t j = 0; j < world[0].size(); j++){
												size_t nbr = nbrCount(i, j, world);
															if((world[i][j] == true && nbr < 2) || (world[i][j] == true && nbr > 3))
																				row.push_back(false);
																		else if(world[i][j] == false && nbr == 3)
																							row.push_back(true);
																					else
																										row.push_back(world[i][j]);
																							}
										changed.push_back(row);
											}
				world = changed; 
#endif
}

void dumpState(FILE* f){
		f = fopen(wfilename.c_str(), "wb");
			char dead = '.'; 
				char alive = 'O';
					char newRow = '\n';
						for(size_t i = 0; i < world.size(); i++){
									for(size_t j = 0; j <world[i].size(); j++){
													if(world[i][j])
																		fwrite(&alive, 1, 1, f);
																else
																					fwrite(&dead, 1, 1, f);
																		}
											fwrite(&newRow, 1, 1, f);
												}
							fclose(f);
}

void mainLoop() {
		fworld = fopen(wfilename.c_str(), "wb");
			update(); 
				dumpState(fworld); 
					int i = 1;	
						if (max_gen == 0) {
									update();
											dumpState(fworld);
													sleep(1);
														} 
							else {
										while(i < max_gen){
														update();
																	i++;
																			}
												dumpState(fworld);
													}

}

size_t nbrCount(size_t i, size_t j, const vector<vector<bool> >& g){
		size_t count = 0; 
			size_t m = g.size();
				size_t n = g[0].size();
					for(int k = -1; k < 2; k++){
								for(int h = -1; h < 2; h++){
												if(!(h==0 && k==0)){
																	int reducedI = i;
																					int reducedJ = j;
																									if((((int)i)+k) == m){
																															reducedI = ((((int)i)+k) - m) % m;
																																			}
																													else if((((int)i)+k)<0){
																																			reducedI = ((((int)i)+k) + m) % m;
																																							}
																																	else{
																																							reducedI = i+k;
																																											}
																																					if((((int)j)+h) == n){
																																											reducedJ = (((int(j))+h) - n) % n;
																																															}
																																									else if((((int)j)+h)<0){
																																															reducedJ = ((((int)j)+h) + n) % n;
																																																			}
																																													else{
																																																			reducedJ = j+h;
																																																							}				
																																																	if(!(reducedI == i && reducedJ == j) && g[reducedI][reducedJ] == true){
																																																							count++;
																																																											}
																																																				}
														
														}
									}
						return count; 
}



