#include <iostream>
using namespace std;

template <class T, int M>
class MWTree {
protected:
    struct Node;
    struct Entry
    {
        T data;
        Node *pRight;
    };
    struct Node
    {
        Node *pLeft;
        Entry e[M-1];
        size_t nE;
    };
    Node *pRoot;
public:
    
};