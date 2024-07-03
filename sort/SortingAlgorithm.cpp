#include <iostream>
#include <stack>
using namespace std;
void insertionSort(int *pD, int N){
    if (N<2) return;
    for (int i=0,j;i<N;i++){
        int temp=pD[i];
        for (j=i-1;j>-1;j--){
            if (pD[j]<=temp) {
                break;}
            else pD[j+1]=pD[j];
        }
        pD[j+1]=temp;
        for (int i=0;i<N;i++) {
            cout<<" "<<pD[i];
        }
        cout<<endl;
    }
}
void selectionSort(int *pD, int N){
    if (N<2) return;
    for (int i=0; i<N;i++){
        int minIdx=i;
        for (int j=i+1;j<N;j++){
            if (pD[j]<pD[minIdx]) minIdx=j; 
        }
        swap (pD[minIdx], pD[i]);
        for (int i=0;i<N;i++) {
            cout<<" "<<pD[i];
        }
        cout<<endl;
    }
}
void bubbleSort (int *pD, int N){
    if (N<2) return;
    for (int i=0;i<N;i++){
        for (int j=0;j<N-i-1;j++){
            if (pD[j]>pD[j+1]) swap(pD[j], pD[j+1]);
            for (int i=0;i<N;i++) {
                cout<<" "<<pD[i];
            }
            cout<<endl;
        }
    }
}
void ShellSort(int *pD, int N, int step){
    if (N<2) return;
    for (int i=step,j;i<N;i+=step){
        int temp=pD[i];
        for (j=i-step;j>-1;j-=step){
            if (pD[j]<=temp) {
                break;}
            else pD[j+step]=pD[j];
        }
        pD[j+step]=temp;
    }
}
void shellSort(int *pD, int N){
    stack<int> st;
    int step=1;
    st.push(1);
    while (step<N){
        step=step*3+1;
        if (step<N) st.push(step);
    }
    while (!st.empty())
    {
        step=st.top();
        st.pop();
        for (int i=0; i<step;i++) ShellSort(pD, N - 1, step);
        for (int i=0;i<N;i++) {
                cout<<" "<<pD[i];
            }
        cout<<endl;
    }
    
}
void mergeSort(int *pD, int N){
    if (N<2) return;
    int N2=N/2;
    mergeSort (pD, N2);
    mergeSort (pD+N2, N-N2);

    int *pintemp= new int[N2];
    for (int i=0;i<N2;i++) pintemp[i]=pD[i];
    int *pintarget=pD, *pL=pintemp, *   pLE=pintemp+N2, *pR=pD+N2, *pRE=pD+N;
    while (pL!=pLE && pR!=pRE)
    {
        if (*pL>*pR) *pintarget++=*pR++;
        else *pintarget++=*pL++;
    }
    while (pL!=pLE) *pintarget++=*pL++;
    while (pR!=pRE) *pintarget++=*pR++;
    for (int i=0;i<N;i++){
        cout<<pD[i]<<" ";
    }
    cout<<endl;
    delete[] pintemp;
}

void quickSort(int *pD, int N){
    if (N<2) return;
    int *pL=pD, *pR=pD+N-1, *pPivot=pD+N/2;
    while (pL<pR)
    {
        while (*pPivot>*pL) pL++;
        while (*pPivot<=*pR) pR--;
        if (pL<pR) {
            if (pL==pPivot) pPivot=pR;
            else if (pR==pPivot) pPivot=pL;
            swap(*pL, *pR);
        }   
        else break;     
        pL++;
        pR--;
    }
    if (pPivot!=pL ){
        swap (*pL, *pPivot);
    }
    quickSort(pD, pL-pD);
    quickSort(pL+1, pD+N-pL-1);
}
int main(){
    int N=10;
    int *a= new int[N];
    for (int i=0;i<N;i++){
        a[i]=(rand()%100);
    }
    cout<<"Merge Sort:";
    for (int i=0;i<N;i++) {
            cout<<" "<<a[i];
    }
    cout<<endl;
    // insertionSort(a, N);
    //selectionSort(a, N);
    quickSort(a, N);
    for (int i=0;i<N;i++){
        cout<<a[i]<<" ";
    }
}
