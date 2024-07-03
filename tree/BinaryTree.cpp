#include<iostream>
#include<string>
#include<vector>
using namespace std;

template<class K, class V>
class BinaryTree
{
public:
    class Node;

private:
    Node *root;

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    class Node
    {
    private:
        K key;
        V value;
        Node *pLeft, *pRight;
        friend class BinaryTree<K, V>;

    public:
        Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };

    void addNode(string posFromRoot, K key, V value)
    {
        if(posFromRoot == "")
        {
            this->root = new Node(key, value);
            return;
        }

        Node* walker = this->root;
        int l = posFromRoot.length();
        for (int i = 0; i < l-1; i++)
        {
            if (!walker)
                return;
            if (posFromRoot[i] == 'L')
                walker = walker->pLeft;
            if (posFromRoot[i] == 'R')
                walker = walker->pRight;
        }
        if(posFromRoot[l-1] == 'L')
            walker->pLeft = new Node(key, value);
        if(posFromRoot[l-1] == 'R')
            walker->pRight = new Node(key, value);
    }

    // STUDENT ANSWER BEGIN
    //Helping functions

//SUM OF LEAF NODE
int sumOfLeafsNode(Node *p){
    //TODO
    if (p->pLeft && p->pRight) return sumOfLeafsNode(p->pLeft)+sumOfLeafsNode(p->pRight);
    else {
        if (p->pLeft) return sumOfLeafsNode(p->pLeft);
        else if (p->pRight) return sumOfLeafsNode(p->pRight);
        else return p->value;
    }
}
int sumOfLeafs(){
    //TODO
    return sumOfLeafsNode(root);
}

//COUNT_2_CHILDREN_NODE
int countTwoChildrenNodes(Node *root){
    if (root->pLeft && root->pRight) return 1 + countTwoChildrenNodes(root->pLeft) + countTwoChildrenNodes(root->pRight);
    else if (root->pLeft) return countTwoChildrenNodes(root->pLeft);
    else if (root->pRight) return countTwoChildrenNodes(root->pRight);
    else return 0;
}
int countTwoChildrenNode()
{
    return countTwoChildrenNodes(root);
}
//GET HIGH
int GH (Node *p){
    if (p) {
        int LHeight= GH(p->pLeft);
        int RHeight= GH(p->pRight);
        if (LHeight > RHeight) return LHeight+1;
        else return RHeight+1;
    }
    else return 0;
}
int getHeight() {
    // TODO: return height of the binary tree.
    return GH(root);
}

//PRE_ORDER
void PreOrder(Node *root, string &s) {
    if (root) {
        s = s + to_string(root->value) + " ";
        PreOrder(root->pLeft, s);
        PreOrder(root->pRight, s);
    } 
}
string preOrder(){
    string s="";
    PreOrder(root, s);
    return s; 
} 

//IN_ORDER
void InOrder(Node *root, string &s) {
    if (root) {
        InOrder(root->pLeft, s);
        s = s + to_string(root->value) + " ";
        InOrder(root->pRight, s);
    } 
}
string inOrder(){
    string s="";
    InOrder(root, s);
    return s; 
} 

//POST_ORDER
void PostOrder(Node *root, string &s) {
    if (root) {
        PostOrder(root->pLeft, s);
        PostOrder(root->pRight, s);
        s = s + to_string(root->value) + " ";
    } 
}
string postOrder(){
    string s="";
    PostOrder(root, s);
    return s; 
} 

//SUM_DIGIT_PATH_MOD_X
int SDP(Node *node,long long int sum){
    if (node==NULL) return 0;
    sum=(10*sum+node->val);
    sum%=27022001;
    if (node->pLeft==NULL && node->pRight==NULL) return sum%27022001;
    return (SDP(node->pLeft,sum)+SDP(node->pRight, sum))%27022001;
}
int sumDigitPath(Node* root) {
    // 
    return SDP(root, 0)%27022001;
}

//BFS
void BFSS(Node *root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);
        
}
void BFS()
{
   if (!root) return;
        queue<Node*> q;
        q.push(root);
        while(!q.empty()){
            Node *p = q.front();
            cout<<p->value<<" ";
            if (p->pLeft) q.push(p->pLeft);
            if (p->pRight) q.push(p->pRight);
            q.pop();
        }
}

//LONGEST_PATH_SUM 
void LPS(Node* node, int sum, int len, int &maxsum, int &maxlen){
    if (node) {
    LPS(node->pLeft, sum + node->val, len + 1, maxsum, maxlen);
    LPS(node->pRight, sum + node->val, len + 1, maxsum, maxlen);
}
    else {
        if (maxlen < len) {maxlen = len; maxsum = sum;}
        else if (maxlen == len && maxsum < sum) maxsum=sum;
    }
}
int longestPathSum(Node* root) {
    if (!root) return 0;
    int maxlen=0;
    int maxsum=-1000000;
    LPS(root, 0, 0, maxsum, maxlen);
    return maxsum;
}
    
//LOWEST_ANCESTOR
bool findPath(Node* node, vector<int> &vt, int val){
    if (!node) return false;
    vt.push_back(node->value);
    if (node->value==value) return true;
    if (node->pLeft && findPath(node->pLeft, vt, val)) {
        return true;
    }
     if (node->pRight && findPath(node->pRight, vt, val)) {
        return true;
    }
    vt.pop_back();
    return false;
}
int lowestAncestor(Node* root, int a, int b) {
    vector<int> p1, p2;
    int i=0;
    if (findPath(root, p1, a) && findPath(root, p2, b)) {
        while(p1[i]==p2[i]) i++;
    }
    return p1[i-1];
}

    // STUDENT ANSWER END
};


int main(){
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("", 2, 4); // Add to root
    binaryTree.addNode("L", 3, 6); // Add to root's left node
    binaryTree.addNode("R", 5, 9); // Add to root's right node

    cout << binaryTree.getHeight() << endl;
    cout << binaryTree.preOrder() << endl;
}