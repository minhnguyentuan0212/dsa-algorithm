#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

struct CBoard {
    int N;
    int **pD;
    CBoard (int size) : N(size), pD(new int*[N])
    {
        for (int i = 0; i < N; i++) {
            pD[i] = new int[N];
            for (int j = 0; j < N; j++)
                pD[i][j] = 0;
        }
    }
    ~CBoard(){
        if (pD) {
            for (int i = 0; i < N; i++)
                delete[] pD[i];
            delete[] pD;
        }
    }
};
static struct Coordinate {int dx,dy;} d[]={{1,2},{-1,2},{1,-2},{-1,-2},{2,1},{-2,1},{2,-1},{-2,-1}};
bool Move(CBoard* pB, int row, int col, int step) {
    cout << step <<endl;
    if (step == pB->N * pB->N) return true;

    for (int i = 0; i < 8; i++){
        int nRow = row + d[i].dy;
        int nCol = col + d[i].dx;
        if (nRow < 0 || nRow >= pB->N || nCol < 0 || nCol >= pB->N) continue;
        if (pB->pD[nRow][nCol]) continue; 
        pB->pD[nRow][nCol] = pB->pD[row][col] + 1;
        if (Move(pB, nRow, nCol, step + 1)) return true;
        pB->pD[nRow][nCol] = 0;
    }
    return false;
}
bool KnightMove(CBoard* pB, int row, int col) {
    pB->pD[row][col] = 1;
    return Move(pB, row, col, 1);
}
int main() {
    CBoard *c = new CBoard(5);
    KnightMove(c, 0, 0);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
            cout<<setw(2) << c->pD[i][j] << " ";
        cout <<endl;
    }
    return 0;
}