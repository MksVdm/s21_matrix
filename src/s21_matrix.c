#include "s21_matrix.h"

matrix_t s21_create_matrix(int rows, int columns) {
    char memory_given = 1;
    matrix_t matrix;

    matrix.matrix_type = INCORRECT_MATRIX;
    if (rows > 0 && columns > 0) {
        matrix.rows = rows;
        matrix.columns = columns;
        matrix.matrix = (double **)calloc(matrix.rows, sizeof(double *));
        if (matrix.matrix) {
            for (rows--; rows >= 0 && memory_given; rows--) {
                matrix.matrix[rows] = (double *)calloc(matrix.columns, sizeof(double));
                if (!matrix.matrix[rows]) memory_given = 0;
            }
        } else {
            memory_given = 0;
        }
        if (memory_given) matrix.matrix_type = ZERO_MATRIX;
    } else {
        matrix_error(&matrix);
    }

    return matrix;
}

void s21_remove_matrix(matrix_t *a) {
    if (a && a->matrix) {
        for (a->rows--; a->rows >= 0; a->rows--) {
            if (a->matrix[a->rows]) {
                free(a->matrix[a->rows]);
                a->matrix[a->rows] = NULL;
            }
        }
        free(a->matrix);
        a->matrix = NULL;
        a->matrix_type = 0;
        a->columns = 0;
        a->rows = 0;
    }
}

int s21_eq_matrix(matrix_t *a, matrix_t *b) {
    char state = 0;
    int equal = SUCCESS;

    state = base_check_matrices(a, b);
    if (a && b && state && a->columns == b->columns && a->rows == b->rows) {
        for (int i = 0; equal && i < a->rows; i++) {
            for (int j = 0; equal && j < a->columns; j++) {
                equal = equal && fabs(a->matrix[i][j] - b->matrix[i][j]) < ACCURACY;
            }
        }
    } else {
        equal = FAILURE;
    }

    return equal;
}

matrix_t s21_sum_matrix(matrix_t *a, matrix_t *b) {
    matrix_t matrix;
    char state = 0;

    state = base_check_matrices(a, b);
    if (a && b && state && a->columns == b->columns && a->rows == b->rows) {
        matrix = s21_create_matrix(a->rows, a->columns);
        simple_matrix_operations(matrix_value_summ, *a, *b, &matrix);
        check_matrix_type(&matrix);
    } else {
        matrix_error(&matrix);
    }

    return matrix;
}

matrix_t s21_sub_matrix(matrix_t *a, matrix_t *b) {
    matrix_t matrix;
    char state = 0;

    state = base_check_matrices(a, b);
    if (a && b && state && a->columns == b->columns && a->rows == b->rows) {
        matrix = s21_create_matrix(a->rows, a->columns);
        simple_matrix_operations(matrix_value_subb, *a, *b, &matrix);
        check_matrix_type(&matrix);
    } else {
        matrix_error(&matrix);
    }

    return matrix;
}

matrix_t s21_mult_number(matrix_t *a, double number) {
    matrix_t matrix;
    char state = 0;

    state = base_check_matrices(a, NULL);
    if (a && state) {
        matrix = s21_create_matrix(a->rows, a->columns);
        for (int i = 0; i < a->rows; i++) {
            for (int j = 0; j < a->columns; j++) {
                matrix.matrix[i][j] = a->matrix[i][j] * number;
            }
        }
        check_matrix_type(&matrix);
    } else {
        matrix_error(&matrix);
    }
    return matrix;
}

matrix_t s21_mult_matrix(matrix_t *a, matrix_t *b) {
    matrix_t matrix;
    char state = 0;

    state = base_check_matrices(a, b);
    if (a && b && state && a->columns == b->rows) {
        matrix = s21_create_matrix(a->rows, b->columns);
        for (int i = 0; i < matrix.rows; i++) {
            for (int j = 0; j < matrix.columns; j++) {
                calculate_multiplied_matrix_element(*a, *b, i, j, &matrix.matrix[i][j]);
            }
        }
        check_matrix_type(&matrix);
    } else {
        matrix_error(&matrix);
    }

    return matrix;
}

matrix_t s21_transpose(matrix_t *a) {
    matrix_t matrix;
    char state = 0;

    state = base_check_matrices(a, NULL);
    if (a && state) {
        matrix = s21_create_matrix(a->columns, a->rows);
        for (int i = 0; i < matrix.rows; i++) {
            for (int j = 0; j < matrix.columns; j++) {
                matrix.matrix[i][j] = a->matrix[j][i];
            }
        }
        check_matrix_type(&matrix);
    } else {
        matrix_error(&matrix);
    }

    return matrix;
}

matrix_t s21_calc_complements(matrix_t *a) {
    matrix_t matrix;
    char state = 0;

    state = base_check_matrices(a, NULL);
    if (a && state) {
        matrix = s21_create_matrix(a->rows, a->columns);
        if (a->columns > 1 && a->rows > 1) {
            for (int i = 0; i < a->rows; i++) {
                for (int j = 0; j < a->columns; j++) {
                    matrix.matrix[i][j] = algebraic_addition(*a, i, j) * (-1 + !((i + j) % 2) * 2);
                }
            }
        } else {
            matrix.matrix[0][0] = a->matrix[0][0];
        }
        check_matrix_type(&matrix);
    } else {
        matrix_error(&matrix);
    }

    return matrix;
}

double s21_determinant(matrix_t *a) {
    double returnable = 0.0;
    char state = 0;

    state = base_check_matrices(a, NULL);
    if (a && state && a->columns == a->rows) {
        if (a->rows == 1) {
            returnable = a->matrix[0][0];
        } else if (a->rows == 2) {
            returnable = calculate_2d_determinant(*a);
        } else if (a->rows == 3) {
            returnable = calculate_3d_determinant(*a);
        } else {
            returnable = calculate_Gauss_determinant(*a);
        }
    } else {
        returnable = NAN;
    }

    return returnable;
}

matrix_t s21_inverse_matrix(matrix_t *a) {
    double determinant = 0.0, inverse_determinant = 0.0;
    matrix_t matrix, buffer;
    char state = 0;

    state = base_check_matrices(a, NULL);
    if (a && state && a->rows == a->columns) {
        determinant = s21_determinant(a);
        if (fabs(determinant) >= ACCURACY) {
            inverse_determinant = 1 / determinant;
            matrix = s21_transpose(a);
            buffer = s21_calc_complements(&matrix);
            s21_remove_matrix(&matrix);
            matrix = s21_mult_number(&buffer, inverse_determinant);
            s21_remove_matrix(&buffer);
        } else {
            matrix_error(&matrix);
        }
    } else {
        matrix_error(&matrix);
    }

    return matrix;
}

double algebraic_addition(matrix_t a, int row, int col) {
    double returnable = 0.0;
    matrix_t minor;

    minor = s21_create_matrix(a.rows - 1, a.columns - 1);
    make_matrix_minor(a, row, col, &minor);
    returnable = s21_determinant(&minor);
    s21_remove_matrix(&minor);

    return returnable;
}

void make_matrix_minor(matrix_t a, int row, int col, matrix_t *minor) {
    for (int i = 0, im = 0; im < minor->rows; i++, im++) {
        for (int j = 0, jm = 0; jm < minor->rows; j++, jm++) {
            if (i == row) i++;
            if (j == col) j++;
            minor->matrix[im][jm] = a.matrix[i][j];
        }
    }
}

double calculate_2d_determinant(matrix_t a) {
    return a.matrix[0][0] * a.matrix[1][1] - a.matrix[1][0] * a.matrix[0][1];
}

double calculate_3d_determinant(matrix_t a) {
    double returnable = 0.0;

    returnable += a.matrix[0][0] * (a.matrix[1][1] * a.matrix[2][2] - a.matrix[2][1] * a.matrix[1][2]);
    returnable -= a.matrix[0][1] * (a.matrix[1][0] * a.matrix[2][2] - a.matrix[2][0] * a.matrix[1][2]);
    returnable += a.matrix[0][2] * (a.matrix[1][0] * a.matrix[2][1] - a.matrix[2][0] * a.matrix[1][1]);

    return returnable;
}

double calculate_Gauss_determinant(matrix_t a) {
    double returnable = 0.0;
    int row_constrain = 0;
    char det_zero = 0;
    matrix_t b;

    b = s21_create_matrix(a.rows, a.columns);
    copy_matrix(a, &b);
    for (int i = 0; !det_zero && i < b.columns; i++) {
        for (int j = b.rows - 1; !det_zero && j > row_constrain; j--) {
            process_the_row(&b, j, i, &det_zero);
        }
        row_constrain += 1;
    }
    if (!det_zero) {
        returnable = multiply_diagonal(b);
    } else {
        returnable = 0.0;
    }
    s21_remove_matrix(&b);

    return returnable;
}

double multiply_diagonal(matrix_t a) {
    double returnable = 1.0;

    for (int i = 0; i < a.columns; i++) returnable *= a.matrix[i][i];

    return returnable;
}

void process_the_row(matrix_t *a, const int row, int col, char *zero) {
    double prew_row_n = a->matrix[row - 1][col];
    double row_n = a->matrix[row][col] * -1;

    for (int k = col; k < a->columns && !*zero; k++) {
        if (prew_row_n != 0) {
            a->matrix[row][k] = (row_n / prew_row_n) * a->matrix[row - 1][k] + a->matrix[row][k];
        } else {
            scan_column_to_find_nonzero_num(a, row - 1, k, zero);
            prew_row_n = a->matrix[row - 1][col];
            a->matrix[row][k] = (row_n / prew_row_n) * a->matrix[row - 1][k] + a->matrix[row][k];
        }
    }
    a->matrix[row][col] = 0;
}

void scan_column_to_find_nonzero_num(matrix_t *a, const int row, const int col, char *zero) {
    char found = 0;

    for (int i = a->rows - 1; !found && i >= 0; i--) {
        if (fabs(a->matrix[i][col]) >= ACCURACY) {
            this_row_plus_that_row(a, i, row);
            found = 1;
        } else if (i == 0) {
            *zero = 1;
        }
    }
}

void this_row_plus_that_row(matrix_t *a, const int row_num, const int row_zero) {
    for (int i = 0; i < a->columns; i++) {
        a->matrix[row_zero][i] += a->matrix[row_num][i];
    }
}

void matrix_error(matrix_t *m) {
    m->matrix_type = INCORRECT_MATRIX;
    m->matrix = NULL;
    m->columns = 0;
    m->rows = 0;
}

void calculate_multiplied_matrix_element(matrix_t a, matrix_t b, int i, int j, double *res) {
    for (int k = 0; k < a.columns; k++) {
        *res += a.matrix[i][k] * b.matrix[k][j];
    }
}

void simple_matrix_operations(double operator(double, double), matrix_t a, matrix_t b, matrix_t *res) {
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.columns; j++) {
            res->matrix[i][j] = operator(a.matrix[i][j], b.matrix[i][j]);
        }
    }
    check_matrix_type(res);
}

double matrix_value_summ(double a, double b) {
    return a + b;
}

double matrix_value_subb(double a, double b) {
    return a - b;
}

void check_matrix_type(matrix_t *m) {
    char identity = 1, zero = 1, nan = 0;

    for (int i = 0; !nan && i < m->rows; i++) {
        for (int j = 0; !nan && j < m->columns; j++) {
            if (m->matrix) {
                identity = identity && ((i == j && fabs(m->matrix[i][j] - 1) < ACCURACY) ||
                                                    (i != j && fabs(m->matrix[i][j]) < ACCURACY));
                zero = zero && fabs(m->matrix[i][j]) < ACCURACY;
                if (m->matrix[i][j] != m->matrix[i][j]) nan = 1;
            } else {
                identity = 0;
                zero = 0;
            }
        }
    }

    if (!nan && identity && m->rows == m->columns)
        m->matrix_type = IDENTITY_MATRIX;
    else if (!nan &&zero)
        m->matrix_type = ZERO_MATRIX;
    else if (!nan)
        m->matrix_type = CORRECT_MATRIX;
    else
        m->matrix_type = INCORRECT_MATRIX;
}

char base_check_matrices(matrix_t *a, matrix_t *b) {
    char state = 1;

    if (a) {
        check_matrix_status(a, &state);
    }
    if (b && state) {
        check_matrix_status(b, &state);
    }

    return state;
}

void check_matrix_status(matrix_t *a, char *state) {
    *state = a->columns > 0 && a->rows > 0 && a->matrix != NULL && a->matrix_type != INCORRECT_MATRIX;
    for (int i = a->rows - 1; *state && i >= 0; i--) {
        *state = *state && a->matrix[i];
        if (*state) {
            for (int j = 0; j < a->columns; j++) {
                *state = *state && a->matrix[i][j] == a->matrix[i][j];
            }
        }
    }
}

void copy_matrix(matrix_t a, matrix_t *b) {
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.columns; j++) {
            b->matrix[i][j] = a.matrix[i][j];
        }
    }
}
