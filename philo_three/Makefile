
NAME	= philo_three

CC		= gcc
FLAGS	= -Wall -Wextra -Werror -g

SRC_DIR	= srcs/
OBJ_DIR	= objs/
INC_DIR	= includes/

FILES	= start_simulation validation init utils get_time main 

SRCS 	= $(patsubst %, $(SRC_DIR)%.c, $(FILES))
OBJS 	= $(patsubst %, $(OBJ_DIR)%.o, $(FILES))


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(FLAGS) $(OBJS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@ -I $(INC_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re