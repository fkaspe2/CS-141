/* ------------------------------------------------
 * WorkPlay.cpp
 * 
 * Prog 3: Uses the dictionary to bridge words together 
 * and see how they are bridged by shifting indivisual letters.
 * Allow user to play a game using this concept and see the 
 * full tree of connected letters.
 *
 * Class: Program #3 for CS 141, Fall 2019
 * System: Codio
 * Author: Frank Kasper
 *
*/
#include <iostream>
#include <string>
#include <fstream>      // For file input
#include <vector>		// For dictionary vector
#include <iomanip>		// For setw()
#include <cctype>       // For tolower()


using namespace std;


//---------------------------------------------------------------
// Display ID info
//
void displayIdInfo()
{
    cout << " \n"
         << "Program #3: Work Play   \n"
             << "Author: Dale Reed   \n"
         << "Lab: Tues 8am           \n"
         << "System:  Codio          \n"
         << " \n";
}//end displayIDInfo()


//-----------------------------------------------------------------------------------------
//  You should use parameters for the dictionary, the word lengths array, 
//  the length of words to use, and the total number of words.
// *** Yuwei: function parameters also need to be documented.
void readInWordsFromFile(vector< string>& dictionary, int wordLengths[], int lengthOfWordsToUse, int& wordCount )
{
    dictionary.clear();
	ifstream inputFileStream;
	
    string fileName = "dictionary.txt"; // C string (array of char) to store filename
    string inputWord;				    // stores each word as it is read

	// Open input file
	inputFileStream.open( fileName.c_str() );

   // Verify that the open worked
    if( !inputFileStream.is_open()) {
        cout << "Could not find input file " << fileName << "  Exiting..." << endl;
        exit( -1);
    }
    
    wordCount = 0;
    
	// Read all the words from the file and store them
    while( inputFileStream >> inputWord) {
        inputWord.at(0) = tolower(inputWord.at(0));
        wordLengths[inputWord.length()]++;
        wordCount++;
        
        if (inputWord.length() == lengthOfWordsToUse){
            dictionary.push_back(inputWord);
        }
    }
    
    inputFileStream.close();    // Close the input file.
}


//--------------------------------------------------------------------------------------
// Use binary search to look up the search word in the dictionary vector, returning
// the word's index if found, -1 otherwise.
//
long binarySearch(
            string searchWord,            // word to be looked up
            vector< string> dictionary)   // the dictionary of words
{
    long low, mid, high;     // array indices for binary search
    long searchResult = -1;  // Stores index of word if search succeeded, else -1
    
    // Binary search for word
    low = 0;
    high = dictionary.size() - 1;
    while ( low <= high)  {
        mid = (low + high) / 2;
        // SearchResult negative value means word is to the left, positive value means
        // word is to the right, value of 0 means word was found
        searchResult = searchWord.compare( dictionary[ mid] );
        if ( searchResult == 0)  {
            // Word IS in dictionary, so return the index where the word was found
            return mid;
        }
        else if (searchResult < 0)  {
            high = mid - 1; // word should be located before the mid location
        }
        else  {
            low = mid + 1; // word should be located after the mid location
        }
    }
    
    // Word was not found
    return -1;
}//end binarySearch()

//--------------------------------------------------------------------------------------
//Takes in a user entered word and checks if it is valid. Prompts the user to reenter otherwise
//If valid store 
// *** Yuwei: function parameters also need to be documented.
void wordCheck(string& word, vector<string> dictionary, int lengthOfWordsToUse, int choice) {
    if (word == "exit") {
        cout << endl << "Exiting program." << endl;
        exit(0);
    }
    //searches for a random word in dictionary
    else if (word == "r") {
        word = dictionary.at(rand() % dictionary.size());
    }
    //allows reentry is word size doesnt match
    if (word.length() != lengthOfWordsToUse) {
        while (word.length() != lengthOfWordsToUse){
            cout << endl <<  "   *** '" << word << "' is not of length " << lengthOfWordsToUse << ". Please retry." << endl;
            if (choice == 1){
                cout << "Enter starting word, or 'r' for a random word: ";
            }
            else{
                cout << "Enter ending word, or 'r' for a random word: ";
            }
            cin >> word;
            if (word == "exit") {
                cout << endl << "Exiting program." << endl;
            exit(0);
            }
        }
    }
    //allows reentry is word isn't in dictionary
    if (binarySearch(word, dictionary) == -1) {
        while (binarySearch(word, dictionary) == -1){
            cout << "   *** '" << word << "' is not in the dictionary. Please retry." << endl;
            if (choice == 1){
                cout << "Enter starting word, or 'r' for a random word: ";
            }
            else{
                cout << "Enter ending word, or 'r' for a random word: ";
            }
            cin >> word;
            if (word == "exit") {
                cout << endl << "Exiting program." << endl;
            exit(0);
            }
        }
    }
}

//--------------------------------------------------------------------------------------
//Takes two user entered words and calls functions to check if they work
// *** Yuwei: function parameters also need to be documented.
void enterWords (string& startWord, string& endWord, vector<string> dictionary, int lengthOfWordsToUse) {
    //OPTIONS FOR FIRST WORD
            int first=1;
            cout << "Enter starting word, or 'r' for a random word: ";
            cin >> startWord;
            wordCheck(startWord, dictionary, lengthOfWordsToUse, first);
            
    //OPTIONS FOR SECOND WORD
            int second=2;
            cout << endl
                 << "Enter ending word, or 'r' for a random word: ";
            cin >> endWord;
            wordCheck(endWord, dictionary, lengthOfWordsToUse, second);
}

//--------------------------------------------------------------------------------------
//User starts at one word and moves through the dictioary to try and reach the second word
//Can only move by one character at a time
// *** Yuwei: function parameters also need to be documented.
void WordPlayGame(string startWord, string endWord, int lengthOfWordsToUse, vector< string> dictionary) {
    if (startWord == "" || endWord == ""){
        cout << endl << "One or both word(s) are blank. Please enter two valid words." 
             << endl << "Returning to menu." << endl << endl;
        return;
    }
    
    string userWord = startWord;   //sets the initial word in sequence to the starting word
    string tempWord = userWord;    //for sake of comparison
    int turnNumber = 1;            //tracks turns of game
    int charCounter=0;             //counts number of characters changed for a word (should be only 1)
    int i=0;                       //for loop tracker
    
    //loops until user enters correct word or exits
    while(userWord != endWord) {
        i=0;
        charCounter=0;
        cout << " " << turnNumber << ". Previous word is '" << tempWord << "'.  Next word: ";
        cin >> userWord;
        cout << endl;
        
        if (userWord == "exit") {
            break;
        }
        //retry if word length doesn't work
        else if (userWord.length() != lengthOfWordsToUse){
            cout << "    *** '" << userWord << "' is not of length 3.  Please retry." << endl;
            cout << " " << turnNumber << ". Previous word is '" << tempWord << "'.  Next word: ";
            cin >> userWord;
            if (userWord == "exit") {
                break;
            }
            continue;            
        }
        //retry if word not in dictionary
        else if (binarySearch(userWord, dictionary) == -1) {
            cout << "    *** '" << userWord << "' is not in the dictionary.  Please retry." << endl;
            cout << " " << turnNumber << ". Previous word is '" << tempWord << "'.  Next word: ";
            cin >> userWord;
            if (userWord == "exit") {
                break;
            }
            continue;
        }
        //checks if word is only one character different
        while (i < userWord.length()) {
            if (userWord.at(i) != tempWord.at(i)){
                charCounter++;
            }
            i++;
        }
        if(charCounter == 1) {
            tempWord = userWord;
            turnNumber++;
        }
        else {
            cout << "    *** '" << userWord << "' must be exactly 1 character different.  Please retry." << endl;
            cout << " " << turnNumber << ". Previous word is '" << tempWord << "'.  Next word: ";
            cin >> userWord;
            if (userWord == "exit") {
                break;
            }
            continue;
        }
    }
    
    //if user connects the start and end words
    if(userWord == endWord){
        cout << "Congratulations, you did it!" << endl << endl;
    }
}

//--------------------------------------------------------------------------------------
//Checks to make sure a word isn't listed twice in cases 5,6, and 7
// *** Yuwei: function parameters also need to be documented.
bool checkForRepeats (string scanThroughLetters, vector<string> wordTree){
    for (int i=0; i<wordTree.size(); i++) {
        if (scanThroughLetters == wordTree.at(i)){
            return true;
        }
    }
    return false;
}

//--------------------------------------------------------------------------------------
//Takes starting word and cycles through characters until there is a bridge between word 1 and word 2
//Case 5 displays the sequence
//Case 6 only lets the user know if it's possible
//Case 7 prints the sequence in which the words are bridged together
// *** Yuwei: function parameters also need to be documented.
void debugSequence (vector<string> dictionary, 
                    vector<string> wordTree, 
                    vector<int> parentIndexVector,
                    string startWord, 
                    string endWord,
                    int display
                    ){
    int i=0;                                    //loop counter for for loop
    int looper=0;                               //loop counter for while loop
    int indexNum=0;                             //tracks the index of each word that gets used
    int numWordInSequenceScanned = 0;           //tracks the word that will be currently scanned
    char asciiLoop;                             //cycles through alphabet
    string wordNowBeingScanned = startWord;     //sets first word to the starting word
    
    vector<int> winningSequence;                //vector storing succesful bridge sequence (case 7)
    wordTree.push_back(startWord);
    parentIndexVector.push_back(numWordInSequenceScanned);  //stores the parent index of each word
    
    //if end of loop is reached, there are no possible routes from word1 to word2
    while (looper < wordTree.size()){
    
        //runs through every letter in each character for every word
        for (i=0; i<startWord.length(); i++) {
            wordNowBeingScanned = wordTree.at(numWordInSequenceScanned);    //stores the current word being scanned and checked
            asciiLoop = 97;
            
            //runs through characters a-z
            while (asciiLoop != 123) {
                //prints the word being scanned for each iteration if case 5
                //this is the "parent" word
                if ( (asciiLoop == 97) && (i==0) && display == 0) {
                    cout << endl <<  numWordInSequenceScanned << ". " << wordNowBeingScanned << ":  ";
                }
                
                wordNowBeingScanned[i] = asciiLoop;    //cycles through each letter in each character sequence
                //checks if word is in dictionary and the word hasn't already been encounterd in the loop
                if (binarySearch(wordNowBeingScanned, dictionary) != -1  &&  checkForRepeats(wordNowBeingScanned, wordTree) == 0) {
                    indexNum++;
                    wordTree.push_back(wordNowBeingScanned);
                    parentIndexVector.push_back(numWordInSequenceScanned);
                    
                    //prints the each possible word that stems from the "parent" word
                    if (display == 0) {
                        cout << " " << indexNum << ":" << wordTree.at(indexNum);
                    }
                    
                    //stores data for case 7
                    //stores the winning test cases by checking the parent index of each feesible terms
                    if (wordTree.at(indexNum) == endWord){
                    int winningIndexes = indexNum;
                    int i=0;
                        while(winningIndexes >= 0) {
                            winningSequence.push_back(winningIndexes);
                            winningIndexes = parentIndexVector.at(winningIndexes);
                            i++;
                            if (winningIndexes == 0){
                                winningSequence.push_back(0);
                                break;
                            }
                        }
                        break;
                    } //end case 7 storage
                    
                }
                asciiLoop++;
            }//end while(ascii) loop
            
            //prints once the words are matched
            if (wordTree.at(indexNum) == endWord && display != 2){
                cout << endl << endl << "Winning sequence was found!" << endl;
                break;
            }
        }//end of for loop
        
        numWordInSequenceScanned++;    //tracks the parent index
        
        //if the word was found with no problems, break out of loop
        if (wordTree.at(indexNum) == endWord){
            break;
        }
        //otherwise print that a bridge is not possible between words
        else if (looper == wordTree.size()){
        cout << endl << endl << "It is not possible to go from " 
             << startWord << " to " << endWord << " using the current dictionary." 
             << endl;  
        }
        looper++;
    }//end of while wordTree.size() loop
    
    //prints data for case 7
    if (display == 2  ) {
        int size = winningSequence.size();
       
        cout << "Winning sequence in reverse order is:" << endl;
        i=0;
        while (size > i) {
            cout << setw(5) << winningSequence.at(i) << ". " << wordTree.at(winningSequence.at(i)) << endl;
            i++;
        }   
    }
}


//-----------------------------------------------------------------------------------------
int main()
{
    vector< string> dictionary;    		// Vector of dictionary words read in from file
    int lengthOfWordsToUse = 3;         // Default length of word to use in word transformation
    string startWord = "dog";           // The start word for transformation
    string endWord = "cat";             // The end word for transformation
    int menuOption = -1;                // User menu option selection\
    
    int wordCount;                      // Tracks number of words in dictionary file
    int wordLengths[100] = {0};         // Array counts how many words of each length 
                                        // (assuming a word is no longer than 100 characters)
    
    // Display ID info
    displayIdInfo();
    
    // Seed the random number generator
    srand( 1);  // Change 1 to time(0) for non-predictable results, but leave as 1 for testing
    
    readInWordsFromFile(dictionary, wordLengths, lengthOfWordsToUse, wordCount);
    
    //display a chart of number of words in file by their length,
    //only shows for word lengths that appear over 1400 times
    cout << "Total number of words in dictionary file: " << wordCount << endl << endl;
    cout << "Word lengths where there are more than 1400 words:" << endl;
    cout << "Length  How Many" << endl;
    cout << "------  --------" << endl;
    for (int i=0; i < 50; i++){
        if( wordLengths[i] > 1400) {
            cout << setw(5) << i << setw(10) << wordLengths[i] << endl;                
        }
    }
    
    // Menu display and handling infinite loop
    do {       
        cout << endl << "Currently we have " << dictionary.size() << " words of length "
             << lengthOfWordsToUse << " in the dictionary.  \n"
             << "Changing from '" << startWord << "' to '" << endWord << "'" << endl
             << endl;
        
        cout << "Choose from the following options:  \n"
             << "   1. Change the word length        \n"
             << "   2. Display some dictionary words \n"
             << "   3. Get start and end words       \n"
             << "   4. Play the word change game     \n"
             << "   5. Find the end word with debug  \n"
             << "   6. Find the end word             \n"
             << "   7. Display an answer sequence    \n"
             << "   8. Exit the program              \n"
             << "Your choice -> ";
        cin >> menuOption;
        cout << endl << endl;
				 
		if (menuOption == 1) {
            cout << "What length words do you want to use? ";
            cin >> lengthOfWordsToUse;
            readInWordsFromFile(dictionary, wordLengths, lengthOfWordsToUse, wordCount);
            startWord = "";
            endWord = "";
        } 
        
        else if (menuOption == 2) {
            int index1, index2;
            cout << "Enter the start and end index values of words to display: ";
            cin >> index1;
            cin >> index2;
            cout << endl << "About to display dictionary words from " << index1 << " to " << index2 << endl;
            for (int i=index1; i <= index2; i++ ){
                cout << setw(5) << i << " " << dictionary.at(i) << endl;
            }
        } 
        
        else if (menuOption == 3) {
            enterWords(startWord, endWord, dictionary, lengthOfWordsToUse);
        } 
        
        else if (menuOption == 4) {
            WordPlayGame(startWord, endWord, lengthOfWordsToUse, dictionary);
        } 

        else if (menuOption == 5) {
            vector<string> wordTree;
            vector<int> parentIndexVector;
            //0 at end means bypasses displaying debugging information
            debugSequence(dictionary, wordTree, parentIndexVector, startWord, endWord, 0);
        } 
        
        else if (menuOption == 6) {
            vector<string> wordTree;
            vector<int> parentIndexVector;
            //1 at end means displays debugging information
            debugSequence(dictionary, wordTree, parentIndexVector, startWord, endWord, 1);
        } 
        
        else if (menuOption == 7) {
            vector<string> wordTree;
            vector<int> parentIndexVector;
            
            //2 at end means stores data for this case and the winning sequence only
            debugSequence(dictionary, wordTree, parentIndexVector, startWord, endWord, 2);
        } 
        
        else if (menuOption == 8) {
            cout << "Exiting the program" << endl;
            break;
            
        } 
        else {
            continue;
        }
		
    } while( true);
	
    //Good-night, sweet prince
    return 0;
}//end main()

