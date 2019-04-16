//Description: Takes a text file supplied by the user
//             and turns it into a word index, implemented
//             through the use of a BST 

#include <iostream>
#include <fstream>
#include <iomanip>
#include "bst.h"
#include "TTTree.h"
using namespace std;

vector<string> getDistinctWords(istream& input);

int main(int argc, char* argv[]) {
	int choice;
	/*if (argc != 2) {
	    cout << "Incorrect input. Correct format: ./<exectuable.out> <inputtext.txt>\n";
	    return 1;
	}*/

    string filename = "/Users/juanmartinez/Downloads/bst/tale.txt";
    ifstream input;
	//ifstream input(argv[1]);
    //ifstream input (filename, ifstream::in);
    input.open(filename, ifstream::in);

	BST myBST_Tree;
    TTTree my2_3Tree;

	if(input.is_open()) {
        char c;
        cout << "Options: (a) BST, (b) 2-3 Tree, (c) Compare BST and 2-3 Tree\n";
        cin >> c;

        //choices
        //BST
        if (c == 'a') {
            myBST_Tree.buildTree(input);
            input.close();
            while (1) {
                choice = 0;
                cout << "Options: (1) display index, (2) search, (3) save index, (4) quit\n";
                cin >> choice;

                //Print index
                if (choice == 1)
                    myBST_Tree.printTree(cout);

                    //Search index for a word
                else if (choice == 2)
                    myBST_Tree.contains();

                    //Save index
                else if (choice == 3) {
                    string outputFile;
                    cout << "Enter a filename to save your index to (Suggested: <filename>.txt) : ";
                    cin >> outputFile;
                    ofstream output(outputFile.c_str());

                    if (output.fail()) {
                        std::cout << "Failed to open outputfile.\n";
                    }

                    myBST_Tree.printTree(output);
                    output.close();
                    cout << "Saved\n";
                }
                    //Quit
                else
                    break;
            }
        } //end BST

            //2-3Tree
        else if (c == 'b') {

            my2_3Tree.buildTree(input);
            input.close();
            while (1) {
                choice = 0;
                cout << "Options: (1) display index, (2) search, (3) save index, (4) quit\n";
                cin >> choice;

                //Print index
                if (choice == 1)
                    my2_3Tree.printTree(cout);

                    //Search index for a word
                else if (choice == 2)
                    my2_3Tree.contains();

                    //Save index
                else if (choice == 3) {
                    string outputFile;
                    cout << "Enter a filename to save your index to (Suggested: <filename>.txt) : ";
                    cin >> outputFile;
                    ofstream output(outputFile.c_str());

                    if (output.fail()) {
                        std::cout << "Failed to open outputfile.\n";
                    }

                    my2_3Tree.printTree(output);
                    output.close();
                    cout << "Saved\n";
                }
                    //Quit
                else
                    break;
            }
        }

        else if (c == 'c') {
            //If option (c) is chosen, the program builds both the BST and 2-3 Tree, creates the index
            myBST_Tree.buildTree(input);
            input.clear();
            input.seekg(0, input.beg);

            my2_3Tree.buildTree(input);
            input.clear();
            input.seekg(0, input.beg);

            vector<string> searchList = getDistinctWords(input);
            input.close();

            // and then compares the performance (measured in time)
            // of searching all words in the index in both trees:
            //BST
            double BSTtotalTime, BSTfinishTime, BSTstartTime = clock();
            for(auto const& word: searchList) {
                if(myBST_Tree.search(word)) {
                    //if found move on
                }
                else {
                    cout << "ERROR in searching BST for " << word << endl;
                }
            }
            //Do time and height calculation
            BSTfinishTime = clock();
            BSTtotalTime = (double) (BSTfinishTime - BSTstartTime)/CLOCKS_PER_SEC;

            //2-3 Tree
            double TT_totalTime, TT_finishTime, TT_startTime = clock();
            for(auto const& word: searchList) {
                if(my2_3Tree.search(word)) {
                    //if found move on
                }
                else {
                    cout << "ERROR in searching 2-3 Tree for " << word << endl;
                }
            }
            //Do time and height calculation
            TT_finishTime = clock();
            TT_totalTime = (double) (TT_finishTime - TT_startTime)/CLOCKS_PER_SEC;

            cout << "\nComparison of Binary Search Tree and 2-3 Tree\n";
            cout << "-----------------------------------------------\n";
            cout << setw(40) << std::left
                 <<"Total time taken by BST: " << BSTtotalTime << endl;

            cout << setw(40) << std::left
                 <<"Total time taken by 2-3 Tree: " << TT_totalTime << endl;

        }
    }
    else {
        cout << "Invalid File Name. Restart Program.\n";
        return 2;
    }
    return 0;
}

vector<string> getDistinctWords(istream& input) {

    vector<string> result;
    while (!input.eof()) {
        string tempLine, tempWord;

        //Read a whole line of text from the file
        getline(input, tempLine);
        for (int i = 0; i < tempLine.length(); i++) {
            //Insert valid chars into tempWord until a delimiter( newline or space) is found
            while (tempLine[i] != ' ' && tempLine[i] != '\n' && i < tempLine.length()) {
                tempWord.insert(tempWord.end(), tempLine[i]);
                i++;
            }

            //Trim any punctuation off end of word. Will leave things like apostrophes
            //and decimal points
            while (tempWord.length() > 0 && !isalnum(tempWord[tempWord.length() - 1]))
                tempWord.resize(tempWord.size() - 1);

            if (tempWord.length() > 0) {
                //Once word is formatted, add it to vector if its not already in there call
                if (std::find(result.begin(), result.end(), tempWord) != result.end()) {
                    // Element in vector.
                    // Do nothing
                } else {
                    // Word is not in vector, so add it
                    result.push_back(tempWord);
                }

                //Clear out tempWord so we can use it again
                tempWord.clear();
            }
        }
    }
    return result;
}