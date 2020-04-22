/* ------------------------------------------------
   Prog 1: Print UIC
   
   Class: CS 141, Fall 2019.  Tues 10am lab
   System: Codio
   Author: Frank Kasper
    
   This program allows the user to print the UIC logo in 3 distinct ways. The program
   prompts the user to select option 1, 2, or 3.
   Option 1 prints the logo horizontally with a simple border.
   Option 2 prints the logo vertically with a similar border as 1.
   Option 3 will do perform a basic animation of the logo, with the three indivdual
   letters shifting up and down at different levels.
   If the user chooses to not print anything, they can exit the program by entering option 4.
   
   ------------------------------------------------
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
    
    char clearScreen;          //User input to clear previous animation block before printing the next
    int numberOfBlankLines;    //User inputs amount of space between each letter
    int setsOfLetters;         //User inputs how many times the logo will appear
	
	cout << endl
		 << "Go Flames! Choose from among the following options: \n"
		 << "   1. Display U I C as horizontal block letters\n"
		 << "   2. Display U I C as vertical block letters \n"
	     << "   3. Display U I C as an animation \n"
         << "   4. Exit the program \n"
		 << "Your choice -> ";
	cin >> userInputCharacter;
	cout << endl;
	
	
	
	// Displays UIC horizontally
	if( userInputCharacter == '1') {
		cout << "\n------------------------\n\n"
			 << "*     *  ****     * *       \n"
			 << "*     *   **    *           \n"
			 << "*     *   **   *            \n"
			 << "*     *   **   *            \n"
             << "*     *   **    *           \n"
             << "  * *    ****     * *     \n\n"
             << "------------------------    \n"
			 << endl;
	}
	
	// Display UIC vertically
	else if( userInputCharacter == '2') {
        cout << "\n-------\n\n"
             << "*     *\n"
             << "*     *\n"
             << "*     *\n"
             << "*     *\n"
             << "*     *\n"
             << "  * *  \n"
             << "       \n"
             << " ****  \n"
             << "  **   \n"
             << "  **   \n"
             << "  **   \n"
             << "  **   \n"
             << " ****  \n"
             << "       \n"
             << "   * * \n"
             << " *     \n"
             << "*      \n"
             << "*      \n"
             << " *     \n"
             << "   * * \n"
             << "-------\n"
             << endl;
    }
        
    //Display UIC as an animation:
    //prompt user if the screen should clear between frames, 
    //the number of frames, and the space between each letter
    else if( userInputCharacter == '3') {
        cout << "Clear the screen between displays? (Y/N) -> ";
        cin >> clearScreen;
        
        cout << "How many sets of letters? -> ";
        cin >> userInputNumber;
            
        cout << "How many blanks between letters (0..30)? -> ";
        cin >> numberOfBlankLines;
    
        int temp = numberOfBlankLines;      //stores the number of blank lines for later use and manipulation
            
            
        //displays user specified amount of frames
        for(setsOfLetters = 0; setsOfLetters < userInputNumber; setsOfLetters++) {
			//***Aditi: Use meaningful variables names
            for( int i=0; i<10; i++) {
                //***Aditi: Avoid repetition of major code blocks
                //phase 1
                if(setsOfLetters % 4 == 0) {
                
                    if (i==0) {
                        for (int j = 17 + (numberOfBlankLines * 2); j > 0; j--) {
                            cout << "-";
                        }
                    }
                    //***Aditi: Comments are missing for major code blocks
                    if(      i==1) cout << "       ";
                    else if( i==2) cout << "       ";
                    else if( i==3) cout << "*     *";
                    else if( i==4) cout	<< "*     *";
                    else if( i==5) cout	<< "*     *";
                    else if( i==6) cout	<< "*     *";
                    else if( i==7) cout	<< "*     *";
                    else if( i==8) cout	<< "  * *  ";
                    for(numberOfBlankLines = temp; numberOfBlankLines > 0; numberOfBlankLines--) {
                        cout << " ";
                    }
                    numberOfBlankLines = temp;
               
                    if(      i==1) cout << "    ";
                    else if( i==2) cout << "****";
                    else if( i==3) cout << " ** ";
                    else if( i==4) cout << " ** ";
                    else if( i==5) cout << " ** ";
                    else if( i==6) cout << " ** ";
                    else if( i==7) cout << "****";
                    else if( i==8) cout << "    ";
                    for(numberOfBlankLines = temp; numberOfBlankLines > 0; numberOfBlankLines--) {
                        cout << " ";
                    }
                    numberOfBlankLines = temp;
                
                    if(      i==1) cout << "   * *";
                    else if( i==2) cout << " *    ";
                    else if( i==3) cout << "*     ";
                    else if( i==4) cout << "*     ";
                    else if( i==5) cout << " *    ";
                    else if( i==6) cout << "   * *";
                    else if( i==7) cout << "      ";
                    else if( i==8) cout << "      ";
                    
                    if (i==9) {
                        cout << endl;
                        for (int j = 17 + (numberOfBlankLines * 2); j > 0; j--) {
                            cout << "-";
                        }
                    }
                    cout << endl;
                }
                
                 
                //phase 2
                else if (setsOfLetters % 4 == 1 || setsOfLetters % 4 == 3){
            
                    if (i==0) {
                        for (int j = 17 + (numberOfBlankLines * 2); j > 0; j--) {
                            cout << "-";
                        }
                    }
                   
                    if(      i==1) cout << "       ";
                    else if( i==2) cout	<< "*     *";
                    else if( i==3) cout	<< "*     *";
                    else if( i==4) cout	<< "*     *";
                    else if( i==5) cout	<< "*     *";
                    else if( i==6) cout	<< "*     *";
                    else if( i==7) cout	<< "  * *  ";
                    else if( i==8) cout	<< "       ";
                    for(numberOfBlankLines = temp; numberOfBlankLines > 0; numberOfBlankLines--) {
                        cout << " ";
                    }
                    numberOfBlankLines = temp;

                    if(      i==1) cout << "****";
                    else if( i==2) cout << " ** ";
                    else if( i==3) cout << " ** ";
                    else if( i==4) cout << " ** ";
                    else if( i==5) cout << " ** ";
                    else if( i==6) cout << "****";
                    else if( i==7) cout	<< "    ";
                    else if( i==8) cout	<< "    ";
                    for(numberOfBlankLines = temp; numberOfBlankLines > 0; numberOfBlankLines--) {
                        cout << " ";
                    }
                    numberOfBlankLines = temp;
                    if(      i==1) cout	<< "      ";
                    else if( i==2) cout << "   * *";
                    else if( i==3) cout << " *    ";
                    else if( i==4) cout << "*     ";
                    else if( i==5) cout << "*     ";
                    else if( i==6) cout << " *    ";
                    else if( i==7) cout << "   * *";
                    else if( i==8) cout	<< "      ";
                    if (i==9) {
                        cout << endl;
                        for (int j = 17 + (numberOfBlankLines * 2); j > 0; j--) {
                            cout << "-";
                        }
                    }
                    cout << endl;
                 }
            
                 
                //phase 3
                else if (setsOfLetters % 4 == 2){
        
                if (i==0) {
                    for (int j = 17 + (numberOfBlankLines * 2); j > 0; j--) {
                        cout << "-";
                    }
                }
                    
                if(      i==1) cout << "*     *";
                else if( i==2) cout	<< "*     *";
                else if( i==3) cout	<< "*     *";
                else if( i==4) cout	<< "*     *";
                else if( i==5) cout	<< "*     *";
                else if( i==6) cout	<< "  * *  ";
                else if( i==7) cout	<< "       ";
                else if( i==8) cout	<< "       ";
                for(numberOfBlankLines = temp; numberOfBlankLines > 0; numberOfBlankLines--) {
                    cout << " ";
                }
                numberOfBlankLines = temp;

                if(      i==1) cout << "    ";
                else if( i==2) cout << "****";
                else if( i==3) cout << " ** ";
                else if( i==4) cout << " ** ";
                else if( i==5) cout << " ** ";
                else if( i==6) cout << " ** ";
                else if( i==7) cout << "****";
                else if( i==8) cout	<< "    ";
                for(numberOfBlankLines = temp; numberOfBlankLines > 0; numberOfBlankLines--) {
                    cout << " ";
                }
                numberOfBlankLines = temp;
                
                if(      i==1) cout << "      ";
                else if( i==2) cout << "      ";
                else if( i==3) cout << "   * *";
                else if( i==4) cout << " *    ";
                else if( i==5) cout << "*     ";
                else if( i==6) cout << "*     ";
                else if( i==7) cout << " *    ";
                else if( i==8) cout << "   * *";
                
                if (i==9) {
                    cout << endl;
                    for (int j = 17 + (numberOfBlankLines * 2); j > 0; j--) {
                        cout << "-";
                    }
                }
                cout << endl;
                }     
            }
        }           
	}
    
    
	// Clear the screen after the letters are displayed.
    this_thread::sleep_for(chrono::milliseconds( 185));	// Sleep for 185 milliseconds
    //if "Y" or "y" function clears each previous frame before showing the next, resulting in the animation
    if (clearScreen == 'y' || clearScreen == 'Y') {
    system( "clear");  
    }
            

    //allows user to quit program
    else if( userInputCharacter == '4') {
        exit( -1);
    }
        
    //good night, sweet prince
    return 0;
}//end main()





