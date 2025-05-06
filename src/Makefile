CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11
MAC_FLAGS=-lcheck -lm
LINUX_FLAGS=-lcheck -lm -lrt -lpthread -lsubunit
GCOV_FLAGS=-fprofile-arcs -ftest-coverage

FILES=$(wildcard s21_*.c)
OBJ=$(patsubst %.c, %.o, $(FILES))
TEST_FILES=$(wildcard tests/*.c)
USERNAME=$(shell whoami)

MYLIB=s21_matrix.a

OS := $(shell uname -s)

ifeq ($(OS),Darwin)
	OPEN=open
endif
ifeq ($(OS),Linux)
	OPEN=xdg-open
endif

all: $(MYLIB)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(MYLIB): $(OBJ)
	ar rc $@ $^
	ranlib $@

test: $(MYLIB) $(TEST_FILES)
ifeq ($(OS),Darwin)
	$(CC) $(FLAGS) $(GCOV_FLAGS) $(TEST_FILES) $(MYLIB) -o test $(MAC_FLAGS)
else
	$(CC) $(FLAGS) $(GCOV_FLAGS) $(TEST_FILES) $(MYLIB) -o test $(LINUX_FLAGS)
endif
	./test

gcov_report: clean
	mkdir -p report
ifeq ($(OS),Darwin)
	$(CC) $(FLAGS) $(GCOV_FLAGS) $(FILES) $(TEST_FILES) -o test $(MAC_FLAGS)
else
	$(CC) $(FLAGS) $(GCOV_FLAGS) $(FILES) $(TEST_FILES) -o test $(LINUX_FLAGS)
endif
	./test
	lcov --capture --directory . --output-file report/coverage.info
	genhtml report/coverage.info --output-directory report
	$(OPEN) report/index.html


style_check:
	clang-format -i -style=google *.c *.h
	clang-format -n -style=google *.c *.h

clean:
	rm -rf *.a *.o *.gcda *.gcno *.gcov test report

rebuild: clean all
