#include <bits/stdc++.h>
using namespace std;

#define ROW 8
#define COL 8

struct Cell {
    int parent_i, parent_j;
    int f, g, h;
};

// 8 possible movements (N, S, E, W, NE, NW, SE, SW)
int dx[8] = {-1,  1,  0,  0, -1, -1,  1,  1};
int dy[8] = { 0,  0, -1,  1, -1,  1, -1,  1};

// Chebyshev distance heuristic
int calculateH(int row, int col, pair<int,int> dest) {
    return max(abs(row - dest.first), abs(col - dest.second));
}

bool isValid(int row, int col) {
    return (row >= 0) && (row < ROW) &&
           (col >= 0) && (col < COL);
}

bool isUnBlocked(int grid[ROW][COL], int row, int col) {
    return grid[row][col] == 1;
}

bool isDestination(int row, int col, pair<int,int> dest) {
    return row == dest.first && col == dest.second;
}

void tracePath(Cell cellDetails[ROW][COL], pair<int,int> dest) {
    int row = dest.first, col = dest.second;
    stack<pair<int,int>> path;
    while (!(cellDetails[row][col].parent_i == row &&
             cellDetails[row][col].parent_j == col)) {
        path.push({row, col});
        int pi = cellDetails[row][col].parent_i;
        int pj = cellDetails[row][col].parent_j;
        row = pi; col = pj;
    }
    path.push({row, col});
    cout << "Path:\n";
    while (!path.empty()) {
        auto p = path.top(); path.pop();
        cout << "(" << p.first << "," << p.second << ") ";
    }
    cout << "\n";
}

void aStarSearch(int grid[ROW][COL],
                 pair<int,int> start, pair<int,int> dest) {
    if (!isValid(start.first, start.second) ||
        !isValid(dest.first, dest.second)) {
        cout << "Start or destination is invalid.\n";
        return;
    }
    if (!isUnBlocked(grid, start.first, start.second) ||
        !isUnBlocked(grid, dest.first, dest.second)) {
        cout << "Start or destination is blocked.\n";
        return;
    }
    if (isDestination(start.first, start.second, dest)) {
        cout << "Already at the destination.\n";
        return;
    }

    bool closedList[ROW][COL] = {false};
    Cell cellDetails[ROW][COL];

    // Initialize all cells
    for (int i = 0; i < ROW; ++i)
        for (int j = 0; j < COL; ++j)
            cellDetails[i][j] = {-1, -1, INT_MAX, INT_MAX, INT_MAX};

    // Initialize start cell
    int sx = start.first, sy = start.second;
    cellDetails[sx][sy] = {sx, sy, 0, 0, 0};

    // openList: set of (f, (i,j))
    set<pair<int, pair<int,int>>> openList;
    openList.insert({0, {sx, sy}});

    while (!openList.empty()) {
        auto p = *openList.begin();
        openList.erase(openList.begin());
        int i = p.second.first, j = p.second.second;
        closedList[i][j] = true;

        // If we reached the destination
        if (isDestination(i, j, dest)) {
            tracePath(cellDetails, dest);
            return;
        }

        // Explore all 8 neighbors
        for (int dir = 0; dir < 8; ++dir) {
            int ni = i + dx[dir], nj = j + dy[dir];
            if (isValid(ni, nj) && isUnBlocked(grid, ni, nj) && !closedList[ni][nj]) {
                int gNew = cellDetails[i][j].g + 1;
                int hNew = calculateH(ni, nj, dest);
                int fNew = gNew + hNew;

                // If this path to neighbor is better
                if (cellDetails[ni][nj].f == INT_MAX ||
                    cellDetails[ni][nj].f > fNew) {
                    openList.insert({fNew, {ni, nj}});
                    cellDetails[ni][nj] = {i, j, fNew, gNew, hNew};
                }
            }
        }
    }
    cout << "Failed to find a path to the destination.\n";
}

int main() {
    int grid[8][8] = {
        {1, 1, 0, 1, 1, 0, 1, 1},
        {0, 1, 1, 1, 0, 1, 0, 1},
        {1, 1, 0, 1, 1, 1, 1, 0},
        {1, 0, 1, 0, 1, 0, 1, 1},
        {1, 1, 1, 1, 0, 1, 1, 0},
        {0, 1, 0, 1, 1, 1, 0, 1},
        {1, 1, 1, 0, 1, 0, 1, 1},
        {0, 1, 1, 1, 1, 1, 0, 1}
    };
    

    pair<int,int> start = {0, 0};
    pair<int,int> dest  = {7, 7};


    aStarSearch(grid, start, dest);
    return 0;
}