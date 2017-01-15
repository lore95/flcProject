EXE = flcProject
SRC = main.c utilities.c flc_lex.c flc_yacc.c

LEX = flex
YACC = bison --debug -o y.tab.c

LOCAL_CFLAGS = -O -g
LOCAL_LIBES = -lfl

CC = gcc
LD = gcc

.SUFFIXES: .uil .uid .do .x .C .ec 

CFLAGS = -I/usr/include $(LOCAL_CFLAGS)

OBJ =  $(SRC:.c=.o) 

LIBES = $(LOCAL_LIBES)

$(EXE):		$(OBJ) 
		$(LD) -o $@ $(OBJ) $(LIBES)

all:	$(EXE)

compile:	$(EXE)

clean: 
	rm -f $(EXE) $(OBJ) flc_yacc.c flc_lex.c y.tab.c y.tab.h

y.tab.h: 
	@echo Updating parser symbol defs ...
	$(YACC) -d flc_yacc.y
	rm -f y.tab.c

flc_lex.c:   flc_lex.l y.tab.h 
	@echo Building lexical analyzer ...
	$(LEX) -t $< > $@

flc_yacc.c:  flc_yacc.y
	@echo Building parser ...
	$(YACC) $< 
	mv y.tab.c $@
