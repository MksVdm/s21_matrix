TEST_FLAGS=-I -L -lcheck `pkg-config --cflags --libs check`
CPP_FLAGS=-Wall -Wextra -Werror
STD=-std=c11
DEBUG_FLAG=-g
GCOV_FLAG=--coverage
OBJECTS=s21_matrix.o s21_matrix_test.o
FUNCS=s21_matrix.c
TEST_C=s21_matrix.c s21_matrix_test.c
EXECUTABLE=s21_matrix_test.out
CC=gcc
LINT_WAY=../materials/linters/cpplint.py
LINTCFG_WAY=../materials/linters/CPPLINT.cfg
LINTCFG=CPPLINT.cfg
COPY=cp
PY=python3
EXTENSION=--extensions=c
CHECK_FILES=*.c *.h
CPPCH=cppcheck
DELETE=rm -rf
TO_DELETE=*.o *.a *.gcda *.gcno *.info report *.dSYM

all: gcov_report check s21_matrix.a test

check:
	$(CPPCH) $(CHECK_FILES)
	$(COPY) $(LINTCFG_WAY) $(LINTCFG)
	$(PY) $(LINT_WAY) $(EXTENSION) $(CHECK_FILES)

clean:
	$(DELETE) $(TO_DELETE) $(EXECUTABLE) $(LINTCFG)

test: clean
	# $(CC) $(STD) $(CPP_FLAGS) $(DEBUG_FLAG) $(GCOV_FLAG) $(TEST_C) -o $(EXECUTABLE) $(TEST_FLAGS)
	$(CC) $(STD) $(DEBUG_FLAG) $(GCOV_FLAG) $(TEST_C) -o $(EXECUTABLE) $(TEST_FLAGS)
	./s21_matrix_test.out

gcov_report: test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info

s21_matrix.a:
	$(CC) -c $(FUNCS)
	ar rc s21_matrix.a s21_matrix.o
	ranlib s21_matrix.a

valgrind: test
	CK_FORK=no valgrind --tool=memcheck --leak-check=full ./$(EXECUTABLE)

leaks: test
	leaks -atExit -- ./$(EXECUTABLE)
