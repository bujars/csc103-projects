/*
 * CSc103 Project 3: unix utilities
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

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <algorithm>
using std::sort;
#include <string.h> // for c-string functions.
#include <getopt.h> // to parse long arguments.
#include <map>
using std::map;





static const char* usage =
"Usage: %s [OPTIONS] SET1 [SET2]\n"
"Limited clone of tr.  Supported options:\n\n"
"   -c,--complement     Use the complement of SET1.\n"
"   -d,--delete         Delete characters in SET1 rather than translate.\n"
"   --help          show this message and exit.\n";

void escape(string& s) {
	/* NOTE: the normal tr command seems to handle invalid escape
	 * sequences by simply removing the backslash (silently) and
	 * continuing with the translation as if it never appeared. */
	/* TODO: write me... */

	for(int  i = 0;i < (int) s.size() - 1;i++) {
				if(s[i] == '\\' && i !=  s.size() - 1) {
								if(s[i + 1] == '\\') {
													s[i] = '\\';
																	s.erase(i + 1);
																				}else if(s[i + 1] == 'n') {
																									s[i] = '\n';
																													s.erase(i + 1);
																																}else if(s[i + 1] == 't') {
																																					s[i] = '\t';
																																									s.erase(i + 1);
																																												}
										}
					}
}


void createAsciiMap(map<char,char> &map, int comp, string s1, string s2);
string formatSetStr(string s);
void replaceValues(map<char,char> map,string &line);
void createDelMap(map<char,char> &map,int comp, string s);
void deleteValues(map<char,char> map, string &line);








int main(int argc, char *argv[])
{
	// define long options
	static int comp=0, del=0;
	static struct option long_opts[] = {
		{"complement",      no_argument,   0, 'c'},
		{"delete",          no_argument,   0, 'd'},
		{"help",            no_argument,   0, 'h'},
		{0,0,0,0}
	};
	// process options:
	char c;
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "cdh", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'c':
				comp = 1;
				break;
			case 'd':
				del = 1;
				break;
			case 'h':
				printf(usage,argv[0]);
				return 0;
			case '?':
				printf(usage,argv[0]);
				return 1;
		}
	}
	if (del) {
		if (optind != argc-1) {
			fprintf(stderr, "wrong number of arguments.\n");
			return 1;
		}
	} else if (optind != argc-2) {
		fprintf(stderr,
				"Exactly two strings must be given when translating.\n");
		return 1;
	}
	string s1 = argv[optind++];
	string s2 = (optind < argc)?argv[optind]:"";
	/* process any escape characters: */
	escape(s1);
	//escape(s2);

	if(!del) {
			escape(s2);
				}
	/* TODO: finish this... */
	string line = ""; 

		while(fread(&c,1,1,stdin)) {
					line += c;
						}

			s1 = formatSetStr(s1);
				s2 = formatSetStr(s2);
					map<char,char> asciiMap;

						if(del) {
									createDelMap(asciiMap,comp,s1);
											deleteValues(asciiMap,line);
												}else {
															createAsciiMap(asciiMap,comp,s1,s2);
																	replaceValues(asciiMap,line);
																		}


							cout << line;





	/* TODO: finish this... */

	return 0;
}

void replaceValues(map<char,char> map,string &line) {
		for(size_t i = 0;i < line.size();i++) {
					line[i] = map[line[i]];	
						}
}



void deleteValues(map<char,char> map, string &line) {
		for(int i = 0;i <(int) line.size();i++) {
					if(map.find(line[i]) == map.end()) {
									line.erase(i);
												i--;
														}
						}
}


string formatSetStr(string s) {
		string result = "";
			for (size_t i = 0; i < s.size(); i++) {
						if(s[i] == '-' && i != 0 && i != s.size() - 1){
										for(int j = s[i-1] + 1;j < s[i + 1];j++) {
															result += (char) j;
																		}
												}else {
																result+=s[i];
																		}
							}
				return result;
}



void createAsciiMap(map<char,char> &map, int comp, string s1, string s2) {
if(comp){
			size_t s2It = 0;

					for(size_t i = 0;i < s1.size();i++) {
									map[s1[i]] = s1[i];
											}

							for(int i = 0;i < 256;i++) {
											if(map.find((char) i) == map.end()) {
																map[(char) i]=s2[s2It];
																				s2It = s2It ==  s2.size() - 1  ? s2It : s2It + 1;
																							}
													}

}else{
	size_t  s2It = 0;
			for(size_t i = 0;i < s1.size();i++) {
							map[s1[i]]=s2[s2It];
										s2It = s2It ==  s2.size() - 1  ? s2It + 1 : s2It;
												}	
					for(int i = 0;i < 256;i++) {
									if(map.find((char) i) == map.end()) {
														map[(char) i] = i;
																	}
											}
						}
}



void createDelMap(map<char,char> &map,int comp, string s) {
		if(comp) {
					for(size_t  i = 0; i < s.size();i++) {
									map[s[i]] = s[i];
											}
						}else {
									for(int i = 0;i < 256;i++) {
													map[(char) i] = i;
															}
											for(size_t i = 0;i < s.size();i++) {
															map.erase(s[i]);
																	}
												}

			
}



