NAME_PROGRAMM = push_swap

CC          = cc
CFLAGS      = -Wall -Wextra -Werror

LIBFT_PATH  = libft/
LIBFT       = $(LIBFT_PATH)libft.a
INCLUDES    = -I. -I$(LIBFT_PATH)

SRCS_PROGRAMM = push_swap.c \
stack/tools.c \
stack/stack.c \
stack/checkers.c \
stack/input_check.c \
stack/init_stacks.c \
stack/cleanup.c \
sort/sort_helpers_2.c \
sort/sort_helpers.c \
sort/sort.c \
moves/push.c \
moves/rotate_back.c \
moves/rotate.c \
moves/swap.c \
sort/rot_both.c \
sort/lis.c \
sort/positions.c

OBJS_PROGRAMM = $(SRCS_PROGRAMM:.c=.o)

all: $(NAME_PROGRAMM) $(NAME_SERVER)

$(NAME_PROGRAMM): $(OBJS_PROGRAMM) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_PROGRAMM) $(LIBFT) $(INCLUDES) -o $(NAME_PROGRAMM)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_PATH)

clean:
	rm -f $(OBJS_PROGRAMM)
	make clean -C $(LIBFT_PATH)

fclean: clean
	rm -f $(NAME_PROGRAMM)
	make fclean -C $(LIBFT_PATH)

re: fclean all