#include <iostream>
#include <math.h>
#include <queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int &n)
{
    cout << n << " ";
}

template<class T>
class AVLTree
{
public:
    class Node;
private:
    Node *root;
protected:
    int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree(){}
    int getHeight()
    {
        return this->getHeightRec(this->root);
    }
    void printTreeStructure()
    {
        int height = this->getHeight();
        if (this->root == NULL)
        {
            cout << "NULL\n";
            return;
        }
        queue<Node *> q;
        q.push(root);
        Node *temp;
        int count = 0;
        int maxNode = 1;
        int level = 0;
        int space = pow(2, height);
        printNSpace(space / 2);
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            if (temp == NULL)
            {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else
            {
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }
            printNSpace(space);
            count++;
            if (count == maxNode)
            {
                cout << endl;
                count = 0;
                maxNode *= 2;
                level++;
                space /= 2;
                printNSpace(space / 2);
            }
            if (level == height)
                return;
        }
    }

void rotR(Node *&p) {
    Node *temp = p->pLeft;
    p->pLeft = temp->pRight;
    temp->pRight = p;
    p = temp;
}
void rotL(Node *&p) {
    Node *temp = p->pRight;
    p->pRight= temp->pLeft;
    temp->pLeft = p;
    p = temp;
}
bool balanceLeft(Node *&p){
        if (p->balance == EH) {p->balance = LH; return true;}
        else if (p->balance == RH) {p->balance = EH; return false;}
        if (p->pLeft->balance == EH) {
            rotR(p); p->balance = RH; p->pRight->balance = LH; return true;
        }
        else if (p->pLeft->balance == LH) {
            rotR(p); p->balance = EH; p->pRight->balance = EH; return false;
        }
        else {
            rotL(p->pLeft); rotR(p);
            if (p->balance == EH) {p->pLeft->balance = p->pRight->balance = EH;}
            else if (p->balance == RH) {p->pLeft->balance = LH; p->pRight->balance = EH;}
            else {p->pLeft->balance = EH; p->pRight->balance = RH;}
            p->balance = EH;
            return false;
        }
}
bool balanceRight(Node *&p){
        if (p->balance == EH) {p->balance = RH; return true;}
        else if (p->balance == LH) {p->balance = EH; return false;}
        if (p->pRight->balance == EH) {
            rotL(p); p->balance = LH; p->pLeft->balance = RH; return true;
        }
        else if (p->pRight->balance == RH) {
            rotL(p); p->balance = EH; p->pLeft->balance = EH; return false;
        }
        else {
            rotR(p->pRight); rotL(p);
            if (p->balance == EH) {p->pLeft->balance = p->pRight->balance = EH;}
            else if (p->balance == RH) {p->pLeft->balance = LH; p->pRight->balance = EH;}
            else {p->pLeft->balance = EH; p->pRight->balance = RH;}
            p->balance = EH;
            return false;
        }
}
bool Insert(const T &value, Node *&p){
    if (p) {
        if (value < p->data) {
            if (Insert(value, p->pLeft)) return balanceLeft(p);
        }
        else {
            if (Insert(value, p->pRight)) return balanceRight(p);
        }
        return false;
    }
    else {p = new Node(value); return true;}
}
void insert(const T &value){
    //TODO
    Insert(value, root);
}
bool Remove(Node *&p,const T& val){
    if (!p) return false;
    if (p->data > val) {
        if (Remove(p->pLeft, val)) return !balanceRight(p);
        else return false;
    }    
    else if (p->data < val){
        if (Remove(p->pRight, val)) return !balanceLeft(p);
        else return false;
    }
    if (p->pLeft && p->pRight){
        Node *temp = p->pRight;
        while (temp->pLeft) temp = temp->pLeft;
        p->data = temp->data;
        if (Remove(p->pRight, temp->data)) return !balanceLeft(p);
    }
    else if (p->pLeft){
        Node *temp = p;
        p = p->pLeft;
        delete temp;
        return true;
    }
    else if (p->pRight){
        Node *temp = p;
        p = p->pRight;
        delete temp;
        return true;
    }
    else {delete p; p=NULL; return true;}
    return false;
}
void remove(const T &value){
    //TODO
    Remove(root, value);    
}
void printInorder(Node *node){
    if (node){
        printInorder(node->pLeft);
        cout<<node->data<<" ";
        printInorder(node->pRight);
    }
}
void printInorder(){
    //TODO
    printInorder(root);
}
bool search(const T &val, Node *node){
    if (node->data == val) return true;
    else if (node->data > val) return search(val, node->pLeft);
    else return search(val, node->pRight);
    return false;
}

bool search(const T &value){
    //TODO
    return search(value, root);
    return false;
}

    class Node
    {
    private:
        T data;
        Node *pLeft, *pRight;
        BalanceValue balance;
        friend class AVLTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}
    };
};
int main(){
AVLTree<int> avl;
int arr[] = {10,52,98,32,68,92,40,13,42,63,99,100};
for (int i = 0; i < 12; i++){
avl.insert(arr[i]);
cout<<"Lan "<<i<<":"<<endl;
avl.printTreeStructure();
}
avl.remove(13);
}
