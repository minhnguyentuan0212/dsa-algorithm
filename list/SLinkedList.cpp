#include <iostream>
using namespace std;
struct Node {
    int data;
    Node* next;
    Node(int a):data(a){
        next=nullptr;
    };
  
    };
void printLinkedList (Node* head){
        Node*temp=head;
        while (temp!=NULL){
            cout<<temp->data;
             if (temp->next!=NULL)
            cout<<"->";
            temp=temp->next;     
        }

    }
void InsertHeadNode (Node* &head, int a)
{
    Node *temp=head;
    head=new Node(a);
    head->next=temp;
}
void InsertTailNode (Node* head, int a)
{
    Node *temp=head;
    while (temp->next!=NULL)
    {
        temp=temp->next;
    }
    temp->next=new Node(a);

}
void InsertNode(Node* head, int a, int index){
    Node *previous=head;
    while (index!=1)
    {
       previous=previous->next;
       index--;
    }
    Node*temp=new Node(a);
    temp->next=previous->next;
    previous->next=temp;
    
}
void ReverseLinkedList (Node* &head){
    Node *curNode=head;
    while (curNode!=nullptr && curNode->next!=nullptr)
    {
        Node *nextNode=curNode->next;
        curNode->next=nextNode->next;
        nextNode->next=head;
        head=nextNode;
    }
}
Node* ReverseLinkedList2 (Node* head)
{
    if (head->next==nullptr) return head;
    Node* node=ReverseLinkedList2(head->next);
    Node* temp=node;
    while (node->next!=nullptr)
    {
        node=node->next;
    }
    
    node->next=head;
    head->next=nullptr;
    head=temp;
    return head;
}
int main(){
    Node n1(1);
    Node* head=&n1;
    Node n2(2), n3(3);
    n1.next=&n2;
    n2.next=&n3;
    InsertHeadNode(head, 0);
    InsertHeadNode(head, 1);
    InsertTailNode(head, 1);
    InsertNode(head, 10, 3);
    printLinkedList(head);
    cout<<"\n";
    printLinkedList(ReverseLinkedList2(head));
    // printLinkedList(head);
    // printLinkedList(head);
}