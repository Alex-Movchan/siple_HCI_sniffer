NAME = hcisniffer

G = gcc

SRC = hcisnif.c \
      	hciscan.c \
	libfunc.c \
	ltg_hciconfig.c \
	searchInPath.c \


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(G) $(SRC) -o $@

%.o: %.c
	$(G) -c $< -o $@

clean:
	rm -fr $(OBJ)

fclean: clean
	rm -fr $(NAME)

re: fclean all
