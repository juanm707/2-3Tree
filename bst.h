//Description: Prototypes for the binary search tree class.

#ifndef BST_H
#define BST_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

class BST{
    public: 
        BST();
        void contains() const;
        bool isEmpty();
        void printTree(ostream & out = cout) const;
        void buildTree(ifstream & input);
		bool search(string word); //added this
    private:
    struct node{
	    node(const string &x, node *l, node *r)
		:key(x), left(l), right(r){
                lines.resize(0);
	    }
	    string key;
	    node * left;
	    node * right;
	    vector<int> lines;
	};
	node * root;
	void insertHelper(const string &X, int line, node *& t, int &distWords);
	bool containsHelper(const string & x, node * t, node* &result) const;
	void printTreeHelper(node *t, ostream & out) const;
	int findHeight(node *t);

	//added this
	bool searchHelper(const string & word, node * t);
};
	
#endif	
    
	

