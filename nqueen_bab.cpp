// #include<bits/stdc++.h>
// using namespace std;

// // leftRow 
// // . . . . . . Q

// // upperLeftDiagonal
// //  .
// //    .
// //      .
// //        .
// //          .
// //            Q

// // lowerRightDiagonal
// //            Q
// //          .
// //        .
// //      .
// //    .
// //  .

// void branchAndBound(int col, int n, vector<string>& board, vector<bool>& leftRow, vector<bool>& upperLeftDiagonal, vector<bool>& lowerRightDiagonal, vector<vector<string>>& ds) {
//     if(col == n) {
//         ds.push_back(board);
//         return ;
//     }

//     for (int row = 0; row < n; row++)
//     {
//         if(leftRow[row] == 0 and upperLeftDiagonal[(n-1)+(col-row)] == 0 and lowerRightDiagonal[row+col] == 0) {
//             leftRow[row] = 1, upperLeftDiagonal[(n-1)+(col-row)] = 1, lowerRightDiagonal[row+col] = 1;
//             board[row][col] = 'Q';
//             branchAndBound(col+1, n, board, leftRow, upperLeftDiagonal, lowerRightDiagonal, ds);
//             leftRow[row] = 0, upperLeftDiagonal[(n-1)+(col-row)] = 0, lowerRightDiagonal[row+col] = 0;
//             board[row][col] = '.';
//         }
//     }
// }

// int main(){
//     int n = 4;
//     string str(n, '.');
//     vector<string> board(n, str);
//     vector<vector<string>> ans;

//     vector<bool> uld(2*n-1, 0), lrd(2*n-1, 0), lr(n, 0);
//     branchAndBound(0, n, board, lr, uld, lrd, ans);

//     cout << "Total possible Boards are : " << ans.size() << endl;
//     for (int i = 0; i < ans.size(); i++)
//     {
//         cout << "Board " << i+1 << endl;
//         for (int j = 0; j < ans[i].size(); j++)
//         {
//             for (int k = 0; k < ans[i][j].size(); k++)
//             {
//                 cout << ans[i][j][k] << " ";
//             }
//             cout << endl;
//         }
//         cout << endl;
//     }
//     return 0;
// }
#include <iostream>
#include <vector>
using namespace std;

int N;
int totalSolutions = 0;

void printSol(vector<vector<int>> board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool isSafe(int row, int col, vector<bool>& rows, vector<bool>& left_diagonals, vector<bool>& right_diagonals) {
    if (rows[row] || left_diagonals[row + col] || right_diagonals[col - row + N - 1]) {
        return false;
    }
    return true;
}

bool solve(vector<vector<int>>& board, int col, vector<bool>& rows, vector<bool>& left_diagonals, vector<bool>& right_diagonals) {
    if (col >= N) {
        totalSolutions++; 
        cout<<"Dfs"<<endl;// Increment the total number of solutions
        printSol(board);
        return true;
    }

    bool res = false;
    for (int i = 0; i < N; i++) {
        if (isSafe(i, col, rows, left_diagonals, right_diagonals)) {
            rows[i] = true;
            left_diagonals[i + col] = true;
            right_diagonals[col - i + N - 1] = true;
            board[i][col] = 1;

            cout << "Placing queen at (" << i << ", " << col << "):" << endl;
            printSol(board);

            res = solve(board, col + 1, rows, left_diagonals, right_diagonals) || res;

            rows[i] = false;
            left_diagonals[i + col] = false;
            right_diagonals[col - i + N - 1] = false;
            board[i][col] = 0;

            cout << "Backtracking from (" << i << ", " << col << "):" << endl;
            printSol(board);
        }
    }

    return res;
}

int main() {
    cout << "Enter the number of rows for the square board: ";
    cin >> N;

    vector<vector<int>> board(N, vector<int>(N, 0));

    vector<bool> rows(N, false);
    vector<bool> left_diagonals(2 * N - 1, false);
    vector<bool> right_diagonals(2 * N - 1, false);

    bool ans = solve(board, 0, rows, left_diagonals, right_diagonals);

    if (!ans) {
        cout << "Solution does not exist\n";
    } else {
        cout << "Total number of solutions: " << totalSolutions << endl; // Print total number of solutions
    }

    return 0;
}