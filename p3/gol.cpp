/*
 * CSc103 Project 3: Game of Life
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 * 
 * TA: Ben Wu
 * stackoverflow.com/questions/19672301/checking-out-of-bounds-in-java  
 * IDEA: //Helped me realized that I need to make sure my indexes are within 0, the start of the grid, or the vector, column/row length
 * stackoverflow.com/questions/9694838/how-to-implement-2d-vector-array 
 * IDEA: //Helped me form the 2D array
 * groups.google.com/forum/m/#!topic/comp/lang.java.help/qshQBJ-1rFk 
 * IDEA://Helped me realized that the neighbor count can be greatly simplified -- then went for Skeith's help 3/6/18
 * en.cppreference.com/w/cpp/types/size_t 
 * IDEA: //Help me figure out the negative fault.
 * bitstorm.org/gameoflife/
 * web.stanford.edu/~cdebs/GameOfLife/


 * Finally, please indicate approximately how many hours you spent on this:
 * #hours: 30
 */

#include <cstdio>
#include <stdlib.h> // for exit();
#include <getopt.h> // to parse long arguments.
#include <unistd.h> // sleep
#include <vector>
using std::vector;
#include <string>
using std::string;

static const char* usage =
"Usage: %s [OPTIONS]...\n"
"Text-based version of Conway's game of life.\n\n"
"   --seed,-s     FILE     read start state from FILE.\n"
"   --world,-w    FILE     store current world in FILE.\n"
"   --fast-fw,-f  NUM      evolve system for NUM generations and quit.\n"
"   --help,-h              show this message and exit.\n";

size_t max_gen = 0; /* if > 0, fast forward to this generation. */
string wfilename =  "/tmp/gol-world-current"; /* write state here */
FILE* fworld = 0; /* handle to file wfilename. */
string initfilename = "/tmp/gol-world-current"; /* read initial state from here. */

size_t nbrCount(size_t i, size_t j, const vector<vector<bool> >& g); //count neighbors of cell i, j on grid g
void update(); //transform the old version of the world into the new one
int initFromFile(const string& fname); /* read initial state into vectors. */
void mainLoop(); //update state, write state, sleep, repeat...
void dumpState(FILE* f); //write the state to a file
//void dumpState(const string& fname);

char text[3] = ".O";

vector<vector<bool> > world;

int main(int argc, char *argv[]) {
	// define long options
	static struct option long_opts[] = {
		{"seed",    required_argument, 0, 's'},
		{"world",   required_argument, 0, 'w'},
		{"fast-fw", required_argument, 0, 'f'},
		{"help",    no_argument,       0, 'h'},
		{0,0,0,0}
	};
	// process options:
	char c;
	int opt_index = 0;

	/* NOTE NOTE NOTE: What this is doing is taking in the filename
	and everything. Wher eyou usually do cin>>, this code is doing
	it as provided by the sketlon. This is not something you need to
	worry about. Updated: March 5th, 2018 -- Told by Ben on March 2
	nd. */

	//Parts in Main that you must keep, but don't worry about it. Just know what it accomplishes
	while ((c = getopt_long(argc, argv, "hs:w:f:", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'h': //If someone gives -h or --help, it just prints a help screen
				printf(usage,argv[0]);
				return 0;
			case 's': //-s or --speed
				//have to open this to see the dots and 0s
				initfilename = optarg; //This is the argument after -s
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

	/* NOTE: at this point wfilename initfilename and max_gen
	 * are all set according to the command line. */
	/* If you wrote the initFromFile function, call it here: */
	//note its called initfilename as thats the global variable of the file that gets stored. 
	initFromFile(initfilename);
	mainLoop();	
	return 0;
}

/* NOTE NOTE NOTE: This is where I believe the initFromFile(initfilename) function is called. 
 * I believe this program is a little similar to the gravity program.... 
 * where you input the text name, give it to the program, 
 * the program generates the output 
 * and then the it is played/presented on the screen. */
	//int initFromFile(const string& fname){ /* read initial state into vectors. */
	//This should be global?... //vector<vector<bool> > world;
	//NOTE NOTE NOTE its wfname because it was already set... as a global variable

int initFromFile(const string& fname){ /* read initial state into vectors. */
	FILE* f = fopen(fname.c_str(),"rb"); /* note conversion to char* */
	if(!f){
		exit(1);
	}
	world.push_back(vector<bool>()); /* add a new row */
	size_t rows = 0; /* current row we are filling */
	vector<bool> row;
	char c;
	while(((fread(&c,1,1,f)))) {
		if (c == '\n'){
		/* found newline; add a new row */
			 rows++;
			 world.push_back(row);
			 //world.push_back(rows); //this is so ew insert a new row into our world.
		} else if (c == '.') {
			world[rows].push_back(false); /* dead x_x */
		} else {
			world[rows].push_back(true); /* alive 8D */
		 }
	}
	world.pop_back();
	fclose(f);
	return 0;
}

void update(){
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

}

void dumpState(){ //note f here becomes wfilename from mainloop
	char dead = '.'; //to make dead thing
	char alive = 'O'; //to make a live thing
	char newRow = '\n';//To make a new row. 
	//rewind(f);
	if(wfilename == "-"){
		for(size_t i = 0; i < world.size(); i++){
			for(size_t j = 0; j <world[i].size(); j++){
				if(world[i][j])//positive/true = alive
					fwrite(&alive, 1, 1, stdout);
				else
					fwrite(&dead, 1, 1, stdout);
				}
			fwrite(&newRow, 1, 1, stdout);
			}
		}
	else{
		FILE* f = fopen(wfilename.c_str(), "wb");
		for(size_t i = 0; i < world.size(); i++){
			for(size_t j = 0; j <world[i].size(); j++){
				if(world[i][j])//positive/true = alive
					fwrite(&alive, 1, 1, f);
				else
					fwrite(&dead, 1, 1, f);
			}
			fwrite(&newRow, 1, 1, f);
		}	
		fclose(f);
	}
}

void mainLoop(){
	/* TODO: write this */
	/* update, write, sleep */	
	//fworld = fopen(wfilename.c_str(), "wb");
	//update(); //this puts the new positions. Inside neighbor count is also called. 
	//dumpState(); //fworld is a global variable hat was set by skeith
	size_t i = 0;
	if(max_gen == 0){
		while(true){
			//while(true) {
			update();
			dumpState();
			sleep(1);
			i++;
		}
	}
	else {
		while(i < max_gen){
			update();
			i++;
		}
		dumpState(); 
	}
}

size_t nbrCount(size_t i, size_t j, const vector<vector<bool> >& g){
	size_t count = 0; //The number of neighbors
	size_t m = g.size(); //holds row length
	size_t n = g[0].size(); //holds column length
	//cout << "The value i " << i << " j " << j << " \n";	
	

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














