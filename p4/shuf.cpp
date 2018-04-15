#include <cstdio>   // printf
#include <cstdlib>  // rand
#include <time.h>   // time
#include <getopt.h> // to parse long arguments.
#include <stdlib.h>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <iostream>
using std::cin;
using std::cout;
#include <algorithm>
using std::swap;
using std::min;

static const char* usage =
"Usage: %s [OPTIONS]...\n"
"Limited clone of shuf.  Supported options:\n\n"
"   -e,--echo              treat each argument as an input line.\n"
"   -i,--input-range=LO-HI treat each number in [LO..HI] as an input line.\n"
"   -n,--head-count=N      output at most N lines.\n"
"   --help                 show this message and exit.\n";

void randPerm(vector<string>& v);

void randPermString(vector<string>& v);
void randPermInt(vector<int>& v);

int main(int argc, char *argv[]) {
	// define long options
	static int echo=0, rlow=0, rhigh=0;
	static size_t count=-1;
	bool userange = false;
	static struct option long_opts[] = {
		{"echo",        no_argument,       0, 'e'},
		{"input-range", required_argument, 0, 'i'},
		{"head-count",  required_argument, 0, 'n'},
		{"help",        no_argument,       0, 'h'},
		{0,0,0,0}
	};
	// process options:
	char c;
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "ei:n:h", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'e':
				echo = 1;
				break;
			case 'i':
				if (sscanf(optarg,"%i-%i",&rlow,&rhigh) != 2) {
					fprintf(stderr, "Format for --input-range is N-M\n");
					rlow=0; rhigh=-1;
				} else {
					userange = true;
				}
				break;
			case 'n':
				count = atol(optarg);
				break;
			case 'h':
				printf(usage,argv[0]);
				return 0;
			case '?':
				printf(usage,argv[0]);
				return 1;
		}
	}
	/* NOTE: the system's shuf does not read stdin *and* use -i or -e.
	 * Even -i and -e are mutally exclusive... */

	/* TODO: write me... */
#if 0
	vector<string> v;
	while(optind < argc){
		v.push_back(argv[optind++]);
	}
	randPerm(v);
	if(echo){
		for(size_t i = 0; i < v.size(); i++){
			cout << v[i] << "\n";
		}
	}
	if((int)count > 0){
		for(size_t i = 0; i < count; i++){
			cout << v[i] << "\n";
		}
	}
	if(userange){
		for(size_t i = rlow; i < rhigh; i++){
			cout << v[i] << "\n";
		}
	}
#endif


	vector<string> s; /*vector for everthing not -i */
	vector<int> I; /* vector of ints for -i*/
	if(echo){
		while(optind < argc){
			s.push_back(argv[optind++]);
	}
						/*randPermString(s);
							 * 		for(size_t i = 0; i < s.size(); i++){
							 * 					cout << s[i] << "\n";
							 * 							}*/
	}
	else if(userange){
		int adder = rlow;
		int end = rhigh;
		while(adder <= end){	
			I.push_back(adder++); 	
		}
	}
	randPermString(s);
	randPermInt(I);
	int nC = count;
	if(nC > 0){
		if(userange){
			for(size_t i = 0; i < nC; i++)
				cout << I[i] << "\n";
		}
		else{
			for(size_t i = 0; i < nC; i++)
				cout << s[i] << "\n";
		}
	}
	else if(echo){
		for(size_t i = 0; i < s.size(); i++){
			cout << s[i] << "\n";
		}
	}
	else if(userange){
		for(size_t j = 0; j < I.size(); j++){
			cout << I[j] << "\n";
		}
	}


	return 0;
	//vector<string> words; //To store all of the user input

}


void randPerm(vector<string>& v){
	srand(time(0));	
	for(int i = v.size()-1; i > 0; --i){
		int random = rand();
		int randPos = random % (i+1); 
		string temp = v[randPos];
		v[randPos] = v[i];
		v[i] = temp;
	}
}


void randPermString(vector<string>& v){
		srand(time(0));	
			for(int i = v.size()-1; i > 0; --i){
						int random = rand();
								int randPos = random % (i+1); 
										string temp = v[randPos];
												v[randPos] = v[i];
														v[i] = temp;													
															}
}

void randPermInt(vector<int>& v){
		srand(time(0));	
			for(int i = v.size()-1; i > 0; --i){
						int random = rand();
								int randPos = random % (i+1); 
										int temp = v[randPos];
												v[randPos] = v[i];
														v[i] = temp;													
															}
}




