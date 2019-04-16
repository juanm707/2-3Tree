//Description: Prototypes for the 2-3 tree class.

#ifndef TTTREE_H
#define TTTREE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

class TTTree {
    public:
        TTTree(); //constructor
        void contains() const;
        bool isEmpty();
        void printTree(ostream & out = cout) const;
        void buildTree(ifstream & input);
        bool search(string word);

    private:
        struct TTNode {
            string leftKey, rightKey;
            TTNode* left;
            TTNode* center;
            TTNode* right;
            vector<int> leftLines, rightLines;

            TTNode() {
                left = center = right = NULL;
                leftLines.resize(0);
                rightLines.resize(0);
            }

            TTNode(string lkey, string rkey, TTNode* p1, TTNode* p2, TTNode* p3) {
                leftKey = lkey;
                rightKey = rkey;
                left = p1;
                center = p2;
                right = p3;
                leftLines.resize(0);
                rightLines.resize(0);
            }

            bool isLeaf() { return left == NULL; }

            TTNode* lchild() { return left; }
            TTNode* rchild() { return right; }
            TTNode* cchild() { return center; }

            string lkey() { return leftKey; }
            string rkey() { return rightKey; }

            void setLeftKey(string k) { leftKey = k; }
            void setRightKey(string k) { rightKey = k; }

            void setLeftChild( TTNode* it) { left = it; }
            void setRightChild( TTNode* it) { right = it; }
            void setCenterChild( TTNode* it) { center = it; }

            TTNode* add(TTNode* it, int line);
        };

        TTNode* root;
        TTNode* insertHelper(const string & X, int line, TTNode* & t, int &distWords);
        bool containsHelper(const string & x, TTNode* t, TTNode* &result) const;
        void printTreeHelper(TTNode* t, ostream & out) const;
        int findHeight(TTNode* t);
        bool searchHelper(const string & word, TTNode * t);
};


#endif //TTTREE_H
