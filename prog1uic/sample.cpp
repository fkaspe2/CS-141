/* ------------------------------------------------
   sample.cpp
 
   This is a sample program to illustrate the programming concepts needed to write
   the first program. Note that to run this code you would need to copy and paste
   it into main.cpp and run it from there.
   
*/

#include <iostream>   // For cin and cout
#include <cstdlib>    // For system("clear") used to clear the screen
#include <chrono>     // Used in pausing for some milliseconds using sleep_for(...)
#include <thread>     // Used in pausing for some milliseconds using sleep_for(...)
using namespace std;

//---------------------------------------------------------------------------
//  Main loop
int main() {
	char userInputCharacter;   // User input for some character
	int  userInputNumber;      // User input for some numerical value
	
	cout << endl
		 << "Go Flames! Choose from among the following options: \n"
		 << "   1. Display OK  \n"
		 << "   2. Display OK as an animation \n"
	     << "   3. Exit the program \n"
		 << "Your choice -> ";
	cin >> userInputCharacter;
	cout << endl;
	
	// Handle the "Exit" option
	if( userInputCharacter == '3') {
		exit( -1);
	}
	
	// Display OK
	else if( userInputCharacter == '1') {
		cout << "  **    *  * \n"
			 << " *  *   * *  \n"
			 << "*    *  **   \n"
			 << " *  *   * *  \n"
			 << "  **    *  * \n"
			 << endl;
	}
	
	// Display OK as an animation
	else if( userInputCharacter == '2') {
		cout << "How many sets of letters do you want to display? -> ";
		cin >> userInputNumber;
		
		for( int setsOfLetters = 0; setsOfLetters < userInputNumber; setsOfLetters++) {
			
			// Display some number of blank lines.  This starts as a large number the first time, then
			// gets smaller each subsequent time, moving the ENTIRE set of letters vertically.
			for( int numberOfBlankLines = userInputNumber; numberOfBlankLines > setsOfLetters; numberOfBlankLines--) {
				cout << endl;
			}
			
			// Display one set of letters, going through and printing one "slice" of each letter at a time.
			for( int i=0; i<5; i++) {
				if(      i==0) cout << "  **   ";
				else if( i==1) cout	<< " *  *  ";
				else if( i==2) cout	<< "*    * ";
				else if( i==3) cout	<< " *  *  ";
				else if( i==4) cout	<< "  **   ";

				if(      i==0) cout << "*  * ";
				else if( i==1) cout << "* *  ";
				else if( i==2) cout << "**   ";
				else if( i==3) cout << "* *  ";
				else if( i==4) cout << "*  * ";

				cout << endl;
			}//end for( int i...)

			// Clear the screen after the letters are displayed.
			this_thread::sleep_for(chrono::milliseconds( 185));	// Sleep for 185 milliseconds
			system( "clear");   // Clear the screen.  Comment out this line if you don't want them erased.
			
		}//end for( int setsOfLetters...
		
	}//end else if( userInputCharacter == '2' ...
	
    return 0;
}//end main()