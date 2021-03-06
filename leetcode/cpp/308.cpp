/*
 * Binary Indexed Tree (BIT)
 *
 */
class NumMatrix {
public:
    NumMatrix(vector<vector<int>> matrix) {
        if (matrix.empty() || matrix[0].empty()) return;
        mat.resize(matrix.size() + 1, vector<int>(matrix[0].size() + 1, 0));
        bit.resize(matrix.size() + 1, vector<int>(matrix[0].size() + 1, 0));
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[i].size(); ++j) {
                update(i, j, matrix[i][j]);
            }
        }        
    }
    
    void update(int row, int col, int val) {
        int diff = val - mat[row + 1][col + 1];
        for (int i = row + 1; i < mat.size(); i += i&-i) {
            for (int j = col + 1; j < mat[i].size(); j += j&-j) {
                bit[i][j] += diff;
            }
        }
        mat[row + 1][col + 1] = val;        
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return getSum(row2 + 1, col2 + 1) 
               - getSum(row1, col2 + 1) 
               - getSum(row2 + 1, col1) 
               + getSum(row1, col1);        
    }
    
    int getSum(int row, int col) {
        int res = 0;
        for (int i = row; i > 0; i -= i&-i) {
            for (int j = col; j > 0; j -= j&-j) {
                res += bit[i][j];
            }
        }
        return res;
    } 
    
private:
    vector<vector<int>> mat;
    vector<vector<int>> bit;
};

// Conclusion:



/*
 * Segment Tree
 *
 */
class NumMatrix {
public:
    NumMatrix(vector<vector<int>> matrix) {
        N = matrix.size();
        if (N == 0) return;
        M = matrix.at(0).size();
        if (M == 0) return;
        buildTree(matrix);
    }
    
    void update(int row, int col, int val) {
        row += N;
        col += M;
        tree[row][col] = val;
        int r, c;
        // by row
        r = row;
        c = col / 2;
        while (c > 0) {
            tree[r][c] = tree[r][2 * c] + tree[r][2 * c + 1];
            c /= 2;
        }
        // by col
        c = col;
        r = row / 2;
        while (r > 0) {
            tree[r][c] = tree[2 * r][c] + tree[2 * r + 1][c];
            r /= 2;
        }
        // upper left matrix
        r = row / 2;
        while (r > 0) {
            c = col / 2;
            while (c > 0) {
                tree[r][c] = tree[r][2 * c] + tree[r][2 * c + 1];
                c /= 2;
            }
            r /= 2;
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        int sum = 0;
        row1 += N;
        row2 += N;
        col1 += M;
        col2 += M;
        while (row1 <= row2) {
            if (row1 % 2 == 1) {
                // add this dangling row
                sum += sumRow(row1, col1, col2);
                ++row1;
            }
            if (row2 % 2 == 0) {
                // add this dangling row
                sum += sumRow(row2, col1, col2);
                --row2;
            }
            row1 /= 2;
            row2 /= 2;
        }
        return sum;
    }

private:
    int N, M;
    vector<vector<int>> tree;

    void buildTree(vector<vector<int>> &matrix) {
        tree = vector<vector<int>>(2 * N, vector<int>(2 * M, 0));
        // all leaf node
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                tree[N + i][M + j] = matrix[i][j];
            }
        }
        // finish row
        for (int i = N - 1; i > 0; --i) {
            for (int j = 0; j < M; ++j) {
                tree[i][M + j] = tree[2 * i][M + j] + tree[2 * i + 1][M + j];
            }
        }
        // finish col
        for (int i = 0; i < N; ++i) {
            for (int j = M - 1; j > 0; --j) {
                tree[N + i][j] = tree[N + i][2 * j] + tree[N + i][2 * j + 1];
            }
        }
        // finish 2D
        for (int i = N - 1; i > 0; --i) {
            for (int j = M - 1; j > 0; --j) {
                tree[i][j] = tree[i][2 * j] + tree[i][2 * j + 1];
            }
        }
    }

    int sumRow(int row, int col1, int col2) {
        int sum = 0;
        while (col1 <= col2) {
            if (col1 % 2 == 1) {
                sum += tree[row][col1];
                ++col1;
            }
            if (col2 % 2 == 0) {
                sum += tree[row][col2];
                --col2;
            }
            col1 /= 2;
            col2 /= 2;
        }
        return sum;
    }
};

// Conclusion:

// Reference:
// https://leetcode.com/problems/range-sum-query-2d-mutable/discuss/135478/90ms-C++-2D-segment-tree-(array-representation)-solution




