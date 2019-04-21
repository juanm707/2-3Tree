//Description: Implementations for the 2-3 tree class.

#include "TTTree.h"
#include "time.h"
#include <iomanip>
#include <sstream>

//Constructor
TTTree::TTTree() {
    root = NULL;
}

//Returns true if there are no nodes in the tree
bool TTTree::isEmpty(){
    return root == NULL;
}

//Used to implement the search function in the main
//program.
void TTTree::contains() const {
    string input;
    TTNode *foundNode = NULL;
    cout << "Search word: ";
    cin >> input;
    if(containsHelper(input, root, foundNode)){

        if(foundNode->leftKey == input) {
            cout << "Line Numbers: " << foundNode->leftLines[0];
            for(int i = 1; i < foundNode->leftLines.size(); i++)
                cout << ", " <<foundNode->leftLines[i];
            cout << '\n';
        }
        else { //equal to position right key
            cout << "Line Numbers: " << foundNode->rightLines[0];
            for(int i = 1; i < foundNode->rightLines.size(); i++)
                cout << ", " <<foundNode->rightLines[i];
            cout << '\n';
        }
    }
    else
        cout << '\"' << input <<"\" is not in the document\n";
}

//Used by contains() to see if a words is present or not. Will
//give contains() a pointer to the found node so that contains()
//can prints the lines the word was found on.
bool TTTree::containsHelper(const string & x, TTNode * t, TTNode * &result) const{
    if (t == NULL)
        return false;
    if ((t->leftKey == x) || (t->rightKey == x)) {
        result = t;
        return true;
    }
    else if (x < t->leftKey)
        return containsHelper(x, t->left, result);
    else if (t->rightKey.empty() || (x < t->rightKey))
        return containsHelper(x, t->center, result);
    else
        return containsHelper(x, t->right, result);
}

//Prints the index to the supplied receiver, either
//cout or the output file
void TTTree::printTree(ostream & out) const {
    out << "2-3 Tree Index:\n-------------------------\n";
    printTreeHelper(root, out);
}

//Called by printTree(), does the actual formatted printing
void TTTree::printTreeHelper(TTNode* t, ostream & out) const{
    if(t == NULL)
        return;
    else {
        printTreeHelper(t->left, out);
        out << setw(30) << std::left;
        out << t->leftKey << " " << t->leftLines[0]; //left is filled first
        for (int i = 1; i < t->leftLines.size(); i++)
            out << ", " << t->leftLines[i];
        out << endl;

        if (t->rightKey == "") { //since right key is empty, there is no middle child
            printTreeHelper(t->center, out); //but this implementation, if right empty, center = right child, and right is null
        }
        else if (t->rightKey != "") {
            printTreeHelper(t->center, out);
            out << setw(30) << std::left;
            out << t->rightKey << " " << t->rightLines[0];
            for (int i = 1; i < t->rightLines.size(); i++)
                out << ", " << t->rightLines[i];
            out << endl;
            printTreeHelper(t->right, out);
        }
    }
}


//Receives the specified input file and constructs
//the actual tree. Prints a message when finished.
void TTTree::buildTree(ifstream & input){
    int line = 1, numWords = 0, distWords = 0, treeHeight = 0;
    stringstream tempWord;
    double totalTime, finishTime, startTime = clock();
    while (!input.eof()) {
        string tempLine, tempWord;

        //Read a whole line of text from the file
        getline(input, tempLine);
        for (int i = 0; i < tempLine.length(); i++) {
            //Insert valid chars into tempWord until a delimiter( newline or space) is found
            while (tempLine[i] != ' '&& tempLine[i] != '\n' && i < tempLine.length() ) {
                tempWord.insert(tempWord.end(), tempLine[i]);
                i++;
            }

            //Trim any punctuation off end of word. Will leave things like apostrophes
            //and decimal points
            while(tempWord.length() > 0 && !isalnum(tempWord[tempWord.length() - 1]))
                tempWord.resize(tempWord.size() -1);

            if (tempWord.length() > 0)
            {
                //Once word is formatted,call insert with the word, the line of the input
                //file it came from, the root of our tree, and the distinct word counter
                root = insertHelper(tempWord, line, root, distWords);

                //Increment our total number of words inserted
                numWords++;

                //Clear out tempWord so we can use it again
                tempWord.clear();
            }

        }
        line++;
    }
    //Do time and height calculation
    finishTime = clock();
    totalTime = (double) (finishTime - startTime)/CLOCKS_PER_SEC;
    treeHeight = findHeight(root);

    //Print output
    cout << "\n2-3 Tree Info\n";
    cout << "-------------\n";
    cout << setw(40) << std::left;
    cout << "Total number of words: " << numWords<< endl;

    cout << setw(40) << std::left
         << "Total number of distinct words: " << distWords << endl;

    cout << setw(40) << std::left
         <<"Total time spent building index: " << totalTime << endl;

    cout << setw(40) << std::left
         <<"Height of 2-3 Tree is: " << treeHeight << endl;

}


//x is the word to insert, line is the line in the text file
//the word was found at, TTNode is the node of the tree being
//examined, and distWord is incremented if a new word is created
//and used by buildTree
TTTree::TTNode* TTTree::insertHelper(const string & X, int line, TTNode* & t, int & distWords) {

    if (t == NULL) {
        t = new TTNode(X, "", NULL, NULL, NULL);
        t->leftLines.push_back(line);
        distWords++;
        return t;
    }

    // At leaf node: insert here
    if(t->isLeaf()) {

        if(X == t->leftKey) {
            t->leftLines.push_back(line);
            return t;
        }
        else if (X == t->rightKey) {
            t->rightLines.push_back(line);
            return t;
        }

        distWords++;

        TTNode* _old = new TTNode(X, "", NULL, NULL, NULL);
        _old->leftLines.push_back(line);

        TTNode* _new = t->add(_old, line);

        return _new;
    }

    //not a leaf
    //insert left
    else if (X < t->leftKey) {
        TTNode* retval = insertHelper(X, line, t->left, distWords);
        if (retval == t->left)
            return t;
        else
            return t->add(retval, line);
    }
    else if((X == t->leftKey)) {
        t->leftLines.push_back(line);
        return t;
    }
    else if((X == t->rightKey)) {
        t->rightLines.push_back(line);
        return t;
    }

    else if((t->rightKey == "") || (X < t->rightKey)) {
        TTNode* retval = insertHelper(X, line, t->center, distWords);
        if (retval == t->center)
            return t;
        else
            return t->add(retval, line);
    }
    //insert right
    else {
        TTNode* retval = insertHelper(X, line, t->right, distWords);
        if (retval == t->right)
            return t;
        else return t->add(retval, line);

    }
}

TTTree::TTNode* TTTree::TTNode::add(TTNode* it, int line) {

    // Only one key, add here
    if(this->rightKey == "") {
        if(this->leftKey < it->leftKey) {
            this->rightKey = it->leftKey;
            this->center = it->left;
            this->right = it->center;

            //this->rightLines.push_back(line); //linesss
            this->rightLines = it->leftLines; //linesss
        }
        else {
            this->rightKey = this->leftKey;
            this->left = it->left; //added this
            this->right = this->center;
            this->leftKey = it->leftKey;
            this->center = it->center;

            //swtich lines linesss
            rightLines = leftLines;
            leftLines.resize(0);
            //leftLines.push_back(line);
            this->leftLines = it->leftLines;
        }
        return this;
    }

    else if(it->leftKey < this->leftKey) { //add left

        TTNode* n1 = new TTNode(this->leftKey, "", it, this, NULL);

        n1->leftLines = this->leftLines; //linesss

        //it->setLeftChild(this->left);

        this->left = this->center;
        this->center = this->right;
        this->right = NULL;
        this->leftKey = this->rightKey;

        this->leftLines = this->rightLines; //linesss

        this->rightKey = "";

        this->rightLines.resize(0); //linesss

        return n1;
    }

    else if(it->leftKey < this->rightKey) { //add center

        TTNode* check = it->left; //added this

        TTNode* newNode = new TTNode(this->rightKey, "", it->center, this->right, NULL);
        newNode->leftLines = this->rightLines; //linessss

        it->setCenterChild(newNode);
        it->setLeftChild(this);
        this->rightKey = "";

        this->rightLines.resize(0); //linesss

        this->center = check; //added this
        this->right = NULL;
        return it;
    }

    else { //add right
        TTNode* n1 = new TTNode(this->rightKey, "", this, it, NULL);
        n1->leftLines = this->rightLines; //linesss

        //it->setLeftChild(this->right);
        this->right = NULL;
        this->rightKey = "";

        this->rightLines.resize(0); //linesss

        return n1;
    }
}

//Returns height of tree. If tree has only one node, height is 1
int TTTree::findHeight(TTNode* t){
    if(t == NULL)
        return 0;
    else {
        int leftHeight = findHeight(t->left), rightHeight = findHeight(t->right);
        if(leftHeight > rightHeight)
            return(leftHeight+1);
        else
            return(rightHeight+1);
    }
}

bool TTTree::search(const string word) {
    return searchHelper(word, root);
}

bool TTTree::searchHelper(const string & word, TTNode * t) {
    if (t == NULL)
        return false;
    if ((t->leftKey == word) || (t->rightKey == word)) { //if its equal to either the left or right key
        return true;
    }
    else if (word < t->leftKey)
        return searchHelper(word, t->left);
    else if (t->rightKey.empty() || (word < t->rightKey))
        return searchHelper(word, t->center);
    else
        return searchHelper(word, t->right);
}