BIN = ./wish
OBJS = wish_yyparser.tab.o lex.yy.o wish.o wish_read.o wish_parse.o

CFLAGS = -Wall -pedantic -Wextra -Wcast-align -Wcast-qual \
	-Wdisabled-optimization -Wformat=2 -Winit-self \
	-Wmissing-include-dirs -Wredundant-decls -Wshadow \
	-Wstrict-overflow=5 -Wundef -Werror -Wno-unused \
	-g -Wno-unused-result -O3 -Wlogical-op -Wno-strict-overflow 

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $(BIN) -lreadline #-lefence

wish.o: wish.c wish.h

wish_read.o: wish_read.c wish.h

wish_parse.o: wish_yyparser.tab.h wish.h

wish_yyparser.tab.c wish_yyparser.tab.h: wish_yyparser.y
	bison -d wish_yyparser.y

wish_yyparser.tab.o: wish_yyparser.tab.c wish.h

lex.yy.o: lex.yy.c wish.h wish_yyparser.tab.h

lex.yy.c: wish_yylexer.l
	flex -I wish_yylexer.l 

clean:
	rm -f $(OBJS) $(BIN) lex.yy.c\
		wish_yyparser.tab.c wish_yyparser.tab.h

valgrind: all
	clear
	valgrind --leak-check=full $(BIN)
