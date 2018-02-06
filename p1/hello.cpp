/*
 * CSc103 Project 1: (hello_world++)
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 *
 */


/* NOTE resources used: 
 * Project webpage to get all the code above main.
 * */

#include <iostream> //Adds iostream library
using std::cin; //Helps us reduce use of std::cin
using std::cout; //Helps us reduce use of std::cout
#include <string> //Adds string library
using std::string; //not sure what this actually does  2/5/18 //Update: I believe its to allow is to use the string variable, still unsure.
int main(){ //Where the code goes inside
	string yourName; //String varible where name will be stored.
	string relative; //String variable where relative will be stored.
	cout << "Welcome to my first project. Please enter your name: ";
	//cin >> name; //note this is what I originally planned to use.
	getline(cin, yourName); 
	/* NOTE what ^this code does is it says 
	 * take the inputted line from the compiler 
	 * using the function cin, 
	 * and then store that into name */
	cout << "Enter the name of your relative: ";
	getline(cin, relative); //Gets relative's name and stores it.
	cout << "Hello. My name is " << yourName << ". You killed my " << relative << ". Prepare to die.\n";


	return 0; //Tells us the code works
}

