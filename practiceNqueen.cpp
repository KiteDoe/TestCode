#include <iostream>
using namespace std;
int cnt = 1;

void display(bool board[][50], int n){
    for(int row = 0; row < n; row++){
        for(int col = 0; col < n; col++){
            if(board[row][col]){
                cout << "Q ";
            }
            else{
                cout << "- ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

int queenB(bool board[][50], int row, int n){
    int count = 0;

    if(row == n){
        display(board, n);
        return 1;
    }

    for(int col = 0; col < n; col++){
        bool safe = true;
        for(int i = 0; i < row; i++){
            
            if(board[i][col]){
                safe = false;
                break;
            }

            int leftCheck = min(row, col);
            for(int i = 1; i <= leftCheck; i++){
                if(board[row-i][col-i]){
                    safe = false;
                    break;
                }
            }

            int rightCheck = min(row, n-col-1);
            for(int i = 1; i <= rightCheck; i++){
                if(board[row-i][col+i]){
                    safe = false;
                    break;
                }
            }
        }
        if(safe){
            board[row][col] = true;
            display(board, n);
            count += queenB(board, row+1, n);
            board[row][col] = false;
        }
    }
    return count;
}

void backTracking(int queens){
    bool board[50][50] = {{false}};
    int noOfPossibilities = queenB(board, 0, queens);
    cout << "No of possibilities: " << noOfPossibilities;
}

void queenBNB(bool board[][50], int row, bool colChecked[], bool leftAttacked[], bool rightAttacked[], int n){

    if(row == n){
        cout << "Final arrangement: " << cnt << endl;
        cnt++;
        display(board, n);
        return;
    }

    for(int col = 0; col < n; col++){
        if(!colChecked[col] && !leftAttacked[row+col] && !rightAttacked[row-col+n-1]){
            board[row][col] = true;
            colChecked[col] = true;
            leftAttacked[row+col] = true;
            rightAttacked[row-col+n-1] = true;
            queenBNB(board, row+1, colChecked, leftAttacked, rightAttacked, n);
            board[row][col] = false;
            colChecked[col] = false;
            leftAttacked[row+col] = false;
            rightAttacked[row-col+n-1] = false;
        }
    }
}


void branchAndBound(int queens){
    bool board[50][50] = {{false}};
    bool colChecked[50] = {false};
    bool leftAttacked[50] = {false};
    bool rightAttacked[50] = {false};
    queenBNB(board, 0, colChecked, leftAttacked, rightAttacked, queens);
}


int main(){
    int queens;
    cout << "Enter number of queens: ";
    cin >> queens;
    // backTracking(queens);
    branchAndBound(queens);
}