//------------------------------------
//  vexed.cpp
//     Move pieces to be adjacent.  Once adjacent pieces match, they are cleared off the board.  Once the entire
//     board is clear, play advances to the next level.
//     
//  Prog 4: Vexed
//  Author: Dale Reed
//  Using Codio, for UIC CS 141, Fall 2019
//
//  Running the program looks like:
/*
		Welcome to Vexed!
		The objective is to place identical pieces next to each other, so that they vanish,
		clearing the board completely within the indicated number of moves. On each move
		enter the row, column, and direction (L or R) to move, in either upper or lower
		case. You may also enter 'x' to exit the program, or 'r' to reset the current level.


			Board 0 par 4
			  0 1 2 3 4 5 6 7 8 9
			-----------------------
		  A | . . . . . . . . . . | A
		  B | . . . . . . . . . . | B
		  C | . . . @ &     . . . | C
		  D | . . . . .     . . . | D
		  E | . . .         . . . | E
		  F | . . . &     @ . . . | F
		  G | . . . . & @ . . . . | G
		  H | . . . . . . . . . . | H
			-----------------------
			  0 1 2 3 4 5 6 7 8 9
		1. Your move: c4r

			Board 0 par 4
			  0 1 2 3 4 5 6 7 8 9
			-----------------------
		  A | . . . . . . . . . . | A
		  B | . . . . . . . . . . | B
		  C | . . . @   &   . . . | C
		  D | . . . . .     . . . | D
		  E | . . .         . . . | E
		  F | . . . &     @ . . . | F
		  G | . . . . & @ . . . . | G
		  H | . . . . . . . . . . | H
			-----------------------
			  0 1 2 3 4 5 6 7 8 9

			Board 0 par 4
			  0 1 2 3 4 5 6 7 8 9
			-----------------------
		  A | . . . . . . . . . . | A
		  B | . . . . . . . . . . | B
		  C | . . . @       . . . | C
		  D | . . . . . &   . . . | D
		  E | . . .         . . . | E
		  F | . . . &     @ . . . | F
		  G | . . . . & @ . . . . | G
		  H | . . . . . . . . . . | H
			-----------------------
			  0 1 2 3 4 5 6 7 8 9

			Board 0 par 4
			  0 1 2 3 4 5 6 7 8 9
			-----------------------
		  A | . . . . . . . . . . | A
		  B | . . . . . . . . . . | B
		  C | . . . @       . . . | C
		  D | . . . . .     . . . | D
		  E | . . .     &   . . . | E
		  F | . . . &     @ . . . | F
		  G | . . . . & @ . . . . | G
		  H | . . . . . . . . . . | H
			-----------------------
			  0 1 2 3 4 5 6 7 8 9

			Board 0 par 4
			  0 1 2 3 4 5 6 7 8 9
			-----------------------
		  A | . . . . . . . . . . | A
		  B | . . . . . . . . . . | B
		  C | . . . @       . . . | C
		  D | . . . . .     . . . | D
		  E | . . .         . . . | E
		  F | . . . &   & @ . . . | F
		  G | . . . . & @ . . . . | G
		  H | . . . . . . . . . . | H
			-----------------------
			  0 1 2 3 4 5 6 7 8 9
		2. Your move:

 */
#include <iostream>   // For cin, cout
#include <fstream>    // For file input
#include <chrono>     // Used in pausing for some milliseconds using sleep_for(...)
#include <thread>     // Used in pausing for some milliseconds using sleep_for(...)
#include <iomanip>
#include <cstring>
using namespace std;

// Global constants
const int MaxNumberOfBoards = 118;
const int BoardRows = 8;
const int BoardColumns = 10;
const int NumberOfPresetBoardParValues = 60;    // After the first 60 par values, the default par value is 15
const char FileName[] = "boards.txt";
const int SleepAmount = 150;                    // Length of time to pause, in milliseconds

// OUR GLOBALS
int score = 0;
int boardIndex = 0;

//------------------------------------------------------------------------------------------------------------------
// Class used to store a game board
class Board
{
    public:
        // Constructor declarations  
        Board();
        Board(int boardIndex, int thisAllBoards[], int thisLevelParValues);
        void displayBoard();
        int boardDirections(int &boardIndex); 
        //void moveBoardPiece(int board[80], char userMove[3]) ;
        void mark(int position, int valueToMatch, int theBoard[80], bool &matchExists);
        void scanAndDelete(int position, int theBoard[80]);
        void scanAndFall(int position, int theBoard[80]);
        int checkIfEmpty(int position, int board[], int moveNumber);
        void resetBoard();
        void blankMatching(int board[]);
        bool compareBoards (int boards[], int temp[]);
        //int checkIfEmpty(int position, int board[80]);
        // Utility member function declarations.  

    private:
    int level;
    int board[80];
    int par;

};  // end class Board

// default constructor
Board::Board()
{
  level = -1;
  par = -1;
  for(int i = 0; i < BoardRows * BoardColumns; i++)
  {
    board[i] = -1;
  }
}

// Fully qualified constructor
Board::Board(int boardIndex, int thisAllBoards[], int thisLevelParValues)
{
  level = boardIndex;
  for (int i = 0; i < BoardRows * BoardColumns; i++) {
    board[i] = thisAllBoards[i];
  }
  par = thisLevelParValues;
}

// display board whenever called (also after changes)
void Board::displayBoard()
{
  int i = 0;
  char letter = 'A';
  cout << "    Board " << level << " par " << par << endl;

  cout << "      0 1 2 3 4 5 6 7 8 9  " << endl;
  cout << "    ----------------------- " << endl;
  while(i < ((BoardRows * BoardColumns)))
  {
    if(i % 10 == 0 )
    {
      if (i % 10 == 0 && i != 0)
      {
        cout << " | " << letter ;
        letter++;
        cout << endl;
      }
      cout << "  " << letter << " |" ;
    }
    //if (board[i] == -1)      { cout << setw(2) << ' '; }  //not sure if okay
    if (board[i] == 0)      { cout << setw(2) << ' '; }
    else if (board[i] == 1) { cout << setw(2) << '&'; }
    else if (board[i] == 2) { cout << setw(2) << '@'; }
    else if (board[i] == 3) { cout << setw(2) << '+'; }
    else if (board[i] == 4) { cout << setw(2) << '%'; }
    else if (board[i] == 5) { cout << setw(2) << '^'; }
    else if (board[i] == 6) { cout << setw(2) << '#'; }
    else if (board[i] == 7) { cout << setw(2) << '='; }
    else if (board[i] == 8) { cout << setw(2) << '*'; }
    else if (board[i] == 9) { cout << setw(2) << '.'; }
    i++; 
  }
  cout << " | " << letter << endl << "    ----------------------- " << endl ;
  cout                            << "      0 1 2 3 4 5 6 7 8 9     " << endl << endl;
}



int Board::boardDirections(int &boardIndex) //int boardIndex, int thisAllBoards[boardIndex], int levelParValues[boardIndex]
{
  char userMove[3];
  int tempBoard[80];
  int moveNumber = 0;
  int emptyCheck = 0;
  
  while(true) {  // CHECK SOLUTION IF GAME STOPS AFTER PAR
    emptyCheck = checkIfEmpty(79, board, moveNumber);
    //returns -1 if level succesfuly completed
    if (emptyCheck == 1)
    {
      return -1;
    }
    //returns -2 if par value has been exceeded
    if (emptyCheck == 2)
    {
      return -2;
    }
    
    for (int i = 0; i < BoardRows * BoardColumns; i++) {
      tempBoard[i] = board[i];
    }

    cout << moveNumber+1 << ". Your move: ";
    cin >> userMove;
    /* CODE BLOCK BELOW CONTAINS ALL THE CHECKS THAT ARE INVALID MOVES */
    // exit program
    if(userMove[0] == 'x' || userMove[0] == 'X') {
      //cout << "Exiting program..." << endl;
      exit(1);
    }
    // reset level, move = 1
    if (userMove[0] == 'r' || userMove[0] == 'R')  
    {
      return -2;
      // for (int i = 0; i < BoardRows * BoardColumns; i++) {
      //   board[i] = tempBoard[i];
      // }
      // moveNumber = 0;
      // resetBoard();
      // continue;
    }


    if(userMove[0] == 's' || userMove[0] == 'S')
    {
      moveNumber = 0;
      if((userMove[1]- 48) > -1 && (userMove[1]- 48) < 118)
      {
        //this one stays
        boardIndex = userMove[1] - 48;
        return boardIndex;
      }
      cin >> boardIndex;
      
      return boardIndex;
    }


    // user enters letter/number outside of grid
    // FIX TO ACCOUNT FOR OTHER CASES
    if ( !(userMove[0] >= 'a' && userMove[0] <= 'h') 
      && !(userMove[0] >= 'A' && userMove[0] <= 'H') ) { //any charaecter between 1 and 8 are valid
      cout << endl << "Move value is out of bounds.  Please retry." << endl;
      continue;
    }
    // direction is not left or right
    if ( userMove[2] != 'l' && userMove[2] != 'r' && userMove[2] != 'L' && userMove[2] != 'R' ) {
      cout << endl << "Invalid move direction.  Please retry." << endl;
      continue;
    }

    int rowNumber;
    int colNumber;
    int position;

    
    // FOR LOWERCASE INPUT
    if (userMove[0] >= 97 && userMove[0] <= 104 ) {
      rowNumber = (userMove[0] - 97) * 10;   
    }
    // FOR UPPERCASE INPUT
    else {
      rowNumber = (userMove[0] - 65) * 10;
    }
    colNumber = userMove[1] - 48;
    position = rowNumber + colNumber; //NOT NEEDED
      
    if (board[position] == 0 || board[position] == 9 ) {
        cout << endl << "Attempting to move an invalid character.  Please retry. " << endl;
        continue;
    }
    

    int temp;
    if (userMove[2] == 'r' || userMove[2] == 'R')
    {
      
      if (board[rowNumber + colNumber] >=1 && board[rowNumber + colNumber] <= 8 && board[rowNumber + colNumber + 1] == 0 ) //won't move spacess or dots
      {                                                                                                                    //and only swaps with spaces
        temp = board[rowNumber + colNumber];
        board[rowNumber + colNumber] = board[rowNumber + colNumber + 1];
        board[rowNumber + colNumber + 1] = temp;
        colNumber++;
        moveNumber++;
        displayBoard();
      }
      else {
        cout << endl << "Attempting to move into a non-empty space.  Please retry." << endl;
        continue;
      }
    }
  
    else if(userMove[2] == 'l' || userMove[2] == 'L')
    {
      if (board[rowNumber + colNumber] >=1 && board[rowNumber + colNumber] <= 8 && board[rowNumber + colNumber - 1] == 0) 
      {
        temp = board[rowNumber + colNumber];
        board[rowNumber + colNumber] = board[rowNumber + colNumber - 1];
        board[rowNumber + colNumber - 1] = temp;
        colNumber--;
        moveNumber++;
        displayBoard();
        
      }

      else {
        cout << endl << "Attempting to move into a non-empty space.  Please retry." << endl;
        continue;
      }
    }
    


/*
    do {
        boardCopy = theBoard;     // Make a copy of the current board using the copy constructor
        
        theBoard.slideAllPiecesDown();             // Slide all possible pieces down
        theBoard.findAndDeleteMatchingPieces();    // Delete any adjacent matching pieces
    } while( theBoard.isNotTheSameAs( boardCopy) );
*/
    

      position = rowNumber + colNumber;
      int tempBoard[80];
      for (int k = 0; k < 80; k++) {
        tempBoard[k] = board[k];
      }

      scanAndFall (position, board);
      scanAndDelete(position, board);
       while (compareBoards(board, tempBoard) == true) {
        for (int k = 0; k < 80; k++) {
          tempBoard[k] = board[k];
        }
        scanAndFall (position, board);
        scanAndDelete(position, board);
       }   
    
    
   }  
}

bool Board::compareBoards (int board[], int temp[]) 
{
  // Compare each board member
  
  for( int position = 0; position < 80; position++) {
      if( board[position] != temp[position]) {
          return true;
      }
  }
  return false;    // All pieces were the same
} //end for( int row...

  

// function that checks and marks index to -1 to later delete them. position is current position; valueToMatch is index that is checked and theBoard is [1-D] array of current board being displayed.

void Board::mark(int position, int valueToMatch, int theBoard[], bool &matchExists)
{
  //check left
  if(theBoard[position -1] == valueToMatch)
  {
      // set to -1
      theBoard[position] = -1;
      theBoard[position -1] = -1;
      matchExists = true;
      // recurse
      mark(position-1, valueToMatch, theBoard, matchExists);
  }
  // check above
  if(theBoard[position - 10] == valueToMatch)
  {
      // set to -1
      theBoard[position] = -1;
      theBoard[position - 10] = -1;
      matchExists = true;
      // recurse
      mark(position-10, valueToMatch, theBoard, matchExists);
  }
  // check below
  if(theBoard[position + 10] == valueToMatch)
  {
      // set to -1
      theBoard[position] = -1;
      theBoard[position + 10] = -1;
      matchExists = true;
      // recurse
      mark(position+10, valueToMatch, theBoard, matchExists);
  }
  // check right
  if(theBoard[position +1] == valueToMatch)
  {
      // set to -1
      theBoard[position] = -1;
      theBoard[position +1] = -1;
      matchExists = true;
      // recurse
      mark(position+1, valueToMatch, theBoard, matchExists);
  }
}

void Board::scanAndDelete(int position, int theBoard[])
{
  position = 1;
  while(position < 81)
  {
    bool matchExists = false;
    if (theBoard[position] != 0 && theBoard[position] != 9)
    {
      mark(position, theBoard[position], theBoard, matchExists);
    }
    
    blankMatching(theBoard);
    if (matchExists ) {
      displayBoard();
    }
    position++;
  } 
}

void Board::blankMatching(int board[])
{
  int position = 1;
  
  while(position < 81)
  {
    if(board[position] == -1)
    {
      board[position] = 0;
    }
    position++;
  }
}

void Board::scanAndFall(int position, int theBoard[])
{
  for (position = 80; position > 0; position--) {
    while (theBoard[position] != 9 && theBoard[position] != 0 && theBoard[position + 10] == 0) {
      theBoard[position +10] = theBoard[position ];
      theBoard[position] = 0;
      position += 10;
      
      this_thread::sleep_for(chrono::milliseconds( SleepAmount));
      displayBoard();
    }
  }
  //scanAndFall(position, theBoard);
}

int Board::checkIfEmpty(int position, int board[], int moveNumber) 
{

  position = 79;
  
  while (position != -1) 
  {
    if (board[position] != 0 && board[position] != 9)
    {
      return 0;
      boardDirections(boardIndex);
    }
    position--;
  }
  
  score += par;

  if(moveNumber <= par)
  {
    moveNumber = 1;
    cout << "Congratulations!  On to the next level." << endl;
    cout << "Score: " << score << endl;
    return 1;
  }
  else if(moveNumber > par)
  {
    cout << "Sorry, you took " << moveNumber << " moves and you must finish within " << par << " moves before moving on." << endl;
    moveNumber = 1;
    return 2;
  }
  
  
  return 0;
    
} 

// DELETE THIS MAYBE
// DO WE NEED ANYMORE?
void Board::resetBoard()
{
  int i = 0;
  char letter = 'A';
  cout << "    Board " << level << " par " << par << endl;

  cout << "      0 1 2 3 4 5 6 7 8 9  " << endl;
  cout << "    ----------------------- " << endl;
  while(i < ((BoardRows * BoardColumns)))
  {
    if(i % 10 == 0 )
    {
      if (i % 10 == 0 && i != 0)
      {
        cout << " | " << letter ;
        letter++;
        cout << endl;
      }
      cout << "  " << letter << " |" ;
    }
    //if (board[i] == -1)      { cout << setw(2) << ' '; }  //not sure if okay
    if (board[i] == 0)      { cout << setw(2) << ' '; }
    else if (board[i] == 1) { cout << setw(2) << '&'; }
    else if (board[i] == 2) { cout << setw(2) << '@'; }
    else if (board[i] == 3) { cout << setw(2) << '+'; }
    else if (board[i] == 4) { cout << setw(2) << '%'; }
    else if (board[i] == 5) { cout << setw(2) << '^'; }
    else if (board[i] == 6) { cout << setw(2) << '#'; }
    else if (board[i] == 7) { cout << setw(2) << '='; }
    else if (board[i] == 8) { cout << setw(2) << '*'; }
    else if (board[i] == 9) { cout << setw(2) << '.'; }
    i++; 
  }
  cout << " | " << letter << endl << "    ----------------------- " << endl ;
  cout                            << "      0 1 2 3 4 5 6 7 8 9     " << endl << endl;
}

//------------------------------------------------------------------------------------------------------------------
// Class used to read in and store all game boards
class AllBoards
{
    public:
        //------------------------------------------------------------------------------------------------------------------
        // Constructor that reads in data from the data file.
        AllBoards();    // Declaration.  See the definition outside the class, below.
        
        // Get and Set member functions.

        //------------------------------------------------------------------------------------------------------------------
        // Find and return a particular board.
        Board getBoard( int boardIndex)
        {
            // Validate board index number
            if( boardIndex < 0 || boardIndex > MaxNumberOfBoards) {
                cout << "In getBoard() inside AllBoards class, boardIndex "
                     << boardIndex << " is out of range. Exiting..." << endl;
                exit( -1);
            }
            
            // Construct a Board from one of all the boards
            Board newBoard( boardIndex, allBoards[ boardIndex], levelParValues[ boardIndex]);
            return newBoard;
        }
    
        /*  DO WE NEED THIS?  
        Board setBoard(int boardIndex)
        {
          // Validate board index number
            if( boardIndex < 0 || boardIndex > MaxNumberOfBoards) {
                cout << "In getBoard() inside AllBoards class, boardIndex "
                     << boardIndex << " is out of range. Exiting..." << endl;
                exit( -1);
            }
            Board newBoard( boardIndex, allBoards[ boardIndex], levelParValues[ boardIndex]);
            boardIndex = currentLevel;
            //allBoards
        } */

        //------------------------------------------------------------------------------------------------------------------
        // Retrieve the par value
        int getParValue( int boardIndex) {
            int theParValue = 15;   // default
            if( boardIndex < NumberOfPresetBoardParValues) {
                theParValue = levelParValues[ boardIndex];
            }
            return theParValue;
        } // end getParValue()
    
    private:
        int par = 0;             // The number of moves it should take to solve this level
        int currentLevel = -1;   // Which board we're on
        int allBoards[ 118][ BoardRows * BoardColumns];   // Array to store all 118 8x10 boards
    
        // Par values for levels 0 through 59.  Default is 15 after that.
        const int levelParValues[ NumberOfPresetBoardParValues] =
            // 0   1   2   3   4   5   6   7   8   9
            { 4,  3, 14,  5,  6,  4,  4, 14,  5, 25,  //  0 -  9
             12, 17, 17,  8,  4, 12,  9,  8, 12,  8,  // 10 - 19
             10, 10, 16, 13, 20, 14, 10,  9, 12, 14,  // 20 - 29
             15, 13, 20,  8, 15, 10, 10, 11,  7, 23,  // 30 - 39
              8, 11, 16, 14, 12, 13, 13,  3, 35, 18,  // 40 - 49
             26, 10, 13, 18, 26, 12, 15,  5, 22, 15}; // 50 - 59
}; //end class allBoards


//------------------------------------------------------------------------------------------------------------------
// AllBoards constructor
AllBoards::AllBoards()
 {
    // Read in all the boards from the data file
    ifstream inputFileStream;  // declare the input file stream

    // Open input file and verify file open worked.
    inputFileStream.open( FileName);
    if( !inputFileStream.is_open()) {
        cout << "Could not find input file. " << FileName << ".  Exiting..." << endl;
        exit( -1);
    }

    // Read the five lines of comments at the top of the datafile.  Datafile structure is:
    //    // Originally from Vexed v2.0 - globals.c "Global variable declarations"
    //    // Copyright (C) 1999 James McCombe (cybertube@earthling.net)
    //    // September 1,2001 - Version 2.0 changes by Mark Ingebretson (ingebret@yahoo.com) and others.
    //    // Oct 13, 2019  Format changed by Dale Reed (reed @ uic.edu)
    //    // Covered by the GNU General Public License https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html
    //    // Level 000
    //    9 9 9 9 9 9 9 9 9 9
    //    9 9 9 9 9 9 9 9 9 9
    //    9 9 9 2 1 0 0 9 9 9
    //    9 9 9 9 9 0 0 9 9 9
    //    9 9 9 0 0 0 0 9 9 9
    //    9 9 9 1 0 0 2 9 9 9
    //    9 9 9 9 1 2 9 9 9 9
    //    9 9 9 9 9 9 9 9 9 9
    //    // Level 001
    //    9 9 9 9 9 9 9 9 9 9
    //    9 9 9 9 9 9 9 9 9 9
    // ...
    
    // Read and discard the five lines of comments at the beginning of the file.
    string inputLine;
    for( int i=0; i<5; i++) {
        getline(inputFileStream, inputLine);
    }
    
    // Now read each of the 118 (MaxNumberOfBoards) boards.  Each one starts with a comment that has the board number.
    for( int boardIndex = 0; boardIndex < MaxNumberOfBoards; boardIndex++) {
        // Read the comment with the board number
        getline(inputFileStream, inputLine);
        
        // For each board now read the BoardRows * BoardColumns number of board values, as integers
        for( int row=0; row<BoardRows; row++) {
            for( int col=0; col<BoardColumns; col++) {
                inputFileStream >> allBoards[ boardIndex][ row * BoardColumns + col];
            }
            // Get rid of end-of-line character at the end of each board, so we can get a clean start on reading the
            //   first line of the next board, on the line with the comment and board number.
            getline(inputFileStream, inputLine);
        }
    }//end for( int boardIndex=0...

    // Close the input file.
    inputFileStream.close();
}//end AllBoards() constructor



//------------------------------------------------------------------------------------------------------------------
void displayDirections()
{
    cout << "Welcome to Vexed!  \n"
         << "The objective is to place identical pieces next to each other, so that they vanish,   \n"
         << "clearing the board completely within the indicated number of moves. On each move      \n"
         << "enter the row, column, and direction (L or R) to move, in either upper or lower       \n"
         << "case. You may also enter 'x' to exit the program, or 'r' to reset the current level. \n"
         << endl;
}


//------------------------------------------------------------------------------------------------------------------
// Driver for the program, using the classes and functions declared above
int main()
{
    AllBoards allTheBoards;     // Reads in and stores all the boards from a data file
    int currentBoardIndex = 0;  // Starting board index
    Board theBoard;             // The board instance, that is set to hold the values for each 
    int score = 0;              // Score accumulates par points for each level finished
    int repeatOrContinue = 0;
    char move;

    displayDirections();
    do{
      theBoard = allTheBoards.getBoard( currentBoardIndex);
	    theBoard.displayBoard();
      repeatOrContinue = theBoard.boardDirections(currentBoardIndex);
      if (repeatOrContinue == -1)
        currentBoardIndex++;
      else if (repeatOrContinue == -2)
        continue;
      else {
        currentBoardIndex = repeatOrContinue;
        continue;
      }

    }while(true);
	  

    return 0;
}

