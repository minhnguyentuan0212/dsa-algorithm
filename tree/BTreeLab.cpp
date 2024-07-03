#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <class K, class D, int M> // K: key, D: data, M: degree of BTree
class BTree {
public:
    class Node;
    class Entry;
private:
    Node *root;
public:
    BTree() : root(0) {};
    ~BTree() {}
public:
    class Entry {
    private:
        K key;
        D data;
        Node *rightPtr;
        friend class BTree<K, D, M>;
    public:
        Entry(K key = K{}, D value = D{}) : key(key), data(value), rightPtr(0) {}
        ~Entry() {}
        string toString() {
            stringstream ss;
            ss << "<"
               << this->key << ","
               << this->data
               << ">";
            return ss.str();
        }
    };
public:
    class Node {
    private:
        Node *firstPtr;
        int numEntries;
        Entry entries[M - 1];
        friend class BTree<K, D, M>;
    public:
        Node() : firstPtr(0), numEntries(0) {};
        ~Node() { }
        bool isFull() {
            return (numEntries >= M - 1);
        }
        string toString() {
            stringstream ss;
            ss<<"[(";
            ss<<this->numEntries;
            ss<<")";
            for (int i = 0; i < this->numEntries; i++){
                ss<<this->entries[i].toString();
            }
            ss<<"]";
            return ss.str();
        }
        
    };
    string ToStringPreOrder(Node *node){
        stringstream ss;
        if (node) {
            ss<<node->toString()<<" ";
            ss<<ToStringPreOrder(node->firstPtr);
            for (int i = 0; i < node->numEntries; i++){
                ss<<ToStringPreOrder(node->entries[i].rightPtr);
            }
    }
    return ss.str();
    }       
    string toStringPreOrder() {
        return ToStringPreOrder(this->root); 
    }
    bool Search(Node *node, const K& key, Node *&oN, int &oE){
    if (node){
    int i = 0;
    for (; i < node->numEntries; i++){
        if (key == node->entries[i].key) {
            oN = node; oE = i;
            return true;
        }
        if (key < node->entries[i].key){
            if (i == 0) return Search(node->firstPtr, key, oN, oE);
            else return Search(node->entries[i-1].rightPtr, key, oN, oE);
        }
    }
    if (i == node->numEntries) return Search(node->entries[i-1].rightPtr, key, oN, oE);
    }
    return false;
}
    bool search(const K& key, Node*& outNodePtr, int& outEntryIdx) {
        return Search(root, key, outNodePtr, outEntryIdx);
    }

void insertEntry(Node *pNode, int entryNdx, const Entry &newEntry) { //root, 1, upEntry
        int shifter = pNode->numEntries ; // 2
        while (shifter > entryNdx){    
            pNode->entries[shifter] = pNode->entries[shifter - 1];
            shifter--;
        }
        pNode->entries[shifter] = newEntry;
        pNode->numEntries++;
    }
    void splitNode(Node *pNode, int entryNdx, Entry &upEntry) {
        int minEntries; // =1
        if (M%2) minEntries = M/2;
        else minEntries = M/2 - 1;
        int fromNdx;
        Node *rightPtr = new Node();
        if (entryNdx <= minEntries) fromNdx = minEntries;
        else fromNdx = minEntries + 1;
        int toNdx = 0;
        rightPtr->numEntries = pNode->numEntries - fromNdx;
        while (fromNdx <= pNode->numEntries - 1){
            rightPtr->entries[toNdx] = pNode->entries[fromNdx];
            fromNdx++;
            toNdx++;
        }
        pNode->numEntries -= rightPtr->numEntries;
        if (entryNdx <= minEntries) {insertEntry(pNode, entryNdx, upEntry); pNode->numEntries--;}
        else {
            insertEntry(rightPtr, entryNdx - minEntries - 1, upEntry);
            pNode->numEntries--;
        }
        
        int medianNdx = minEntries;
        upEntry.data  = pNode->entries[medianNdx].data;
        upEntry.key = pNode->entries[medianNdx].key;
        upEntry.rightPtr = rightPtr;
        rightPtr->firstPtr = pNode->entries[medianNdx].rightPtr;
    }   

    int searchNode(Node *nodePtr, K key) {
        int idx;
        if (key < nodePtr->entries[0].key) return 0;
        else {
            idx = nodePtr->numEntries;
            while (key < nodePtr->entries[idx-1].key) idx--;
        }
        return idx;
    }

     bool insertNode(Node *&root, const K &key, const D &data, Entry &upEntry) {
        int entryNdx;
        bool taller;
        Node *subTree;
        if (root){
            entryNdx = searchNode(root, key);
            if (entryNdx) subTree = root->entries[entryNdx-1].rightPtr;
            else subTree = root->firstPtr;
            taller = insertNode(subTree, key, data, upEntry);
            if (taller) {
            if(root->isFull()) {
                splitNode(root, entryNdx, upEntry); taller = true;
            }
            else {
                insertEntry(root, entryNdx, upEntry);
                taller = false;
            }
            }
        }
        else {
            upEntry.data = data;
            upEntry.key = key;
            upEntry.rightPtr = NULL;
            taller = true;
        }
    return taller;
    }

    void insert(Node *&root, const K &key, const D &data) {
        Entry upEntry;
        bool taller = insertNode(root, key, data, upEntry);
        if (taller){
            Node *newNode = new Node();
            newNode->entries[0].data = upEntry.data;
            newNode->entries[0].key = upEntry.key;
            newNode->entries[0].rightPtr = upEntry.rightPtr;
            newNode->firstPtr = root;
            newNode->numEntries = 1;
            root = newNode;
        }
    }
    void insert(const K &key, const D &data) {
        insert(root, key, data);
    }

    void testPrintNode(K* keys, D* data, int size) {
        Node node;

        for (int idx = 0; idx < size; idx++) {
            node.entries[idx].key = keys[idx];
            node.entries[idx].data = data[idx];
        }
        node.numEntries = size;
        cout << node.toString() << endl;
    }
};

int main(){
BTree<int, int, 4> bTree;
int keys[] = {9, 21, 14, 20, 22, 24, 30, 2, 10, 99, 11, 3, 5};
int size = sizeof(keys) / sizeof(int);

for (int idx = 0; idx < size; idx++) {
    bTree.insert(keys[idx], idx);
    cout << bTree.toStringPreOrder() << endl;
}

cout << bTree.toStringPreOrder() << endl;
}