CC		=	gcc
CFLAGS	=	-Wextra -Wall -Werror -I ./
OUT		=	microshell
SRC		=	microshell.c
OBJ		=	$(SRC:.cpp=.o)

all: $(OUT)

%.o : %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

clean:
	rm -fr $(OBJ)

fclean:
	make clean
	rm -fr $(OUT)

re: fclean all
