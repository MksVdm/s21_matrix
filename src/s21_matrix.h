#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

// matrix comparison states
#define SUCCESS 1
#define FAILURE 0

// accuracy to double values comparison
#define ACCURACY 0.0000001

// matrix states
typedef enum {
    CORRECT_MATRIX = 0,
    INCORRECT_MATRIX = 1,
    IDENTITY_MATRIX = 2,
    ZERO_MATRIX = 3
} matrix_type_t;

// matrix struct
typedef struct matrix_struct {
    double **matrix;
    int rows;
    int columns;
    matrix_type_t matrix_type;
} matrix_t;

// defines
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/**
 * @brief Creates matrix with "rows" rows and "columns" columns which both larger than 0. In case of error
 * returns matrix_t type struct with NULL pointer and matrix_type field as INCORRECT_MATRIX
 * 
 * @param rows int type
 * @param columns int type
 * @return matrix_t 
 */
matrix_t s21_create_matrix(int rows, int columns);

/**
 * @brief Removes matrix
 * 
 * @param a matrix_t type
 */
void s21_remove_matrix(matrix_t *a);

/**
 * @brief Compares matrices and return values defined at the library as SUCCESS or FAILURE
 * 
 * @param a matrix_t pointer type
 * @param b matrix_t pointer type
 * @return int SUCCESS/FAILURE
 */
int s21_eq_matrix(matrix_t *a, matrix_t *b);

/**
 * @brief Summs matrices and return new one matrix_t example
 * 
 * @param a matrix_t pointer type
 * @param b matrix_t pointer type
 * @return matrix_t 
 */
matrix_t s21_sum_matrix(matrix_t *a, matrix_t *b);

/**
 * @brief Substracts matrices and return new one matrix_t example
 * 
 * @param a matrix_t pointer type
 * @param b matrix_t pointer type
 * @return matrix_t 
 */
matrix_t s21_sub_matrix(matrix_t *a, matrix_t *b);

/**
 * @brief Multiplies every matrix element by "number" value
 * 
 * @param a matrix_t pointer type
 * @param number double type
 * @return matrix_t
 */
matrix_t s21_mult_number(matrix_t *a, double number);

/**
 * @brief Multiplies two matrices with sizes m*k and k*m
 * 
 * @param a matrix_t pointer type
 * @param b matrix_t pointer type
 * @return matrix_t
 */
matrix_t s21_mult_matrix(matrix_t *a, matrix_t *b);

/**
 * @brief Transposes matrix
 * 
 * @param a matrix_t pointer type
 * @return matrix_t 
 */
matrix_t s21_transpose(matrix_t *a);

/**
 * @brief Calculates algebraic additions matrix of matrix "a"
 * 
 * @param a matrix_t pointer type
 * @return matrix_t 
 */
matrix_t s21_calc_complements(matrix_t *a);

/**
 * @brief Calculates determinant of matrix "a"
 * 
 * @param a matrix_t pointer type
 * @return double
 */
double s21_determinant(matrix_t *a);

/**
 * @brief Calculates inverse matrix of matrix "a"
 * 
 * @param a matrix_t pointer type
 * @return matrix_t 
 */
matrix_t s21_inverse_matrix(matrix_t *a);

/**
 * @brief Calculates 2-dimentional matrix determinant. Used in s21_determinant() function
 * 
 * @param a matrix_t type
 * @return double 
 */
double calculate_2d_determinant(matrix_t a);

/**
 * @brief Calculates 3-dimentional matrix determinant. Used in s21_determinant() function
 * 
 * @param a matrix_t type
 * @return double 
 */
double calculate_3d_determinant(matrix_t a);

/**
 * @brief Calculates n-dimentional matrix determinant by Gauss method. Used in s21_determinant() function
 * 
 * @param a matrix_t type
 * @return double 
 */
double calculate_Gauss_determinant(matrix_t a);

/**
 * @brief Checks matrices for positive rows and columns, correct matrix type and
 * if any matrix elements exist. Use first argument "a" in case of only one has to be checked and 
 * NULL value for second "b"
 * 
 * @param a matrix_t pointer type
 * @param b matrix_t pointer type
 * @return char 1/0
 */
char base_check_matrices(matrix_t *a, matrix_t *b);

/**
 * @brief Checks and sets correct matrix type according to values defined at
 * the library as IDENTITY_MATRIX, ZERO_MATRIX or CORRECT_MATRIX
 * 
 * @param m matrix_t pointer type
 */
void check_matrix_type(matrix_t *m);

/**
 * @brief Executes addition or substraction operations according to given function "operator" 
 * with correct matrices and return result by "res" pointer
 * 
 * @param operator functions matrix_value_summ() or matrix_value_subb()
 * @param a matrix_t type
 * @param b matrix_t type
 * @param res matrix_t pointer type
 */
void simple_matrix_operations(double operator(double, double), matrix_t a, matrix_t b, matrix_t *res);

/**
 * @brief Calculates new element of matrix while multiplying two others
 * 
 * @param a matrix_t type
 * @param b matrix_t type
 * @param i int type
 * @param j int type
 * @param res double pointer type
 */
void calculate_multiplied_matrix_element(matrix_t a, matrix_t b, int i, int j, double *res);

/**
 * @brief Calculates algebraic additions to the specific matrix element placed in "row" and "col" position
 * 
 * @param a matrix_t type
 * @param row int type
 * @param col int type
 * @return double 
 */
double algebraic_addition(matrix_t a, int row, int col);

/**
 * @brief Sets error to matrix state in case of any error and impossibility carrying operation
 * 
 * @param m 
 */
void matrix_error(matrix_t *m);

/*
    Auxiliary functions used in second and more of nesting level relatively general function
*/
void scan_column_to_find_nonzero_num(matrix_t *a, const int row, const int col, char *zero);
void this_row_plus_that_row(matrix_t *a, const int row_num, const int row_zero);
void process_the_row(matrix_t *a, const int row, int col, char *zero);
void make_matrix_minor(matrix_t a, int row, int col, matrix_t *minor);
void check_matrix_status(matrix_t *a, char *state);
double matrix_value_summ(double a, double b);
double matrix_value_subb(double a, double b);
void copy_matrix(matrix_t a, matrix_t *b);
double multiply_diagonal(matrix_t a);
void print_matrix(matrix_t m);

#endif  // SRC_S21_MATRIX_H_
