SRC := $(wildcard *.c)
OBJ := $(patsubst %.c, %.o, $(SRC))

lexer : $(OBJ)
	gcc -o $@ $^

clean_obj : 
	rm *.o
clean_all :
	rm *.o *.out
