#include <iostream>
#include <vector>

using namespace std;

bool isSafe(int row, int col, vector<vector<int>>& board) {
    int N = board.size();

    // Check row on left side
    for (int i = 0; i < col; i++) {
        if (board[row][i] == 1) {
            return false;
        }
    }
    // Check upper diagonal on left side
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) {
            return false;
        }
    }
    // Check lower diagonal on left side
    for (int i = row, j = col; i < N && j >= 0; i++, j--) {
        if (board[i][j] == 1)
            return false;
    }

    return true;
}

bool solveNQueens(vector<vector<int>>& board, int col) {
    int N = board.size();
    if (col == N) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
            cout << board[i][j] << " ";
            }
            cout << endl;
        }
        return true;
    }

    // Consider this column and try placing this queen in all rows one by one
    for (int i = 0; i < N; i++) {
        if (isSafe(i, col, board)) {
            board[i][col] = 1;
            // cout<<"safe "<<i<<" "<<col<<"\n";
                // for(auto i : board)
                // {
                //     for(auto it : i)
                //     {
                //         cout<<it<<" ";
                //     }
                //     cout<<endl;
                // }
                cout<<"\n"<<endl;
            // recur to place rest of the queens
            if (solveNQueens(board, col + 1))
            {
                return true;
            }
            // If placing queen in board[i][col] doesn't lead to a solution, then remove queen from board[i][col]
            board[i][col] = 0; // BACKTRACK
        }
        // else cout<<"not safe"<<i<<" "<<col<<endl;
    }
    // cout<<"Backtrack\n";
    // If the queen cannot be placed in any row in this column col then return false
    return false;
}

int main() {
    int N;
    cout << "Enter the number of queens: ";
    cin >> N;

    vector<vector<int>> board(N, vector<int>(N, 0));

    if (!solveNQueens(board, 0)) {
        cout << "Solution does not exist";
        return false;
    }

    return 0;
}