OS := $(shell uname)
CC = -Wall -Werror -Wextra -std=c11
FLAGS = -lcheck -lpthread -fprofile-arcs
Sanitize = fsanitize

ifeq ($(OS),Darwin)
	FLAGS += -ftest-coverage
	OPEN_CMD = open
	OPEN_APP = $(OPEN_CMD) 
        APP = 3d_viewer.app
else
	FLAGS += -lm -lrt -lsubunit -ftest-coverage
	OPEN_CMD = xdg-open
	OPEN_APP = ./
        APP = 3d_viewer
endif

all: clean install open

install: clean
	cd front/3d && qmake && make -j6 && make clean && mv 3d.app ../../3d_viewer.app && rm -rf front.app

uninstall:
	cd front/3d && rm -rf Makefile ../../$(APP) front/3d.pro.user .qmake.stash .qtc_clangd .tmp

open:
	$(OPEN_APP)$(APP)

dvi:
	$(OPEN_CMD) README.md

dist: clean install
	cd .. && tar -czvf src/3d_viewer.tar.gz src

test: clean
	gcc $(CC) tests/tests.c back/*.c $(FLAGS) -lgcov -coverage -o test
	./test

clang:
	clang-format -style=Google -n tests/*.h tests/*.c back/*.h back/*.c front/3d/*.cpp front/3d/*.h

toclang:
	clang-format --style=Google -i tests/*.h tests/*.c back/*.h back/*.c front/3d/*.cpp front/3d/*.h

leaks:
	CK_FORK=no leaks --atExit -- ./test

gcov_report: clean
	gcc $(CC) tests/tests.c back/*.c $(FLAGS) -o test
	./test
	lcov -t "./test"  -o report.info --no-external -c -d .
	genhtml -o report report.info
	$(OPEN_CMD) ./report/index.html

	rm -rf *.gcno *gcda *.gco

rebuild: clean install open

clean: uninstall
	rm -rf *.o *.a test
	rm -rf *.gcno *gcda *.gcov gcov
	rm -rf report report.info
	rm -rf 3d_viewer.tar.gz

tt:
	gcc back/*.c && ./a.out
