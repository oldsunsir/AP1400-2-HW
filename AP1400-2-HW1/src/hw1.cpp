#include"hw1.h"

#include<iomanip>
#include<iostream>
#include<random>
#undef minor
using std::cout;
using std::endl;
using std::left;
using std::logic_error;

namespace algebra
{
    Matrix CreateMatrix(size_t n, size_t m, double v){
        if (n <= 0 || m <= 0) 
            throw logic_error("wrong col or row\n");
        Matrix x;
        for (int i = 0; i < n; i++){
            std::vector<double> vect(m, v);
            x.push_back(vect);
        }
        return x;
    }
    Matrix zeros(size_t n, size_t m){
        return CreateMatrix(n, m, 0);
    }
    Matrix ones(size_t n, size_t m){
        return CreateMatrix(n, m, 1);
    }
    Matrix random(size_t n, size_t m, double min, double max){
        if (min > max){
            throw logic_error("min can't be greater than max\n");
        }
        auto x = zeros(n, m);
        //random库如何随机的方法
        std::default_random_engine e;
        std::uniform_real_distribution<double> u(min, max);
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < m; ++j){
                x[i][j] = u(e);
            }
        }
        return x;
    }
    void show(const Matrix& matrix){
        auto m = matrix.size();
        auto n = matrix[0].size();
        for (size_t i = 0; i < m; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                cout << std::left << std::setw(5) << std::setprecision(3) << matrix[i][j];
            }
            cout << endl;
        }   
    }
    Matrix multiply(const Matrix& matrix, double c){
        if (matrix.size() == 0) return matrix;
        auto m = matrix.size();
        auto n = matrix[0].size();
        Matrix x = zeros(m, n);
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                x[i][j] = matrix[i][j] * c;
            }
        }
        return x;
    }
    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2){
        if (matrix1.size() == 0 && matrix2.size() == 0)
            return Matrix{};
        if (matrix1.empty() || matrix2.empty())
            throw logic_error("calucation error!\n");
        if (matrix1[0].size() != matrix2.size())
            throw logic_error("dimension error!\n");
        int m = matrix1.size();
        int n = matrix2[0].size();
        auto x = zeros(m, n);
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                for (int k = 0; k < matrix2.size(); k++)
                    x[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
        return x;
    }
    Matrix sum(const Matrix& matrix, double c){
        if (matrix.empty()) 
            return Matrix{};
        int m = matrix.size();
        int n = matrix[0].size();
        Matrix x = zeros(m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                x[i][j] = matrix[i][j] + c;
            }
        }
        return x;
    }
    Matrix sum(const Matrix& matrix1, const Matrix& matrix2){
        if (matrix1.empty() && matrix2.empty()) 
            return Matrix{};

        if (matrix1.empty() || matrix2.empty()) 
            throw logic_error("calculation error\n");
        if (matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size()) 
            throw logic_error("dimessions error\n");

        auto m{matrix1.size()};
        auto n{matrix1[0].size()};
        auto x{zeros(m, n)};
        for (int i{0}; i < m; i++) {
            for (int j{0}; j < n; j++) {
                x[i][j] = matrix1[i][j] + matrix2[i][j];
            }
        }
        return x;
    }
    Matrix transpose(const Matrix& matrix){
        if (matrix.empty()) return Matrix{};
        int m = matrix[0].size(), n = matrix.size();
        Matrix x{zeros(m, n)};
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                x[i][j] = matrix[j][i];
        return x;
    }
    Matrix minor(const Matrix& matrix, size_t n, size_t m){
        if (n < 0 || n >= matrix.size() || m < 0 || m >= matrix[0].size())
            throw logic_error("out of bound\n");
        Matrix x;
        for (int i = 0; i < matrix.size(); i++){
            if (i == n) continue;
            std::vector<double>y;
            for (int j = 0; j < matrix[0].size(); j++){
                if (j == m) continue;
                y.push_back(matrix[i][j]);
            }
            x.push_back(y);
        }
        return x;
    }
    double determinant(const Matrix& matrix){
        if (matrix.empty())
            return 1;
        if (matrix.size() != matrix[0].size())
            throw logic_error("Not Square!\n");
        if (matrix.size() == 1) 
            return matrix[0][0];
        else if (matrix.size() == 2)
            return matrix[0][0] * matrix[1][1] - matrix[0][1]*matrix[1][0];
        else{
            double res = 0;
            for (size_t i = 0; i < matrix.size(); i++)
                res += matrix[i][0]*pow(-1, i)*determinant(minor(matrix, i, 0));
            return res;
        } 
    }
    Matrix inverse(const Matrix& matrix){
        if (matrix.empty())
            return Matrix{};
        if (matrix.size() != matrix[0].size() || determinant(matrix) == 0)
            throw logic_error("No inverse!\n");
        Matrix x = zeros(matrix.size(), matrix[0].size());
        for (size_t i = 0; i < matrix.size(); i++)
        {
            for (size_t j = 0; j < matrix[0].size(); j++)
            {
                x[i][j] = determinant(minor(matrix, i, j))*pow(-1, i+j);
            }
        }
        x = transpose(x);
        return multiply(x, 1.0 / determinant(matrix));
    }
    Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis){
        if (axis == 0) {
            if (matrix1[0].size() != matrix2[0].size()) {
                throw logic_error("unequal number of columns\n");
            }
            Matrix x;
            for (int i = 0; i < matrix1.size(); i++) {
                x.push_back(matrix1[i]);
            }
            for (int j = 0; j < matrix2.size(); j++) {
                x.push_back(matrix2[j]);
            }

            return x;
    }

        if (matrix1.size() != matrix2.size()) {
            throw logic_error("unequal number of rows\n");
        }

        Matrix x = zeros(matrix1.size(), matrix1[0].size() + matrix2[0].size());

        for (int i = 0; i < x.size(); i++) {
            for (int j = 0; j < x[0].size(); j++) {
                if (j < matrix1[0].size()) {
                    x[i][j] = matrix1[i][j];
                } else {
                    x[i][j] = matrix2[i][j - matrix1[0].size()];
                }
            }
        }
        return x;
    }
    Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2){
        Matrix x;
        auto len = matrix.size();
        if (r1 < 0 || r1 >= len || r2 < 0 || r2 >= len)
            throw logic_error("out of bound\n");
        for (size_t i = 0; i < matrix.size(); i++)
        {
            if (i == r1)
                x.push_back(matrix[r2]);
            else if (i == r2)
                x.push_back(matrix[r1]);
            else
                x.push_back(matrix[i]);
        }
        return x;
    }
    Matrix ero_multiply(const Matrix& matrix, size_t r, double c) {
        auto m{matrix.size()};
        auto n{matrix[0].size()};
        Matrix x = zeros(m, n);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == r) {
                    x[r][j] = matrix[r][j] * c;
                    continue;
                }
                x[i][j] = matrix[i][j];
            }
        }

        return x;
    }
    Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2) {
        Matrix x = ero_multiply(matrix, r1, 1);
        for (int i = 0; i < matrix[r2].size(); i++) {
            x[r2][i] += (x[r1][i] * c);
        }
        return x;
    }
    void mul_sum(Matrix& matrix, size_t r1, double c, size_t r2) {
        for (int i = 0; i < matrix[r2].size(); i++) {
            matrix[r2][i] += (matrix[r1][i] * c);
        }
    }

    Matrix upper_triangular(const Matrix& matrix) {
        if (matrix.empty()) {
            return Matrix{};
        }
        if (matrix.size() != matrix[0].size()) {
            throw logic_error("not a square matrix\n");
        }
        Matrix x = ero_multiply(matrix, 0, 1);
        if (x[0][0] == 0) {
            int row = 1;
            while (x[row][0] == 0 && row < x.size()) {
                row++;
            }
            if (row == x.size()) {
                throw logic_error("impossible");
            }
            x = ero_swap(x, 0, row);
        }

        auto m{matrix.size()};

        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < m; j++) {
                mul_sum(x, i, (-x[j][i] / x[i][i]), j);
            }
        }
        return x;
    }
} // namespace algebra

