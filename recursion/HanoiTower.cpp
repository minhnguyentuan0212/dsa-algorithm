#include <iostream>
using namespace std;
void move(int n, char source, char destination, char auxiliary){
    static int step=0;
    if (n==1) cout<<"Step "<<++step<<" : Move from "<<source<<" to "<<destination<<endl;
    else {
        move (n-1, source, auxiliary, destination);
        move (1, source, destination, auxiliary);
        move (n-1, auxiliary, destination, source);
    }
}
int main(){
int numDisks ;
cout<<"Enter numbers:" ;
cin>>numDisks ;
cout<<"Start Tower of HN:"<<endl;
move (numDisks,'A','B','C') ;
return 0;
}
