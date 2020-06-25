#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include "Indexer.h"
#include "Word.h"

using namespace std;

int main(int argc, char* argv[]) {
    string inFilterFile = ""; //Filter file.
    string inDataFile = ""; //Data file.
    string usrResponse = "";

    //Do we have the right number of aruguments?  We will validate those
    //arguments later.
    if (argc != 3) {
        cout << "Usage:  ./Proj2.out filter.file data.file\n" << endl;
        cout << "filter.file - The file that contains the list of words";
        cout << " not to be included." << endl;
        cout << "data.file - The file that contains the text";
        cout << " to be indexed.\n" << endl;

        //This is the main driver.
    }

    else {
        const string FILTER_CPY = "gsl.txt"; inFilterFile = "gsl.txt";
        
        cout << "Welcome to Index Test" << endl;
        
        // Test 1 Indexing without a filter BST 
        cout << "Test 1: Indexing with and without a filter file" << endl;
        cout << "Enter any value to continue: "; cin >> usrResponse;

        try {
            cout << "Testing without a filter file" << endl;
            cout << "Enter any value to continue: "; cin >> usrResponse;

            inFilterFile.clear(); inDataFile = "TestInput1.txt";
            Indexer* index1 = new Indexer(inFilterFile, inDataFile);
            index1->DoIndex();
            delete index1;
            index1 = nullptr;

            cout << "Testing with a filter file" << endl;
            cout << "Enter any value to continue: "; cin >> usrResponse;

            inFilterFile = FILTER_CPY; inDataFile = "TestInput1.txt";
            Indexer* index2 = new Indexer(inFilterFile, inDataFile);
            index2->DoIndex();
            delete index2;
            index2 = nullptr;
        }

        catch (Exceptions& e) {
            cout << "Error " << e.GetMessage() << endl;
	    return 1;
        }

        // Test 2 Indexing without a Word BST (Expect an error) 
        cout << "\nTest 2: Indexing with and without a word file" << endl;
        cout << "Enter any value to continue: "; cin >> usrResponse;
	
        try {
            cout << "Testing without TestInput1.txt (expect an error)" << endl;
            cout << "Enter any value to continue: "; cin >> usrResponse;
            inFilterFile.clear(); inDataFile.clear();
            Indexer* index3 = new Indexer(inFilterFile, inDataFile);
            index3->DoIndex();
            delete index3;
            index3 = nullptr;
        }
        catch (Exceptions& e) {
            cout << "Error " << e.GetMessage() << endl;
        }
	
        cout << "Testing with TestInput1.txt as word file" << endl;
        cout << "Enter any value to continue: "; cin >> usrResponse;
        try {
            inFilterFile = FILTER_CPY; inDataFile = "TestInput1.txt";
            Indexer* index4 = new Indexer(inFilterFile, inDataFile);
            index4->DoIndex();
            delete index4;
            index4 = nullptr;
        }

        catch (Exceptions& e) {
            cout << "Error " << e.GetMessage() << endl;
	    return 1;
        }

        // Test 3 Final 100m
        cout << "\nTest 3: Final Test" << endl;
        cout << "Indexing 3 Test .txt files given" << endl;
        cout << "Enter any value to continue: "; cin >> usrResponse;


        // Input 2
        /*************************************************************/
        try {
            inDataFile = "TestInput2.txt";
            Indexer* index5 = new Indexer(inFilterFile, inDataFile);
            index5->DoIndex();
            delete index5;
            index5 = NULL;
        }
        //Something went wrong.
        catch (Exceptions& cException) {
            cout << "EXCEPTION: " << cException.GetMessage() << endl;
            return 1;
        }
        /*************************************************************/


        // Input 3
        /*************************************************************/
        try {
            inDataFile = "TestInput3.txt";
            Indexer* index6 = new Indexer(inFilterFile, inDataFile);
            index6->DoIndex();
            delete index6;
            index6 = NULL;
        }
        //Something went wrong.
        catch (Exceptions& cException) {
            cout << "EXCEPTION: " << cException.GetMessage() << endl;
            return 1;
        }
        /*************************************************************/


        // Input 4
        /*************************************************************/
        try {
            inDataFile = "TestInput4.txt";
            Indexer* index7 = new Indexer(inFilterFile, inDataFile);
            index7->DoIndex();
            delete index7;
            index7 = NULL;
        }
        //Something went wrong.
        catch (Exceptions& cException) {
            cout << "EXCEPTION: " << cException.GetMessage() << endl;
            return 1;
        }
        /*************************************************************/
        cout << "End of Tests. Check valgrind for memory leaks" << endl;
    }

    //Uncomment for number of seconds running.
    //cout << (clock() / (float)CLOCKS_PER_SEC) << endl;

    return 0;
}
