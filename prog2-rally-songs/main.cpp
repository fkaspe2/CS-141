/* --------------------------------------------------------
 * prog2RallySongs.cpp
 *    Read political candidate's favorite song lyrics from a file.
 *    Choose random lines and see if the reader can identify the candidate.
 * 
 * 
 * Class: Program #2 for CS 141, Fall 2019
 * Lab: Tues 10pm,
 * Author: Frank Kasper
 * 
 * 
 * 
 */


#include <iostream>
#include <cctype>       // For the letter checking functions
#include <fstream>      // For file input
#include <iomanip>      // For setw
#include <cstdlib>      // For exit and abs
using namespace std;


//-------------------------------------------------------------------------------------------------


//Uses the file name to determine what lines will be printed
void RandomLines(string candidateName)
{  
    // Declare the input file stream
    ifstream inputFileStream;                             
    // Makes sure file can be accessed
    inputFileStream.open( candidateName.c_str() );
    if( !inputFileStream.is_open()) {
        cout << "Could not find input file " << candidateName << "  Exiting..." << endl;
        exit( -1);
    }
    
    // Read the number on the first line of the input file, which indicates how many subsequent
    // lines there are in the file.
    int numberOfLinesInFile = 0;
    inputFileStream >> numberOfLinesInFile;
    
    
    int counter = 1;                              // Counts line number until the desired line is found
    int lineNumber = rand()%numberOfLinesInFile;  // Chooses a random line number in the file
    string line;                                  // Holds the line at the desired number
    
 
    //Loop scans through the file until the desired line is reached
    while( getline( inputFileStream, line) ) {
        //Once the counter matches the line number, print the line
        //Skips line the begin with "#" or are blank and prints the next one
        if(counter == lineNumber){
            if ((line[0] != '#') && (line != "")){
                cout << line << endl;
            }
            else{
                lineNumber++;
            }
        }
        //Tracks the line number throughout the file
        counter++; 
    }
    //Closes the file
    inputFileStream.close();   
}




int main() {
	int userChoice;                    //User's choice at the menu screen
    double numTimesPlayed=0;           //The amount of time the user plays the quiz
    double numTimesCorrect=0;          //The number of times the user gets the quiz correct
    double percentCorrect = 0;         //Shows the percent accuracy of the user (no decimals, rounded up)
    int numberOfLinesToDisplay = 3;    // How many lines to display from lyrics file
    int sendForRandomFile;             //Determines whether the file for the quiz will be Trump or Warren
    int chooseTrumpOrWarren = -1;      //User input guessing Trump or Warren (1 for Trump, 2 for Warren)
    int counter;                       //Tracks loop iterations
    
    
    //Stores the filenames needed
    string filename1 = "Trump.txt";
    string filename2 = "Warren.txt";
    // Initialize the random number generator
    srand( 1);    // Change this to srand( time(0))  if you want it to be different every time.
    
	//cout << "A random value is: " << rand() << endl;
	//tests the random number generator
	
    
    //loops through the menus
    while (userChoice != 5) {
    /***** Incorrect level of indentation - Clark *****/
	// Display which program this is and display menu options to select program output to be displayed
	cout << endl
		 << "---- Program 2: Rally Songs ----           \n"
		 << "Select from the following:                 \n"
		 << "   1. Set number of lines to display       \n"
		 << "   2. Get random lines from Trump.txt      \n"
		 << "   3. Get random lines from Warren.txt     \n"
		 << "   4. Rally song quiz                      \n"
		 << "   5. Exit the program                     \n"
		 << "Your choice --> ";
    
    //user chooses which option they would like
    cin >> userChoice;
    cout << endl;
    
    
    //Allows the user to change the number of lines that are displayed if they enter 1
    if (userChoice == 1) {
        cout << "Enter the number of lines you want to display -> ";
        cin >> numberOfLinesToDisplay;
        cout << endl;
    }
    
    //Prints lyrics from Trump's file if they enter 2
    else if (userChoice == 2) {
        /***** Redundant code(hard code): Similar code should be group into a function - Clark *****/
        for (counter = 0; counter < numberOfLinesToDisplay; counter++) {
            RandomLines(filename1);
        }
    }
    
    //Prints lyrics from Warren's file if they enter 3
    else if (userChoice == 3) {
        /***** Redundant code(hard code): Similar code should be group into a function - Clark *****/
        for (counter = 0; counter < numberOfLinesToDisplay; counter++) {
            RandomLines(filename2);
        }
    }
    
    else if (userChoice == 4) {
        numTimesPlayed++;                          //Keeps track of how many times the user selects the quiz option
        sendForRandomFile = rand() % 2 + 1;        //Randomizes whether the lines are from the Trump or Warren file
        
        //If the random number is 1, call function with Trump file
        if (sendForRandomFile == 1) {
            /***** Redundant code(hard code): Similar code should be group into a function - Clark *****/
            for (counter = 0; counter < numberOfLinesToDisplay; counter++) {
                RandomLines(filename1);
            }
        }
        //If the random number is 1, call function with Warren file
        else {
            /***** Redundant code(hard code): Similar code should be group into a function - Clark *****/
            for (counter = 0; counter < numberOfLinesToDisplay; counter++) {
                RandomLines(filename2);
            }
        }
        
        //User enters their answer
        cout << endl << "Enter 1 for Trump, 2 for Warren: ";
        cin >> chooseTrumpOrWarren;
        cout << endl << endl;
        
        //If the user guesses correctly print this
        //Calculates the current score
        if ( chooseTrumpOrWarren == sendForRandomFile) {
            /***** Redundant code(hard code): Similar code should be group into a function - Clark *****/
            numTimesCorrect++;
            percentCorrect = (numTimesCorrect / numTimesPlayed) * 100.0;
            cout << "Correct! You got " << numTimesCorrect << " out of " << numTimesPlayed << ", which is " 
                 << fixed << setprecision( 0) << percentCorrect << "%" << endl;
            
        }
        //If the user guesses incorrectly print this
        //Calculates the current score
        else {
            /***** Redundant code(hard code): Similar code should be group into a function - Clark *****/
            percentCorrect = (numTimesCorrect / numTimesPlayed) * 100.0;
            cout << "Wrong! You got " << numTimesCorrect << " out of " << numTimesPlayed << ", which is " 
                 << fixed << setprecision( 0) << percentCorrect << "%" << endl;
        }
    } //end of quiz option
    
    //If user enters 5 or an invalid guess print this and end program
    else{
        /***** Redundant code(hard code): Similar code should be group into a function - Clark *****/
        cout << endl << "You got " << numTimesCorrect << " out of " << numTimesPlayed << ", which is " 
                     << fixed << setprecision( 0) << percentCorrect << "%" << endl;
        break;
    }
        
    }//end of while loop for menuing
    
    //Good night, sweet prince
    return 0;
    
}//end main()
