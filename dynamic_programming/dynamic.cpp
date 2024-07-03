#include <iostream>
using namespace std;
int main()
{
    int xu[3]={1,3,5};
    int minn[13]={0,100,100,100,100,100,100,100,100,100,100,100,100};
    for (int i=1; i<=12;i++)
     for (int j=0;j<=2;j++)
        if (xu[j]<=i && minn[i-xu[j]]+1<minn[i]) 
          minn[i]=minn[i-xu[j]]+1;
    for (int i=0;i<13;i++)
      cout<<minn[i]<<endl;
       
    

}