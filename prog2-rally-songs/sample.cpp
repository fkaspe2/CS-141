/* --------------------------------------------------------
 * prog2RallySongs.cpp
 *    Read political candidate's favorite song lyrics from a file.
 *    Choose random lines and see if the reader can identify the candidate.
 *
 *    This was inspired by the New York Times article:
 *       https://www.nytimes.com/interactive/2019/08/19/us/politics/presidential-campaign-songs-playlists.html
 *    which describes the different songs played at political rallies for
 *    different 2020 presidential candidates.
 *
 * Class: Program #2 for CS 141, Fall 2019
 * Lab: Mon 5am,
 * TA Alan Turing
 * System: Mac OS X
 * Author: ?
 */

#include <iostream>
#include <cctype>       // For the letter checking functions
#include <fstream>      // For file input
#include <iomanip>      // For setw
#include <cstdlib>      // For exit and abs
using namespace std;


//-------------------------------------------------------------------------------------------------
int main() {
	
	// Here is some sample code to open a file, read the number on the first line, and print it.
	ifstream inputFileStream;  // Declare the input file stream
    
    // Open input file and verify that file was found
    string candidateName = "Trump.txt";
    inputFileStream.open( candidateName.c_str() );
    if( !inputFileStream.is_open()) {
        cout << "Could not find input file " << candidateName << "  Exiting..." << endl;
        exit( -1);
    }

    // Read the number on the first line of the input file, which indicates how many subsequent
    // lines there are in the file.
    int numberOfLinesInFile = 0;
    inputFileStream >> numberOfLinesInFile;    
    inputFileStream.close();
	
    
    // Initialize the random number generator
    srand( 1);    // You must leave it as srand( 1) for the version you turn in.
	              // Change this to srand( time(0))  if you want it to be different every time.
	cout << "A random value is: " << rand() << endl;

	// Display which program this is and display menu options to select program output to be displayed
	cout << endl
		 << "---- Program 2: Political Lyrics ----      \n"
		 << "Select from the following:                 \n"
		 << "   1. Set number of lines to display       \n"
		 << "   2. Get random lines from Trump.txt      \n"
		 << "   3. Get random lines from Warren.txt     \n"
		 << "   4. Rally song quiz                      \n"
		 << "   5. Exit the program                     \n"
		 << "Your choice --> ";

    
    return 0;
}//end main()
