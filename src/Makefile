.POSIX:
CC=gcc -std=c11
CFLAGS = -Wall -Wextra -Werror
INSTALL_FILES = main.c gui/cli/*.c brick_game.a -lncurses
INSTALL_TEST = gui/cli/*.c brick_game/tetris/*.c  brick_game.a -lncurses
FLAGSCH = -lcheck
TARGET = brick_game


ifeq ($(shell uname),Linux)
	FLAGSCH += -lm -lsubunit
endif

OPEN_COMMAND =open
ifeq ($(OS), Linux)
	OPEN_COMMAND=xdg-open
else
	OPEN_COMMAND=open
endif

all: clean install

install: backend.a
	$(CC) $(INSTALL_FILES) -o tetris
	./tetris

uninstall:
	@rm -f tetris.out
	@echo "Uninstallation is finished"

run:
	./tetris

clean:
	rm -rf *.o *.a *.gcno *.gcda *.info report *.dSYM tetris test

test: clean backend.a
	$(CC) $(INSTALL_TEST) --coverage tests/tests.c -o test $(FLAGSCH)
	./test

backend.a: backend.o
	ar rcs $(TARGET).a *.o
	ranlib $(TARGET).a

backend.o: 
	$(CC) $(CFLAGS) -c brick_game/tetris/*.c 

dvi:
	${OPEN_COMMAND} ../dvi/README.md

dist:
	tar -czvf archive.tar.gz ./*

gcov_report: test
	lcov -t "result" -o res.info -c -d .
	genhtml -o report res.info
	open report/index.html
	rm -rf *gcda *gcno res.info test

# dist: clean_dist
# 	cd ../ && mkdir -p ${DIST_DIR}
# 	cd ../ && cp -rf src/brick_game ${DIST_DIR}/brick_game
# 	cd ../ && cp -rf src/gui ${DIST_DIR}/gui
# 	cd ../ && cp -rf src/Makefile ${DIST_DIR}/
# 	cd ../ && tar -czvf archive.tar.gz ${DIST_DIR}
# 	cd ../ && rm -rf ${DIST_DIR}
# dist_unpack:
# 	cd ../ && tar -xzvf archive.tar.gz

# test:
# 	@mkdir -p ../tests/build
# 	gcc ../tests/main_test.c ${CFLAGS} $(BACKEND) ${COMMON} $(TEST_FLAGS) -o ./test.out
# 	./test.out

test_valgrind:
	@mkdir -p ../tests/build
	gcc ../tests/main_test.c ${CFLAGS} $(BACKEND) ${COMMON} $(TEST_FLAGS) -o ./test.out
	valgrind ${VALGRIND_FLAGS} ./test.out

clang_i:
	cp ../materials/linters/.clang-format .
	@find .. -type f -name "*.c" -exec clang-format -i -style=Google {} \;
	@find .. -type f -name "*.h" -exec clang-format -i -style=Google {} \;
	@echo "Clang format style apply is finished"


clang_n:
	cp ../materials/linters/.clang-format .
	@find .. -type f -name "*.c" -exec clang-format -n -style=Google {} \;
	@find .. -type f -name "*.h" -exec clang-format -n -style=Google {} \;
	@echo "Clang format style check is finished"

# clean: clean_project clean_static_lib clean_log clean_exec clean_obj clean_gcov clean_lcov clean_lcov_report clean_dist
# 	@echo "Clean finished"

clean_project:
	@find .. -type f -name "*.records" -exec rm {} \;


clean_dist:
	@cd ../ && rm -rf archive
	@cd ../ && rm -rf archive.tar.gz
clean_after_building:
	@rm -rf ${OBJ_DIR}
clean_static_lib:
	@find .. -type f -name "*.a" -exec rm {} \;
clean_log:
	@find .. -type f -name "*.log" -exec rm {} \;
clean_exec:
	@find .. -type f -name "*.out" -exec rm {} \;
clean_obj:
	@find .. -type f -name "*.o" -exec rm {} \;
clean_gcov:
	@find .. -type f -name "*.gcda" -exec rm {} \;
	@find .. -type f -name "*.gcno" -exec rm {} \;
clean_lcov:
	@find .. -type f -name "*.info" -exec rm {} \;
clean_lcov_report:
	@rm -rf report

.PHONY: all install unistall clean test dvi dist gcov_report clang