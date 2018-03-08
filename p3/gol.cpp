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
 * #hours: 10
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

vector<vector<bool> > world;



/* NOTE: you don't have to write these functions -- this is just how
 * I chose to organize my code. */

//Pasrt you can ignore from skeleton.
size_t nbrCount(size_t i, size_t j, const vector<vector<bool> >& g); //count neighbors of cell i, j on grid g
void update(); //transform the old version of the world into the new one
int initFromFile(const string& fname); /* read initial state into vectors. */
void mainLoop(); //update state, write state, sleep, repeat...
void dumpState(FILE* f); //write the state to a file

char text[3] = ".O";


//vector<vector<bool> > world;


int main(int argc, char *argv[]) {
	// define long options
	static struct option long_opts[] = {
		{"seed",    required_argument, 0, 's'},
		{"world",   required_argument, 0, 'w'},
		{"fast-fw", required_argument, 0, 'f'},
		{"help",    no_argument,       0, 'h'},
		{-1,0,0,0}
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

	//cin >> file
	//stdin >> wfile;

	/* NOTE: at this point wfilename initfilename and max_gen
	 * are all set according to the command line. */
	/* If you wrote the initFromFile function, call it here: */
	//int fille = initFromFile(initfilename);
	mainLoop();
	return 0;
}

//Counting neighbors of cell i,j on grid g:
//note vectors are v[i][j] i = rows j = columns ..... They produce a grid...
size_t nbrCount(size_t i, size_t j, const vector<vector<bool> >& world){
	/*for(size_t a = 0, a < world.size(); a++){

	}*/
	return 0; 
}

/* NOTE NOTE NOTE: This is where I believe the initFromFile(initfilename) function is called. 
 * I believe this program is a little similar to the gravity program.... 
 * where you input the text name, give it to the program, 
 * the program generates the output 
 * and then the it is played/presented on the screen. */
int initFromFile(const string& fname){ /* read initial state into vectors. */
	//This should be global?... //vector<vector<bool> > world;
	//NOTE NOTE NOTE its wfname because it was already set... as a global variable
#if 0 	
	FILE* f = fopen(fname.c_str(), "rb"); //Make sure you cin the file name...
	world.push_back(vector<bool>()); //add a new row....why is this outside the loop? how do we add more?????
	size_t rows = 0; //Curent row getting filled
	char c;
	while(fread(&c, 1, 1, f))
	{
		if(c == '\n'){
			rows++;
			world.push_back(vector<bool>());
		/*NOTE NOTE NOTE this is adding new rows when a new line is deteced, since we are going row by row. */
		}
		else if(c == '.'){ //if the current character we are reading is a dot,
			world[rows].push_back(false); //set it to false, or in this case dead
		}
		else {
			world[rows].push_back(true); //set it to true, or in this case alive
		}
	}
	fclose(f);
#endif



	//Note this was just copied from Skeiths Stuff.... You stuff was just missing the char c and you had c == "\n" not '\n'
#if 0
	vector<vector<bool> > world;
	FILE* f = fopen(wfilename.c_str(),"rb"); /* note conversion to char* */
	world.push_back(vector<bool>()); /* add a new row */
	size_t rows = 0; /* current row we are filling */
	char c;
	while (fread(&c,1,1,f)) {
		if (c == '\n'){
		/* found newline; add a new row */
			 rows++;
			 world.push_back(vector<bool>());
		} else if (c == '.') {
			world[rows].push_back(false); /* dead x_x */
		} else {
			world[rows].push_back(true); /* alive 8D */
		 }
	}
	fclose(f);
#endif
	/* Open the file (for reading), storing the handle in f: */
	FILE* f = fopen("/path/to/myfile","rb");
	/* make sure file was opened properly: */
	if (!f) {
		    // deal with error by printing a message, or maybe quitting
			//     // the entire program with a non-zero exit code, like this:
		 exit(1);
	}
			//         /* Read a single character from the file: */
	char c; // storage for the byte we'll read
	fread(&c,1,1,f); // read one byte, place it in c
	/* when you're done with the file, be sure to close it like this: */
	 fclose(f);




	return 0;
}

void update() //transform the old version of the world into the new one
{
	//AGAIN notices the wfname as this should be the file name variable that was already set at the start.....
	/*FILE* f = fopen(fname.c_str(), "wb");
	rewind(f); //this is so that we start from the beginning of each file.
	char c = ".";
	fwrite(&c, 1, 1, f);
	fclose(f);*/
}


void mainLoop() {
	/* TODO: write this */
	/* update, write, sleep */
	
	
	//Update means get the new positions of the .0
	//write means reopen the file and rewind all the way up and the transfer the code into .0
	//sleep means take a pause
	//sleep(1); //so we take a break
	//max_gen must be inputted im assuming??
	
	
	if (max_gen == 0) {
		/* make one generation update per second */
	} 
	else {
		/* go through generations as fast as you can until
		 * max_gen is reached... */
	}


	///Additioal Notes:  
	//If a future generation is given, 
	//we do not pause for time, 
	//we want it to skip ahead, 
	//otherwise keep pausing as we go.

}






