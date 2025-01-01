CC = cc
FLAGS = -Wall -Wextra -Werror
SRCS = ft_putchar_fd.c ft_putstr_fd.c ft_split.c ft_strdup.c ft_strjoin.c ft_strlen.c \
		ft_strnstr.c utils.c pipex.c
OBJS = $(SRCS:.c=.o)
NAME = pipex

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
	
.PHONY: all clean fclean re
