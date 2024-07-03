#include <iostream>
#include <iomanip>
using namespace std;

template <class T>
struct fwIteratorBase{//Iterator

public:
        fwIteratorBase(){}
        virtual ~fwIteratorBase(){}
        // virtual fwIteratorBase& operator=(const fwIteratorBase &i){return (*this);}
        // virtual fwIteratorBase& operator=(fwIteratorBase &&i){return (*this);}
        virtual fwIteratorBase<T> *clone(){return new fwIteratorBase(*this);}
        virtual void operator+(unsigned int di){}
        virtual void operator++(){} //prefix
        virtual void operator++(int){} //postfix
        virtual T& operator*(){throw DSA_Exception(-100, "fwIteratorBase: operator* - Unused Method")}

        virtual bool operator==(const fwIteratorBase &i){return typeid(*this) == typeid(i) && equal(i);}
        virtual bool operator!=(const fwIteratorBase &i){return !(*this)==i;}
protected:
        virtual bool equal(const fwIteratorBase<T> &i) {return true;}
    };

template <class T>
struct fwIterator{//Iterator
protected:
    fwIteratorBase<T> *ptr;
public:
        fwIterator():ptr(nullptr){}
        fwIterator(const fwIterator &i):ptr (i.clone()){}
        fwIterator(fwIterator &&i): ptr(i.ptr){i.ptr=nullptr;}

        ~fwIterator(){ if (ptr) delete ptr;}
        fwIterator& operator=(const fwIterator &i){
            if (ptr) delete ptr;
            ptr=i.ptr->clone();
            return (*this);}
        fwIterator& operator=(fwIterator &&i){
            ptr=i.ptr;
            i.ptr=nullptr;
            return (*this);}

        fwIterator operator+(unsigned int di){
            fwIteratorBase<T> fi(*this);
            fwIteratorBase<T> *p=(*fi.ptr)+di;
            delete fi.ptr;
            fi.ptr=p;
            return fi;}
        fwIterator operator++(){
            ptr->operator()++:
            return (*this);} //prefix
        fwIterator operator++(int){
            fwIteratorBase<T> fi(*this);
            ptr->operator++();
            return f1;
            return (*this);} //postfix
        T& operator*(){
            if (ptr) return *ptr;
            throw DSA_Exception(-100, "fwIterator: operator* - Unused Method")}

        bool operator==(const fwIterator &i){return *ptr==*i.ptr;}
        bool operator!=(const fwIterator &i){return !((*this)==1);}
    };

class DSA_Exception {
protected:
    int errCode;
    string msg;
public:
    DSA_Exception(int err, const string &m) :errCode(err),msg(m){}
    int getErrorCode(){return errCode;}
    string& GetMsg(){return msg;}
};

// List Interface
template <class T>
class List {
public:
    List(){} //default constructor
    List(const List<T> &){} //copy constructor
    List(List<T> &&){} //move constructor
    virtual ~List()=0; //destructor

    virtual fwIterator<T> begin()=0;
    virtual fwIterator<T> end()=0;

    virtual int size()=0; //get size
    virtual bool isEmpty()=0; //check Empty
    virtual void clear()=0; //clear list
    virtual List<T>&operator=(const List<T>&)=0; 
    virtual List<T>&operator=(List<T>&&)=0;
    virtual void reserve()=0;
    virtual void append(List<T>&)=0;
    virtual List<T>* operator+ (const List<T> &)=0;
    virtual List<T>* split(int)=0; //create new list from index, and trim the current list

    virtual void insert(const T&, int)=0;
    virtual void insert(T&&, int)=0;
    virtual void remove(int)=0;
    virtual T* find(const T&)=0;
    virtual T* find(const T& a, bool eq(T&, T& ))=0;
    virtual T* findAll(const T& , List<T*>*)=0;
    virtual T* findAll(const T& , bool eq(T&, T& ), List<T*>*)=0;
    virtual T& operator[](int)=0;
    virtual const T& at(int) = 0;
    virtual void traverse(void (*op)(T&))=0;
    virtual void traverse(void (*op)(T&&))=0;
    virtual void swap(int, int)=0;
    virtual void resize (int)=0;
};

//Array Implementation of list
#define DENSE_BLOCK_SIZE 8
template <class T>
class DenseList: public List<T> {
protected:
    T* pD;
    int cap, nE;

public:
// ITERATOR FOR DENSELIST
template <class T>
struct fwIterator: public fwIteratorBase//Iterator
{
protected:
    T *pD;
public:
        fwIterator(){}
        fwIterator(T *ptr):pD(ptr){}
        ~fwIterator(){}
       // virtual ~fwIteratorBase(){}
        // virtual fwIteratorBase& operator=(const fwIteratorBase &i){return (*this);}
        // virtual fwIteratorBase& operator=(fwIteratorBase &&i){return (*this);}
        fwIteratorBase<T> *clone(){ return new fwIterator(pD); }
        void operator+(unsigned int di){pD+=di;} 
        void operator++(){pD++;} //prefix
        void operator++(int){pD++;} //postfix
        T& operator*(){
            if (pD) return *pD;
            throw DSA_Exception(-100, "fwIteratorBase: operator* - Unused Method")}
        bool operator==(const fwIteratorBase &i){return typeid(*this) == typeid(i) && equal(i);}
        bool operator!=(const fwIteratorBase &i){return !(*this)==i;}
protected:
        bool equal(const fwIteratorBase<T> &i) {return pD==&(*i);}
    };
//ITERATOR END

    DenseList():pD(nullptr), cap(0), nE(0){}
    DenseList(const List<T>& inL):nE(inL.size()){//copy constructor
        cap=(nE+DENSE_BLOCK_SIZE-1)/DENSE_BLOCK_SIZE*DENSE_BLOCK_SIZE;
        pD=new T[cap];
        for (int i=0;i<nE;i++) pD[i]=inL[i];
    }
    DenseList(List<T>&& inL):nE(inL.size()){//move constructor
        cap=(nE+DENSE_BLOCK_SIZE-1)/DENSE_BLOCK_SIZE*DENSE_BLOCK_SIZE;
        pD=new T[cap];
        for (int i=0;i<nE;i++) pD[i]=move(inL[i]);
        inL.clear();
    }
    ~DenseList(){
        if (pD) delete[] pD;
    }
    int size(){return nE;}
    bool isEmpty(){return !nE;}
    void clear(){
        if (pD) delete[] pD;
        nE=0;
        cap=0;
    }
    List<T>& operator=(const List<T>& inL){ //List<T> a=b;
        clear();
        cap=(inL.size()+DENSE_BLOCK_SIZE-1)/DENSE_BLOCK_SIZE*DENSE_BLOCK_SIZE;
        pD=new T[cap];
        nE=inL.size();
        for (int i=0;i<nE;i++) pD[i]=inL.at(i);
        return *this;
    }
    List<T>& operator=(List<T>&& inL){
        clear();
        cap=(inL.size()+DENSE_BLOCK_SIZE-1)/DENSE_BLOCK_SIZE*DENSE_BLOCK_SIZE;
        pD=new T[cap];
        nE=inL.size();
        for (int i=0;i<nE;i++) pD[i]=move(inL[i]);
        inL.clear();
        return *this;
    }
    void reserve(){
        for (int i=nE/2;i>-1;i--) swap(i, nE-1-i);
    }
    void append(List<T>& inL){
        for (int i=0;i<inL.size();i++){
            this->insert(inL[i], nE);
        }
    }
    List<T>* operator+ (const List<T>& inL){
        List<T>* pNewL= new DenseList<T>(*this);
        for (int i=0;i<inL.size();i++){
            pNewL->insert(inL.at(i), pNewL->size());
        }
        return pNewL;
    }
    List<T>* split(int idx){
        List<T>* pNewL= new DenseList<T>;
        for (int i=idx;i<nE;i++){
            pNewL->insert(move(pD[i]), pNewL->size());
        }
        // pD=idx;
        return pNewL;
    } //create new list from index, and trim the current list

    void insert(const T& a, int idx){
        if (idx<0) idx=0;
        if (idx>nE) idx=nE;
        resize(nE+1);
        for (int i=nE;i>idx;i--) pD[i]=move(pD[i-1]);
        pD[idx]=a;
        nE++;
    }
    void insert(T&& a, int idx){
        if (idx<0) idx=0;
        if (idx>nE) idx=nE;
        resize(nE+1);
        for (int i=nE;i>idx;i--) pD[i]=move(pD[i-1]);
        pD[idx]=move(a);
        nE++;
    }
    void remove(int idx){
        if (idx<0 || idx>=nE || !nE) return;
        nE--;
        for (int i=idx;i<nE;i++) pD[i]=move(pD[i+1]);

    }
    T* find(const T& a){
        for (T *p=pD, *pE=pD+nE;p!=pE;p++){
            if (*p==a) return p;

        }
        return nullptr;
    }
    T* find(const T& a, bool eq(T&, T& )){ //Expanded
        for (T *p=pD, *pE=pD+nE;p!=pE;p++){
            if (eq(*p,a)) return p;

        }
        return nullptr;
    }
    T* findAll(const T& a, List<T*> *pRetL){
        for (T *p=pD, *pE=pD+nE;p!=pE;p++){
            if (*p==a) pRetL->insert(p, pRetL->size()); 
        }
        return nullptr;
    }
    T* findAll(const T& a, bool eq(T&, T& ), List<T*> *pRetL){ //Expanded
        for (T *p=pD, *pE=pD+nE;p!=pE;p++){
            if (eq(*p,a)) pRetL->insert(p, pRetL->size());
        }
        return nullptr;
    }
    T& operator[](int idx){
         if (idx<0 || idx>=nE || !nE) {
            throw new DSA_Exception(-100, "Invalid index");
         }
         return pD[idx];
    }
    const T& at(int idx){
		if (idx < 0 || idx >= nE || !nE) {
			throw new DSA_Exception(-100, "Invalid index");
		}
		return pD[idx];
	}
    void traverse(void (*op)(T&)){
        for (T *p=pD, *pE=pD+nE; p!=pE;) op(*p++);
    }
    void traverse(void (*op)(T&&)){
        for (T *p=pD, *pE=pD+nE; p!=pE;p++) op(move(*p));
    }
    void swap(int lIdx, int rIdx){
        if (lIdx < 0 || lIdx >= nE || rIdx < 0 || rIdx >= nE || !(rIdx - lIdx)) return;
		T temp = std::move(pD[lIdx]);
		pD[lIdx] = std::move(pD[rIdx]);
		pD[rIdx] = temp;
    }
    void resize(int N){
        cap=(N+DENSE_BLOCK_SIZE-1)/DENSE_BLOCK_SIZE*DENSE_BLOCK_SIZE;
        T *pD1=new T[cap];
        for (int i=0;i<nE && i<cap;i++) pD1[i]=move(pD[i]);
        if (pD) delete[] pD;
        pD=pD1;
        if (N<nE) N=nE;
    }
};

//Singly Linked Implemetation of list
template <class T>
class LList:List<T> {
protected:
    struct Node 
    {
        T data;
        Node *pNext;
        Node (const T &a, Node *pN=nullptr): data(a), pNext(pN){}
        Node (T && a, Node *pN=nullptr): data(move(a)), pNext(pN){}
        Node():pNext(nullptr);

    };
    Node *pHead;
    int nE;
public:
    LList():pHead(nullptr), nE(0){} //default constructor
    LList(const List<T> &aList):pHead(nullptr), nE(aList.size()){
        Node **pp=&pHead;
        aList.traverse([&pp](T &a){
            *pp=new Node(a, *pp);
            pp=&(*pp)->pNext;
        });
    } //copy constructor
    LList(List<T> && aList){
        Node **pp=&pHead;
        aList.traverse([&pp](T &a){
            *pp=new Node(move(a), *pp);
            pp=&(*pp)->pNext;
        });
    } //move constructor
     ~List(){
        while (pHead){
            Node *p=pHead;
            pHead=pHead->pNext;
            delete p;
        }
     }//destructor
    int size() const{// const method: do not modified data, call by const object   
        return nE;
     } //get size 
    bool isEmpty(){return !nE;} //check Empty
    void clear(){
        delete pHead;
        nE=0;
    }
    LList<T>&operator=(const List<T>& aList){
        clear();
        nE=aList.size();
        Node **pp=&pHead;
        aList.traverse([&pp](T &a){
            *pp=new Node(a, *pp);
            pp=&(*pp)->pNext;
        });
        return (*this);
    }
    LList<T>&operator=(List<T>&& a List){
        clear();
        nE=aList.size();
        Node **pp=&pHead;
        aList.traverse([&pp](T &&a){
            *pp=new Node(move(a), *pp);
            pp=&(*pp)->pNext;
        });
        return (*this);
    }
    void reserve(){
        Node *pNL=nullptr;
        while (pHead){
            Node *p=pHead;
            pHead=pHead->next;
            p->pNext=pNL;
            pNL=p;
        }
        pHead=pNL;
    }
    void append(List<T>& aList){
        Node **pp=&pHead;
        int *pNE=&nE;
        while(*pp) pp=&(*pp)->pNext;
        aList.traverse([&pp, &pNE](T&a){*pp=new Node(a);pp=&(*pp)->pNext;(*pNE)++;}
    }
    List<T>* operator+ (const List<T> &){
            List<T> *pNL=new LList<T>(*this)
            for (int i=0;i<inL.size();i++){
            pNewL->insert(inL.at(i), pNewL->size());
        }
        return pNewL;
    }
    List<T>* split(int){
        if (idx<0 || idx>=nE) return nullptr;
        int newNE=nE-idx;
        Node **pp=&pHead;
        while (*pp && idx)
        {
            pp=&(*pp)->pNext;
            idx--;
            nE--;
        }
        List<T> *pNL=new LList<T>;
        pNL->pHead= *pp;
        pNL->nE=newNE;
        *pp=nullptr;
        return pNL;
    } //create new list from index, and trim the current list
    void insert(const T& a, int idx){
        // if (pHead){
        //     if (idx){
        //         Node *pPrev=pHead;
        //         while (idx>1 && pPrev->pNext)
        //         {
        //             pPrev=pPrev->pNext;
        //             idx--;
        //         }
        //         pPrev->pNext= new Node(a, pPrve->pNext);
        //     }
        //     else{
        //         Node *p=new Node(a, pHead);
        //         pHead=p;            
        //     }
        // }
        // else {
        //     pHead= new Node(a);
        // }
        Node **pp= &pHead;
        while (idx && *pp) {
            pp=&(*pp)->pNext;
            idx--;
        }
        *pp=new Node(a, *pp);
        nE++;
    }
    void insert(T&&a, int idx){
         Node **pp= &pHead;
        while (idx && *pp) {
            pp=&(*pp)->pNext;
            idx--;
        }
        *pp=new Node(move(a), *pp);
        nE++;
    }
    void remove(int idx){
        if (idx<0 || idx>=nE) return;
        Node **pp=&pHead;
        while (idx && *pp){
            pp=&(*pp)->pNext;
            idx--;
        }
        if (*pp){
            Node *p=*pp;
            *pp=(*pp)->pNext;
            delete p;
            nE--;
        }
        
    }
    T* find(const T&key){
        Node *p=pHead;
        while (p){
            if (p->data==key) return &(p->data);
            p=p->pNext;
        }
        return nullptr;
    }
    T* find(const T& key, bool eq(const T&,const T& ){
        Node *p=pHead;
        while (p){
            if (eP(p->data,key)) return &(p->data);
            p=p->pNext;
        }
        return nullptr;
    }
    T* findAll(const T& key, List<T*>*pRetL){
        Node *p=pHead;
        while (p){
            if (p->data==key) pRetL->insert(&p->data,pRetL->size());
            p=p->pNext;
        }
        return nullptr;
    }
    T* findAll(const T& key , bool eq(T&, T& ), List<T*>*pRetL){
        Node *p=pHead;
        while (p){
            if (eq(p->data,key)) pRetL->insert(&p->data,pRetL->size());
            p=p->pNext;
        }
        return nullptr;
    }
    T& operator[](int idx){
        if (idx<0 ||idx>=nE) throw DSA_Exception(-1, "LList: Invalid Index");
        Node *p=pHead;
        while(p && idx){
            p=p->pNext;
            idx--;
        }
        return p->data;
    }
    const T& at(int idx) const {
        return this->operator[](idx);
        // if (idx<0 ||idx>=nE) throw DSA_Exception(-1, "LList: Invalid Index");
        // Node *p=pHead;
        // while(p && idx){
        //     p=p->pNext;
        //     idx--;
        // }
        // return p->data;
     }
    void traverse(void (*op)(T&)){
        Node *p=pHead;
        while (p) {
            op(p->data);
            p=p->pNext;
        }
    }
    void traverse(void (*op)(T&&)){
        Node *p=pHead;
        while (p) {
            op(move(p->data));
            p=p->pNext;
        }
    }
    void swapEle(int lIdx, int rIdx){
        if (lIdx < 0 || lIdx >= nE || rIdx < 0 || rIdx >= nE || !(rIdx - lIdx)) return;
		if (lIdx>rIdx) swap(lIdx, rIdx);
        Node *pLeft=pHead, *pRight;
        rIdx-=lIdx;
        while (lIdx) {
            pLeft=pLeft->pNext;
            lIdx--;
        }
        pRight=pLeft;
        while (rIdx){
            pRight=pRight->pNext;
            rIdx--;
        }
        T temp=move(pLeft->data)
		pLeft->data= std::move(pRight->data);
		pRight->data=move(temp);
    }
    //  void resize (int)=0;
};

//Stack Interface
template <class T>
class Stack{
public:
    Stack(){}
    virtual ~class Stack(){}
    Stack (const Stack<T> &){}
    Stack(Stack<T> &&){}

    virtual int size() const=0;
    virtual bool isEmpty() const=0;
    virtual void clear()=0;
    virtual Stack<T> &operator= (const Stack<T> &)=0;
    virtual Stack<T> &operator= (Stack<T> &&)=0;

    virtual void push(const T&)=0;
    virtual void push(T&&)=0;
    virtual void pop()=0;
    virtual T& top()=0;
    virtual const T& getTop() const=0;
};

//Dense Stack Implementation
template <class T>
class DenseStack: public Stack<T>, protected DenseList<T> {
    DenseStack():DenseList<T>(){}
    DenseStack (const Stack<T> & st):DenseList<T>{resize(st.size());}
    DenseStack(Stack<T> && st){}
    ~DenseStack(){}
    int size() const {return DenseList<T>::size();}
    bool isEmpty() const {return DenseList<T>::isEmpty();}
    void clear(){DenseList<T>::clear();}
    Stack<T> &operator= (const Stack<T> &){ }
    Stack<T> &operator= (Stack<T> &&){ }
    void push(const T& val){DenseList<T>::insert(val, DenseList<T>::size())}
    void push(T&&){DenseList<T>::insert(val, DenseList<T>::size())}
    void pop(){if (!DenseList<T>::isEmpty()) DenseList<T>::remove(DenseList<T>::size()-1);}
    T& top(){return DenseList<T>::operator[](DenseList<T>::size()-1)}
    const T& getTop() const {return DenseList<T>::at(DenseList<T>::size()-1);}
    void resize (int N) override {DenseList<T>::resize(N);}
};

//DENSE STACK
template <class T>
class DenseStack: public Stack<T>, protected DenseList<T> {
public:
        T* pS;
public:
    DenseStack():DenseList<T>(){}
    DenseStack (const Stack<T> & st):DenseList<T>{
        resize(st.size());
        DenseStack<T> tempStack;
        tempStack.resize(st.size());
        Stack <T> *pS=(Stack<T>*)&st;
        while (!pS=isEmpty())
        {
            tempStack.push(move(pS->top())
            pS->pop();
        }
        while (!tempStack.isEmpty()){
            push(tempStack, getTop();
            ps->push(move (tempStack, top()))
            teamStack.pop();
        }
    }
    DenseStack(Stack<T> && st){}
    ~DenseStack(){}
    int size() const{ return DenseList<T>::size(); }
    bool isEmpty() const{ return DenseList<T>::isEmpty(); }
    void clear(){ DenseList<T>::clear();} 
    Stack<T> &operator= (const Stack<T> & st){
        clear();
        resize(st.size());
        DenseStack<T> tempStack;
        tempStack.resize(st.size());
        Stack<T> *pS=(Stack<T>*)&st;
        while (!pS->isEmpty())
        {
            tempStack.push(move(pS->top())
            pS->pop();
        }
        while (!tempStack.isEmpty()){
            push(tempStack, getTop());
            pS->push(move (tempStack, top()))
            tempStack.pop();
        }
        return (*this);
    }
    Stack<T> &operator= (Stack<T> && stdout){
        clear();
        resize(st.size());
        DenseStack<T> tempStack;
        tempStack.resi(ze(st.size());
        Stack <T> *pS=(Stack<T>*)&st;
        while (!pS=isEmpty())
        {
            tempStack.push(move(pS->top())
            pS->pop();
        }
        while (!tempStack.isEmpty()){
            push(tempStack, getTop();
            pS->push(move(tempStack, top());
        return (*this);
    }

    void push(const T& val){DenseList<T>::insert(val, DenseList<T>::size());}
    void push(T&&){DenseList<T>::insert(val, DenseList<T>::size());}
    void pop(){if (!DenseList<T>::isEmpty()) DenseList<T>::remove(DenseList<T>::size()-1);}
    T& top(){return DenseList<T>::operator[](DenseList<T>::size()-1);}
    const T& getTop() const{return DenseList<T>::at(DenseList<T>::size()-1);}
    void resize (int N) override {DenseList<T>::resize(N);}
};


//LINKED STACK
template <class T>
class DenseStack
:public Stack<T>, protected DenseList<T> {
    DenseStack():DenseList<T>(){}
    DenseStack (const Stack<T> & st):DenseList<T>{
        resize(st.size());
        DenseStack<T> tempStack;
        tempStack.resize(st.size());
        Stack <T> *pS=(Stack<T>*)&st;
        while (!pS=isEmpty())
        {
            tempStack.push(move(pS->top())
            pS->pop();
        }
        while (!tempStack.isEmpty()){
            push(tempStack, getTop();
            ps->push(move (tempStack, top()))
            teamStack.pop();
        }
    }
    DenseStack(Stack<T> && st){}
    ~DenseStack(){

    }
     int size() const{
        return DenseList<T>::size();
     }
     bool isEmpty() const{
        return DenseList<T>::isEmpty();
     }
     void clear(){
        DenseList<T>::clear();
     } 
     Stack<T> &operator= (const Stack<T> & st){
        clear();
        resize(st.size());
        DenseStack<T> tempStack;
        tempStack.resize(st.size());
        Stack <T> *pS=(Stack<T>*)&st;
        while (!pS=isEmpty())
        {
            tempStack.push(move(pS->top())
            pS->pop();
        }
        while (!tempStack.isEmpty()){
            push(tempStack, getTop();
            ps->push(move (tempStack, top()))
            tempStack.pop();
        }
        return (*this);
     }
     Stack<T> &operator= (Stack<T> && stdout){
        clear();
        resize(st.size());
        DenseStack<T> tempStack;
        tempStack.resi(ze(st.size());
        Stack <T> *pS=(Stack<T>*)&st;
        while (!pS=isEmpty())
        {
            tempStack.push(move(pS->top())
            pS->pop();
        }
        while (!tempStack.isEmpty()){
            push(tempStack, getTop();
            ps->push(move(tempStack, top());
        return (*this);
     }

     void push(const T& val){
        DenseList<T>::insert(val, DenseList<T>::size())
     }
     void push(T&&){
        DenseList<T>::insert(val, DenseList<T>::size())
     }
     void pop(){
        if (!DenseList<T>::isEmpty()) DenseList<T>::remove(DenseList<T>::size()-1);
     }
     T& top(){
        return DenseList<T>::operator[](DenseList<T>::size()-1)
     }
     const T& getTop() const{
        return DenseList<T>::at(DenseList<T>::size()-1);
     }
    void resize (int N) override {DenseList<T>::resize(N);}
};

// Insertion Sort
template <class T>
void insertionSort(T *pD, int N){
    for (int i=1,j;i<N;i++){
        T temp(move(pD[i]));
        for (j=i-1;j>-1;j--)
            if (pD[j]<=temp){
                break;
            }
            else pD[j+1]=move(pD[j]);
        pD[j+1]=move(pD[j]);    
    }
}

//advanced Insertion Sort
template <class T>
void insertionSort(T *pD, int N, function <bool (const T&, const T&)> greaterCmp){
    for (int i=1,j;i<N;i++){
        T temp(move(pD[i]));
        for (j=i-1;j>-1lj--)
            if (pD[j]<=temp){
                break;
            }
            else pD[j+1]=move(pD[j]);
        pD[j+1]=move(pD[j]);    
    }
}

//Shell Sort
template <class T>
void ShellSort(T *pD, int N, int step){
    for (int i=step,j;i<N;i+=step){
        T temp(move(pD[i]));
        for (j=i-step;j>-1;j-=step)
            if (pD[j]<=temp){
                break;
            }
            else pD[j+step]=move(pD[j]);
        pD[j+step]=move(temp);    
    }
}

template <class T>
void shellSort(T *pD, int N){
    LiStack<int> stepStack;
    stepStack.push(1);
    int step=1;
    while (step<n){
        step=step*2+1;
        if (step<N) stepStack.push(step);
    }
    while (!stepStack.isEmpty())
    {
        /* code */
        step=stepStack.top();
        stepStack.pop();
        for (int i=0; i<step;i++) ShellSort(pD+1, N-1, step);
    }
}

//Selection sort
template <class T>
void selectionSort(T *pD, int N){
    if (N<2) return;
    for (int i=0, j;i<N; i++){
        minIdx=1;
        for (int j=i+1;j<N, j++) if (pD[minIdx]>=pD[j]) minIdx=j;
        if (minIdx !=i) {
            T temp(move(pD[i]));
            pD[i]=move(pD(minIdx));
            pd[minIdx]=move(temp);
        }
    }
}
//Advanced Selection Sort
template <class T>
void selectionSort(T *pD, int N){
    if (N<2) return;
    for (int i=0, j;i<8; i++){
        minIdx=1;
        for (int j=i+1;j<N, j++) if (pD[minIdx]->pD[j]) minIdx=j;
        if (minIdx !=i) {
            T temp(move(pD[i]));
            pD[i]=move(pD(minIdx));
            pd[minIdx]=move(temp);
        }
    }
}

//Merge Sort 
template <class T>
void mergeSort(T *pD, int N){
    if (N<2) return;
    int N2 = N / 2;
    mergeSort (pD, N2);
    mergeSort (pD+N2, N-N2);
    //key
    T *pTemp = new T[N2];
    for (int i=0; i<N2; i++) pTemp[i]=move(pD[i]);
    T *pL= pTemp, *pLE= pTemp + N2, *pR=pD+N2, *pRE= pD +N, *pTarget= pD;
    while (pL != pLE && pR != pRE)
    {
        if (*pL > *pR) *pTarget++ = move (*pR++);
        else *pTarget++ = move (*pL++);
    }
    while (pL != pLE) *pTarget++ = move(*pL++);
    while (pR != pRE) *pTarget++ = move(*pR++);
    delete []pTemp;
}

// Quick Sort
template <class T>
void quickSort(T *pD, int N){
    if (N<2) return;
    T *pL=pD, *pR=pD+N-1, *pPivot=pD+N/2;
    while (pL<pR)
    {
        while (*pPivot>*pL) pL++;
        while (*pPivot<=*pR) pR--;
        if (pL<pR) {
            if (pL==pPivot) pPivot=pR;
            else if (pR==pPivot) pPivot=pL;
            T temp(move(*pL));
            *pL=move (*pR);
            *pR=move(temp);
        }   
        else break;     
        pL++;
        pR--;
    }
    if (pPivot!=pL ){
        T temp(move(*pL));
        *pL=move (*pPivot);
        *pPivot=move(temp);
    }
    quickSort(pD, pL-pD);
    quickSort(pL+1, pD+N-pL-1)
}

int main(){
List<int> *pL= new DenseList<int>;
for (int i=0;i<8;i++) pL->insert(rand()%100,i);
pL->traverse([](int &a){cout<<setw(5)<<a;});
cout<<endl;
if (*pL->find(71)) {cout<<"f";}
else cout<<"n";
if (int*p=pL->find(72)){*p=81;}
for (fwIterator<int> i=pL->begin(),e=pL->end();i!=e;i++){
    cout<<setw(9)<<*i;
}

 clock_t bT=clock(), eT;
 shellSort(&(*pL->begin()), pL->size());
 for (int &val :*pL){
    cout<<setW(5)<<val;
 }
}
