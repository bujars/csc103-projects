/*
 * CSc103 Project 2: prime numbers.
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 *
 */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <cmath> //Incase you figure out the efficency improvement. -- To check how many checks are required and making sure you stop long before n - 2.

// HINT: sqrt function might be useful.

int main()
{
 /* NOTE : From what I quickly gathered from the quick skim I did on of the readme file, we are trying to generate all the vlaues of prime, as a value of 1. If the number that is unputted isn't prime, then outout a 0.
To chcek if a number is prime, we should be able to see if any of the number is odd, that means that its not divisible by 2, unless its the number two itself, and making sure it is not divided by the odd vlues, such as (3, 5, 7, ...., n-2)
 -- from website -- Keep it simple - just do trial division by odd integers until you either find a divisor, or you run out of candidates.
 */


 /* Thus might help for when to stop the loop*/
 //unsigned long n;
	int n = 6755;

	//while(cin >> n){
 	//do stuff
 	if ( (n == 2) || (n == 3) || (n==5) || (n==7) || (n==11))
		cout << 1 << endl;
	else if(((n%2 == 0) && (n != 2)) || (n==1) || (n==0))	
 		cout << 0 << endl; //For non-prime values
	else if ((n%3 == 0) || (n%5 == 0) || (n%7 == 0) || (n%11 == 0))
 		cout << 0 << endl;
	else if(n > 2){
		int divide = 2;
		while(divide < n){
			if(n%divide==0){
				cout << 0 << endl;
			}
			divide++;
		}
		divide = 2;
	}
	else {
		cout << 1 << endl;
 	}
 //}
	return 0;
}
