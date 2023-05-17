BIN=shell

all:
	bison -d -g -v $(BIN).y
	# En fonction de la version de bison, il génère un fichier .gv ou .dot
	if [ -f $(BIN).gv ]; then \
		dot -Tdot $(BIN).gv -o $(BIN).dot; \
	fi
	dot -Tpng $(BIN).dot -o $(BIN).png
	flex $(BIN).l
	$(CC) -c lex.yy.c -o lex.yy.o
	$(CC) -c functions.c -o functions.o
	$(CC) -c $(BIN).tab.c -o $(BIN).tab.o
	$(CC) -o bin *.o  -lm

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
	$(CC) -o bin *.o  -lm

clean:
	rm -fv bin $(BIN).tab.h $(BIN).tab.c lex.yy.c *.o lex.backup $(BIN).dot $(BIN).png $(BIN).output $(BIN).vcg $(BIN).gv output.svg

c:
	rm -fv bin $(BIN).tab.h $(BIN).tab.c lex.yy.c *.o lex.backup $(BIN).dot $(BIN).png $(BIN).output $(BIN).vcg $(BIN).gv
	gcc *.c && ./a.out
	rm a.out