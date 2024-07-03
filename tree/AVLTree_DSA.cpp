template <class T>
class AVLTree {
protected:
    enum BFactor {EH = 0, RH, LH}
    struct Node
    {
        BFactor b;
        T data;
        Node *pLeft, *pRight;
        Node(const T& val, Node *pL = nullptr, Node *pR = nullptr) : data(val), pLeft(pL), pRight(pL) {}
    };
    size_t nE;
    Node *pRoot;
    void clear(Node *pR){ if(pR) {clear(pR->pLeft); clear(pR->pRight); delete pR;}}
    void rotR(Node* &pR) {
        Node *p = pR->pLeft;
        pR->pLeft = p->pRight;
        p->pRight = pR;
        pR = p;
    }
    void rotL(Node* &pR) {
        Node *p = pR->pRight;
        pR->pRight = p->pLeft;
        p->pLeft = pR;
        pR = p;
    }
    bool balanceLeft(Node *&pR){
                    if (pR->b == EH) {pR->b = LH; return true;}
                    else if (pR->b == RH) { pR->b = EH; return false;}
                    if (pR->pLeft->b == EH){
                        rotR(pR); pR->b = RH; pR->pRight->b = LH; return true;
                    }
                    else if (pR->pLeft->b == LH){
                        rotR(pR); pR->b = pR->pRight->b = EH; return false;
                    }
                    else {
                        rotL(pR->pLeft); rotR(pR);
                        if (pR->b == EH) {pR->pLeft->b = pR->pRight->b = EH;}
                        else if (pR->b == LH) {pR->pLeft->b = EH; pR->pRight->b = RH; }
                        else { pR->pLeft->b = LH; pR->pRight->b = EH;}
                        pR->b = EH;
                        return false;
                    }
    }
    bool balanceRight(Node *&pR){
                    if (pR->b == EH) {pR->b = RH; return true;}
                    else if (pR->b == LH) { pR->b = EH; return false;}
                    if (pR->pRight->b == EH){
                        rotL(pR); pR->b = LH; pR->pRight->b = RH; return true;
                    }
                    else if (pR->pRight->b == RH){
                        rotL(pR); pR->b = pR->pLeft->b = EH; return false;
                    }
                    else {
                        rotR(pR->pRight); rotL(pR);
                        if (pR->b == EH) {pR->pLeft->b = pR->pRight->b = EH;}
                        else if (pR->b == RH) {pR->pRight->b = EH; pR->pLeft->b = LH; }
                        else { pR->pRight->b = RH; pR->pLeft->b = EH;}
                        pR->b = EH;
                        return false;
                    }
    }
    bool insert(const T& val, Node *pR ){
        if (pR){
            if (pR->data > val) {
                if (insert(val, pR->pLeft)){
                    return balanceRight(pR);
                }
            }
            else {
                if (insert(val, pR->pRight)){
                    return balanceLeft(pR);
                }
            }
            return false;
        }
        else { pR= new Node (val); nE++; return true;}
    }
    bool remove(const T& key, Node * &pR){
        if (!pR) return false;
        if (pR->data > key) 
            if (remove(key, pR->pLeft)) return !balanceRight(pR);
            else return false;

        else if (pR->data < key) 
            if (remove(key, pR->pRight)) return !balanceLeft(pR);
            else return false;
        if (pR->pLeft && pR->pRight) {
            Node *p= pR->pRight;
            while (p->pLeft) p=p->pLeft;
            pR->data= p->data;
            if(remove(p->data, pR->pRight) return !balanceLeft(pR);
       }
        else if (pR->pLeft) {
            Node *p= pR; pR=pR->pLeft;
            delete p;
            nE--;
            return true;
        }
        else if (pR->pRight){
            Node *p= pR; pR=pR->pRightl
            delete p;
            nE--;
            return true;
        }
        else {delete pR; pR=nullptr; nE--; return true;}

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
    AVLTree(): pRoot(nullptr), nE(0){}
    virtual ~AVLTree() {clear();}
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

