BIN=shell
CC=gcc

all:
	bison -d -v $(BIN).y

	flex $(BIN).l
	$(CC) -c lex.yy.c -o lex.yy.o
	$(CC) -c functions.c -o functions.o
	$(CC) -c $(BIN).tab.c -o $(BIN).tab.o
	$(CC) -o minshell *.o  -lm

debug: $(BIN).y $(BIN).l
	bison -d -g -v $(BIN).y
	if [ -f $(BIN).gv ]; then \
		dot -Tdot $(BIN).gv -o $(BIN).dot; \
	fi
	dot -Tpng $(BIN).dot -o $(BIN).png
	flex -d $(BIN).l
	$(CC) -c lex.yy.c -o lex.yy.o
	$(CC) -c functions.c -o functions.o
	$(CC) -c $(BIN).tab.c -o $(BIN).tab.o
	$(CC) -o minshell *.o  -lm

clean:
	rm -fv minshell $(BIN).tab.h $(BIN).tab.c lex.yy.c *.o lex.backup $(BIN).dot $(BIN).png $(BIN).output $(BIN).vcg $(BIN).gv output.svg

c:
	rm -fv minshell $(BIN).tab.h $(BIN).tab.c lex.yy.c *.o lex.backup $(BIN).dot $(BIN).png $(BIN).output $(BIN).vcg $(BIN).gv
	gcc *.c && ./a.out
	rm a.out