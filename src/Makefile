CC=gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
LINUX_FLAGS = -lm -lncurses -lcheck -lsubunit -lm -lrt -lpthread
MACOS_FLAGS = -lm -lncurses
GCOV_FLAGS=-fprofile-arcs -ftest-coverage

ifeq ($(shell uname), Linux)
    LDFLAGS = $(LINUX_FLAGS)
endif
ifeq ($(shell uname), Darwin)
    LDFLAGS = $(MACOS_FLAGS)
endif

all:	install

install:
	mkdir -p build
	$(CC) $(CFLAGS) brick_game/tetris/*.c gui/cli/*.c -o tetris $(LDFLAGS) -o build/tetris
	echo 0 > build/the_best_score.txt

uninstall:
	rm -rf build


gcov_report: back.a
	$(CC) $(CFLAGS) $(GCOV_FLAGS) test/*.c brick_game/tetris/*.c -L. back.a -o testing $(LDFLAGS)
	make run_tests
	lcov -t "testing" -o testing.info -c -d .
	genhtml -o report testing.info
	open report/index.html
back.a:
	$(CC) $(CFLAGS) -c brick_game/tetris/*.c $(LDFLAGS) 
	ar rc back.a *.o
	rm -rf *.o
test:	back.a
	$(CC) $(CFLAGS) test/*.c -L. back.a  $(LDFLAGS) -o testing 
	make run_tests
	
tetris: 
	$(CC) $(CFLAGS) brick_game/tetris/*.c gui/cli/*.c -o tetris $(LDFLAGS)
	make run_game
	make clean

format:
	clang-format -style=google -i */*/*.c */*/*.h test/*.c

style:
	clang-format -style=google -n */*/*.c */*/*.h test/*.c
valgrind:	back.a
	$(CC) $(CFLAGS) test/*.c -L. back.a  $(LDFLAGS) -o testing 
	valgrind --tool=memcheck --leak-check=yes ./testing
    
clean:
	rm -rf *.o a.out *.info *.gcda *.gcno  back.a tetris testing report
run_tests:
	./testing
run_game:
	./tetris
dvi:
	open doc.html

dist:
	mkdir -p builder
	cp -a brick_game builder
	cp -a gui builder
	cp -a *.txt builder
	cp -a doc.html builder
	tar -czf Tetris.tar.gz builder
	rm -rf builder	

	
