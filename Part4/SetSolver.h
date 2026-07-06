#ifndef SetSolver_h
#define SetSolver_h

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "SetSolverSquareSet.h"

using std::vector;
using std::string;
using std::pair;
//You can add another .h class to help you create a data structure of your choosing.


class SetSolver {
private:
    int sizeBoard = 9;
    vector<vector<SetSolverSquareSet>> board;
    vector<vector<int>> x_used;
    vector<vector<int>> y_used;

    bool contains(const vector<int>& vec, int num) {
        for (int element : vec) {
            if (element == num) return true;
        }
        return false;
    }

    vector<vector<int>> getSubgrid(int row, int col) {
        vector<int> x_subgrid;
        vector<int> y_subgrid;
        bool found_compartment = false;

        for (int j = 0; j < sizeBoard; j++) {
            int num = ReturnValue(row, j);
            if (j == col && num > 0) {
                x_subgrid.push_back(num);
                found_compartment = true;
            }
            else if (num <= 0 && !found_compartment) {
                x_subgrid.clear();
            }
            else if (num <= 0 && found_compartment) {
                break;
            }
            else if (num > 0) {
                x_subgrid.push_back(num);
            }
        }

        found_compartment = false;
        for (int i = 0; i < sizeBoard; i++) {
            int num = ReturnValue(i, col);
            if (i == row && num > 0) {
                y_subgrid.push_back(num);
                found_compartment = true;
            }
            else if (num <= 0 && !found_compartment) {
                y_subgrid.clear();
            }
            else if (num <= 0 && found_compartment) {
                break;
            }
            else if (num > 0) {
                y_subgrid.push_back(num);
            }
        }

        return {x_subgrid, y_subgrid};
    }

    bool isContinuous(const vector<int>& subgrid, int n) {
        int size = subgrid.size();
        if (size == 0) return true;

        int max = 0, min = 1000;
        for (int num : subgrid) {
            if (num != 99 && num > max) {
                max = num;
            }
            if (num != 99 && num < min) {
                min = num;
            }
        }

        int upper_bound = min + size - 1;
        int lower_bound = max - size + 1;
        return lower_bound <= n && n <= upper_bound;
    }

    bool isValidMove(int row, int col, int num) {
        if (contains(x_used[row], num) || contains(y_used[col], num)) {
            return false;
        }

        for (int i = 0; i < sizeBoard; i++) {
            int rowVal = ReturnValue(row, i);
            int colVal = ReturnValue(i, col);
            if (rowVal < 0 && -rowVal == num) return false;
            if (colVal < 0 && -colVal == num) return false;
        }

        vector<vector<int>> subgrids = getSubgrid(row, col);
        return isContinuous(subgrids[0], num) && isContinuous(subgrids[1], num);
    }

    bool solve() {
        pair<int, int> bestCell = {-1, -1};
        int minPossibilities = 10;
        
        for (int i = 0; i < sizeBoard; i++) {
            for (int j = 0; j < sizeBoard; j++) {
                if (ReturnValue(i, j) == 99) {
                    int validMoves = 0;
                    for (int num = 1; num <= 9; num++) {
                        if (isValidMove(i, j, num)) {
                            validMoves++;
                        }
                    }
                    if (validMoves == 0) {
                        return false; 
                    }
                    if (validMoves < minPossibilities) {
                        minPossibilities = validMoves;
                        bestCell = {i, j};
                    }
                }
            }
        }
        
        if (bestCell.first == -1) {
            return true;
        }
        
        int row = bestCell.first;
        int col = bestCell.second;
        
        for (int num = 1; num <= 9; num++) {
            if (isValidMove(row, col, num)) {
                board[row][col].set = {num};
                x_used[row].push_back(num);
                y_used[col].push_back(num);
                
                if (solve()) {
                    return true;
                }
                
                board[row][col].set = {99};
                x_used[row].pop_back();
                y_used[col].pop_back();
            }
        }
        
        return false;
    }

    void printBoard() {
        std::cout << "\nCurrent Board State:\n";
        for(int i = 0; i < sizeBoard; i++) {
            for(int j = 0; j < sizeBoard; j++) {
                int val = ReturnValue(i, j);
                if(val == 99) std::cout << " * ";
                else if(val == 0) std::cout << " 0 ";
                else std::cout << " " << val << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    void printSubgrids(const vector<vector<int>>& subgrids, int row, int col) {
        std::cout << "At position (" << row << "," << col << "):\n";
        std::cout << "Horizontal compartment: ";
        for(int n : subgrids[0]) std::cout << n << " ";
        std::cout << "\nVertical compartment: ";
        for(int n : subgrids[1]) std::cout << n << " ";
        std::cout << "\n";
    }

public:
    void PopulateBoard(vector<string> skeletonBoard);
    int ReturnValue(int row, int col);
    void Solve();
};

void SetSolver::PopulateBoard(vector<string> skeletonBoard) {
    board.clear();
    x_used.clear();
    y_used.clear();
    
    board.resize(sizeBoard, vector<SetSolverSquareSet>(sizeBoard));
    x_used.resize(sizeBoard);
    y_used.resize(sizeBoard);

    for (int row = 0; row < sizeBoard; row++) {
        int col = 0;
        for (size_t strIdx = 0; strIdx < skeletonBoard[row].length() && col < sizeBoard;) {
            char cell = skeletonBoard[row][strIdx];
            
            if (cell == '*') {
                board[row][col].set = {99};
                col++;
                strIdx++;
            }
            else if (cell == '0') {
                board[row][col].set.clear();
                col++;
                strIdx++;
            }
            else if (cell == '-') {
                if (strIdx + 1 < skeletonBoard[row].length()) {
                    int val = skeletonBoard[row][strIdx + 1] - '0';
                    board[row][col].set = {-val};
                    col++;
                    strIdx += 2;
                } else {
                    strIdx++;
                }
            }
            else if (cell >= '1' && cell <= '9') {
                int val = cell - '0';
                board[row][col].set = {val};
                x_used[row].push_back(val);
                y_used[col].push_back(val);
                col++;
                strIdx++;
            }
            else {
                strIdx++;
            }
        }
    }

    for (int row = 0; row < sizeBoard; row++) {
        for (int col = 0; col < sizeBoard; col++) {
            if (!board[row][col].set.empty()) {
                int val = board[row][col].set[0];
                if (val < 0) {
                    x_used[row].push_back(-val);
                    y_used[col].push_back(-val);
                }
            }
        }
    }
}

void SetSolver::Solve() {
    if (solve()) {
        std::cout << "Solution found:\n";
        printBoard();
    } else {
        std::cout << "No solution found.\n";
        printBoard();
    }
}

int SetSolver::ReturnValue(int row, int col) {
    if (board[row][col].set.empty()) return 0;
    return board[row][col].set[0];
}

#endif /* SetSolver_h */