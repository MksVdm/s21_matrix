# s21_matrix - simple matrix operations library in C language

### Matrix structure:

```c
typedef enum {
    CORRECT_MATRIX = 0,
    INCORRECT_MATRIX = 1,
    IDENTITY_MATRIX = 2,
    ZERO_MATRIX = 3
} matrix_type_t;

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
    matrix_type_t matrix_type;
} matrix_t;
```  

The matrix_type field defines the matrix type, CORRECT_MATRIX - the correct matrix, INCORRECT_MATRIX - in case of errors in actions with matrices, IDENTITY_MATRIX - a identity matrix, ZERO_MATRIX - a null matrix.
The filling of the matrix in the case of the INCORRECT_MATRIX type is not defined.  

### Matrix operations

1. ```matrix_t s21_create_matrix(int rows, int columns);```
Creates matrix with "rows" rows and "columns" columns which both larger than 0. In case of error returns matrix_t type struct with NULL pointer and matrix_type field as INCORRECT_MATRIX.  

2. ```void s21_remove_matrix(matrix_t *a);```
Removes matrix. matrix_t.matrix will be freed and other fields become equals to zero.  

3. ```int s21_eq_matrix(matrix_t *a, matrix_t *b);```
Compares matrices and returns values defined at the library as SUCCESS or FAILURE.  

4. ```matrix_t s21_sum_matrix(matrix_t *a, matrix_t *b);```
Summs matrices and returns new one matrix_t example.  

5. ```matrix_t s21_sub_matrix(matrix_t *a, matrix_t *b);```
Substracts matrices and returns new one matrix_t example.  

6. ```matrix_t s21_mult_number(matrix_t *a, double number);```
Multiplies every matrix element by "number" value.  

7. ```matrix_t s21_mult_matrix(matrix_t *a, matrix_t *b);```
Multiplies two matrices with sizes m*k and k*m. 

8. ```matrix_t s21_transpose(matrix_t *a);```
Transposes matrix and returns new one matrix_t example.  

9. ```matrix_t s21_calc_complements(matrix_t *a);```
Calculates algebraic additions matrix of matrix "a" and returns new one matrix_t example.  

10. ```double s21_determinant(matrix_t *a);```
Calculates determinant of matrix "a" and returns new one matrix_t example. Determinant calculated by Gauss methos, so it can be usefull and pretty fast to large matrices.  

11. ```matrix_t s21_inverse_matrix(matrix_t *a);```
Calculates inverse matrix of matrix "a" and returns new one matrix_t example.  

Verifiable accuracy of the fractional part is up to 7 decimal places. The library developed in C language of C11 standard using gcc compiler. Static library will be compilled by ```make s21_matrix.a``` command of ```Makefile``` executed in ```src``` folder.  
