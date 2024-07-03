#include <iostream>
using namespace std;
class Computer {
    private:
        int price;
        string* pName;
    public:
        Computer()=default;
        Computer(int a, string b):price(a), pName(new string(b)){}
        Computer(Computer const &c){
            this->price=c.price;
            this->pName= new string(*(c.pName));
            cout<<"Copy Constructor";
        }
        Computer(Computer &&c)
        {
            this->price=c.price;
            this->pName=c.pName;
            c.pName=nullptr;
            delete c.pName;
            cout<<"Move Constructor";
        }
        void print(){
            cout<<price<<endl;
            cout<<*pName<<endl;
        }
};
int main() {
    Computer c1(10, "Asus");
    c1.print();
    Computer c2=move(c1); //move constructor
    c2.print();
    return 0;

}