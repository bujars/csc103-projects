/*
 * CSc103 Project 5: Towers of Hanoi
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 *
 *
 * Finally, please indicate approximately how many hours you spent on this:
 * #hours: 
 */

// TODO: write the program.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <getopt.h> // to parse long arguments.
#include <cstdlib> // for atoi function

void towersOfHanoi(short n, short start, short end);

/* Here's a skeleton main function for processing the arguments. */
int main(int argc, char *argv[]) {
	// define long options
	static struct option long_opts[] = {
		{"start",        required_argument, 0, 's'},
		{"end",          required_argument, 0, 'e'},
		{"num-disks",    required_argument, 0, 'n'},
		{0,0,0,0} // this denotes the end of our options.
	};
	// now process the options:
	char c; // to hold the option
	int opt_index = 0;
	short n=0,start=0,end=0; /* to store inputs to the towers function. */
	while ((c = getopt_long(argc, argv, "s:e:n:", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 's': // process option s
				start = atoi(optarg);
				break;
			case 'e': // process option e
				end = atoi(optarg);
				break;
			case 'n': // process option n
				n = atoi(optarg);
				break;
			case '?': // this will catch unknown options.
				// here is where you would yell at the user.
				// although, getopt will already print an error message.
				return 1;
		}
	}

	/* TODO: now that you have the options and arguments,
	 * solve the puzzle. */

	if(n < 0 || start < 1 || start >3 || end < 1 || end > 3)
		return 1;
	else
		towersOfHanoi(n, start, end);
	return 0;
}

/*
 * Do all the moving until you get the very last one, or n, onto the end base.
 * ONce that occurs, take all of the steps that you made, but this time do it on the invertred pegs. Meanging if u first step was from one to 2, this time you would be going from 2 to 3?? You start becomes the next one over??? Not sure needs more thought put into it. 
 *
 * There seems to be a trend where the odd ones goes to the most at right, and for even it goes to the at left one....
 *
 * */

void towersOfHanoi(short n, short start, short end){
	if(n == 1){ cout << start << "\t" << end << "\n"; return; }
	//cout<< start << "\t" << end << "\n";
	towersOfHanoi(n-1, start, 6-(start+end));
	cout<< start << "\t" << end << "\n";
	towersOfHanoi(n-1, 6-(start+end), end);
	//cout<< start << "\t" << end << "\n";

}

