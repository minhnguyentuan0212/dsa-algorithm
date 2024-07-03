#include <iostream>
using namespace std;
template <class T>
class Queue {
public:
    Queue() {}
    virtual ~Queue() {}
    Queue(const Queue<T> &) {}
    Queue(Queue<T> &&) {}

    virtual int size() const = 0;
    virtual bool isEmpty() const = 0;
    virtual void clear() = 0;
    virtual Queue<T>& operator=(const Queue<T> &) = 0;
    virtual Queue<T>& operator=(Queue<T> &&) = 0;

    virtual void enqueue(const T&) = 0;
    virtual void enqueue(T&&) = 0;
    virtual void dequeue() = 0;
    virtual T& first() = 0;
    virtual const T& getFirst() const = 0; 
};

template <class T>
class LiQueue : protected LiList<T>, public Queue<T> {
public:
    LiQueue(): LiList<T>() {}
    ~LiQueue() {}
    LiQueue(const Queue<T> &q): LiList<T>(q) {}
    LiQueue(Queue<T> &&q): LiList<T> (q) {}

    int size() const {
        return LiList<T>::size();
    }
    bool isEmpty() const {
        return LiList<T>::isEmpty();
    }
    void clear() {
        LiList<T>::clear();
    }
    Queue<T>& operator=(const Queue<T> &q) {
        return *this;
    }
    Queue<T>& operator=(Queue<T> &&q) {
        return *this;
    }

    void enqueue(const T& val) {
        LiList<T>::insert(val, LiList<T>::size());
    }
    void enqueue(T&&) {
        LiList<T>::insert(move(val), LiList<T>::size());       
    }
    void dequeue() {
        LiList<T>::remove(0);
    }
    T& first() {
        if(!this->pHead) throw DSA_Exception(-10, "LiQueue->first: empty queue");
        return this->pHead->data;
    }
    const T& getFirst() const {
        if(!this->pHead) throw DSA_Exception(-10, "LiQueue->first: empty queue");
        return this->pHead->data;
    } 
};

template <class T>
class BST {
protected:
    struct Node
    {
        T data;
        Node *pLeft, *pRight;
        Node(const T& val, Node *pL = nullptr, Node *pR = nullptr) : data(val), pLeft(pL), pRight(pL) {}
    };
    size_t nE;
    Node *pRoot;
    void clear(Node *pR){ if(pR) {clear(pR->pLeft); clear(pR->pRight); delete pR;}}
    void insert(const T& val, Node *pR ){
        if (pR){
            if (pR->data > val) insert(val, pR->pLeft);
            else insert(val, pR->pRight);
        }
        else { pR= new Node (val); nE++;}
    }
    void remove(const T& key, Node * &pR){
        if (!pR) return;
        if (pR->data > key) remove(key, pR->pLeft);
        else if (pR->data < key) remove(key, pR->pRight);
        if (pR->pLeft && pR->pRight) {
            Node *p= pR->pRight;
            while (p->pLeft) p=p->pLeft;
            pR->data= p->data;
            remove(p->data, pR->pRight);
        }
        else if (pR->pLeft) {
            Node *p= pR; pR=pR->pLeft;
            delete p;
            nE--;
        }
        else if (pR->pRight){
            Node *p= pR; pR=pR->pRight;
            delete p;
            nE--;
        }
        else {delete pR; pR=nullptr; nE--;}

    }
    T * find(const T & key, Node * pR) {
        if(!pR) return nullptr;
        if(pR->data == key) return &pR->data;
        if(pR->data>key) return find(key, pR->pLeft);
        else return find(key, pR->pRight);
    }    
    void traverseNLR(Node *pR, function<void (T&)> op){
        if (pR) { op(pR->data); traverseNLR(pR->pLeft, op); traverseNLR(pR->pRight, op);}
    }
    void traverseNRL(Node *pR, function<void (T&)> op){
        if (pR) { op(pR->data); traverseNRL(pR->pRight, op); traverseNRL(pR->pLeft, op);}
    }
    void traverseLNR(Node *pR, function<void (T&)> op){
        if (pR) { traverseLNR(pR->pLeft, op); op(pR->data); traverseLNR(pR->pRight, op);}
    }
    void traverseRNL(Node *pR, function<void (T&)> op){
        if (pR) { traverseRNL(pR->pRight, op); op(pR->data); traverseLNR(pR->pLeft, op);}
    }
    void traverseLRN(Node *pR, function<void (T&)> op){
        if (pR) { traverseLRN(pR->pLeft, op); traverseLRN(pR->pRight, op); op(pR->data);}
    }
    void traverseRLN(Node *pR, function<void (T&)> op){
        if (pR) { traverseRLN(pR->pRight); traverseRLN(pR->pLeft); op(pR->data);}
    }
public:
    BST(): pRoot(nullptr), nE(0){}
    virtual ~BST() {clear();}
    void clear() {clear(pRoot); pRoot=nullptr; nE=0;}
    size_t size() const { return nE;}
    void insert(const T& val) {insert(val, pRoot);}
    void remove(const T& key) {remove(key, pRoot);}
    T* find(const T & key) {return find(key,pRoot);}
    T* findIter(const T& key){
        for (Node *p = pRoot; p; ){
            if (p->data == key) return &p->data;
            else (p = p->data > key)? p->pLeft:p->pRight; 
        }
        return nullptr;
    }
    void traverseNLR(function<void (T&)> op) { traverseNLR(pRoot, op); }
    void traverseNRL(function<void (T&)> op) { traverseNRL(pRoot, op); }
    void traverseLNR(function<void (T&)> op) { traverseLNR(pRoot, op); }
    void traverseRNL(function<void (T&)> op) { traverseRNL(pRoot, op); }
    void traverseLRN(function<void (T&)> op) { traverseLRN(pRoot, op); }
    void traverseRLN(function<void (T&)> op) { traverseRLN(pRoot, op); }



    void traverseBF(function<void (T&)> op) {
        if (!pRoot) return;
        LiQueue<Node*> q;
        q.enqueue(pRoot);
        while(!q.isEmpty()){
            Node *p = q.first();
            op(p->data);
            if (p->pLeft) q.enqueue(p->pLeft);
            if (p->pRight) q.enqueue(p->pRight);
            q.dequeue();
        }
    }
};