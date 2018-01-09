# TODO: use automatic rule
CC=clang++
CFLAGS=-g -Wall -Wno-unused -std=c++11
GTEST_LIBS=-lgtest -lpthread
FLEX_LIBS=-ll
FFLAGS=
BFLAGS=-d --verbose -t --debug -v -g

cool-tree.o: cool-tree.cc cool-tree.h symboltab.h helper.h
	$(CC) $(CFLAGS) $< -c -o $@

symboltab.o: symboltab.cc symboltab.h helper.h
	$(CC) $(CFLAGS) $< -c -o $@

cool.tab.c, cool.tab.h: cool.y
	bison $(BFLAGS) cool.y

lex.yy.c: cool.flex cool.tab.h
	flex $(FFLAGS) $<

lex-test.o: lex-test.cc cool.tab.h cool-tree.h
	$(CC) $(CFLAGS) $< -c -o $@

lex.yy.o: lex.yy.c symboltab.h cool-tree.h
	$(CC) $(CFLAGS) $< -c -o $@

helper.o: helper.cc helper.h cool.tab.h cool-tree.h
	$(CC) $(CFLAGS) $< -c -o $@

helper-test.o: helper-test.cc
	$(CC) $(CFLAGS) $< -c -o $@

helper-test: helper-test.o helper.o
	$(CC) $(CFLAGS) $(GTEST_LIBS) $^ -o $@

cool-lexer: lex-test.o lex.yy.o symboltab.o cool-tree.o helper.o cool.tab.o
	$(CC) $(CFLAGS) $(FLEX_LIBS) $^ -o $@ 

cool.tab.o: cool.tab.c cool.tab.h cool-tree.h symboltab.h
	$(CC) $(CFLAGS) $< -c -o $@

cool-parser: parser-test.o cool.tab.o lex.yy.o symboltab.o cool-tree.o helper.o
	$(CC) $(CFLAGS) $(FLEX_LIBS) $^ -o $@

inheritance-tree.o: inheritance-tree.cc inheritance-tree.h helper.h cool-tree.h symboltab.h
	$(CC) $(CFLAGS) $< -c -o $@

semant.o: semant.cc semant.h inheritance-tree.h helper.h cool-tree.h symboltab.h
	$(CC) $(CFLAGS) $< -c -o $@

semantic-test.o: semantic-test.cc inheritance-tree.h cool-tree.h helper.h
	$(CC) $(CFLAGS) $< -c -o $@

cool-semant: semantic-test.o inheritance-tree.o cool.tab.o lex.yy.o symboltab.o cool-tree.o helper.o semant.o
	$(CC) $(CFLAGS) $(FLEX_LIBS) $^ -o $@

cgen.o: cgen.cc cgen.h cool-tree.h helper.h
	$(CC) $(CFLAGS) $< -c -o $@

codegen-test.o: codegen-test.cc
	$(CC) $(CFLAGS) $< -c -o $@

cool-codegen: codegen-test.o cgen.o semant.o inheritance-tree.o cool.tab.o lex.yy.o symboltab.o cool-tree.o helper.o
	$(CC) $(CFLAGS) $(FLEX_LIBS) $^ -o $@

clean:
	rm *.o
