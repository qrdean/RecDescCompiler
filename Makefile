CC=gcc
CFLAGS=-o
LEXFLAGS=-lfl
c_source := src/main.c
lex_source := src/rules.l
lex_yy := src/lex.yy.c
c_exe := build/parser
lexer_exe := build/lexer

all: $(lex_source) $(lexer_exe) $(c_source) $(c_exe)

clean:
	@rm -f $(lex_yy)
	@rm -f $(c_exe)
	@rm -f $(lexer_exe)

$(lexer_exe): $(lex_source)
	@flex -o $(lex_yy) $(lex_source)
	$(CC) $(CFLAGS) $@ $(lex_yy) $(LEXFLAGS)

$(c_exe): $(c_source) $(lexer_exe)
	$(CC) $(CFLAGS) $@ $(c_source) $(LEXFLAGS)
