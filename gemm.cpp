#include <iostream>
#include <chrono>
#include <cstdlib>

// 定义矩阵大小N
#define N 1000

// 定义宏来计算一维数组的索引
#define INDEX(row, col, n) ((row) * (n) + (col))

// 定义矩阵乘法函数
void matrix_multiply(float* A, float* B, float* C) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            float sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[INDEX(i, k, N)] * B[INDEX(k, j, N)];
            }
            C[INDEX(i, j, N)] = sum;
        }
    }
}

void dcu_matrix_multiply(float* A, float* B, float* C) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            float sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[INDEX(i, k, N)] * B[INDEX(k, j, N)];
            }
            C[INDEX(i, j, N)] = sum;
        }
    }
}

int main() {
    // 分配内存并初始化一维数组 A, B, C
    float* A = (float*)malloc(N * N * sizeof(float));
    float* B = (float*)malloc(N * N * sizeof(float));
    float* C = (float*)malloc(N * N * sizeof(float));
    float* C_CPU = (float*)malloc(N * N * sizeof(float));

    for (int i = 0; i < N * N; i++) {
        A[i] = i * 0.123456;
        B[i] = (i + 5) * 0.566756;
        C[i] = 0.0f;
    }

    // 计时开始
    auto start_time = std::chrono::high_resolution_clock::now();

    // 执行矩阵乘法
    dcu_matrix_multiply(A, B, C);

    // 计时结束
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    matrix_multiply(A, B, C_CPU);

    std::cout << "Matrix multiplication took " << duration.count() << " ms." << std::endl;

    // 验证结果
    bool error_found = false;
    int error_row = -1;
    int error_col = -1;

    for (int i = 0; i < N * N; i++) {
        if (C[i] != C_CPU[i]) {
            error_found = true;
            error_row = i / N;
            error_col = i % N;
            std::cout << "Error at position (" << error_row << ", " << error_col << "): ";
            std::cout << "Expected " << C_CPU[i] << ", but got " << C[i] << std::endl;
            break;  // Exit the loop on the first error found
        }
    }

    if (!error_found) {
        std::cout << "Result verified: All elements match." << std::endl;
    } else {
        std::cout << "Verification failed. Exiting program." << std::endl;
    }

    // 释放分配的内存
    free(A);
    free(B);
    free(C);
    free(C_CPU);

    return 0;
}
