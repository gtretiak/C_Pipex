# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtretiak <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 18:19:21 by gtretiak          #+#    #+#              #
#    Updated: 2025/06/14 17:10:58 by gtretiak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_B = pipex_bonus
LIBFT = libft.a
LIBFT_DIR = C_libft/
PIPEX_LIB = pipex.a
PIPEX_LIB_B = pipex_bonus.a
HEADER = pipex.h
HEADER_B = pipex_bonus.h
SRCS_B = main_bonus.c check_errors_bonus.c freeing_bonus.c files_bonus.c \
	 processes_bonus.c child_processes_bonus.c \
	 execution_bonus.c utils_bonus.c
SRCS_DIR_B = Sources_bonus/
SRCS = main.c check_free_errors.c processes.c execution.c 
SRCS_DIR = Sources/
OBJS = $(addprefix $(SRCS_DIR), $(SRCS:.c=.o))
OBJS_B = $(addprefix $(SRCS_DIR_B), $(SRCS_B:.c=.o))
CFLAGS = -Wall -Wextra -Werror

all: $(LIBFT) $(PIPEX_LIB) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(PIPEX_LIB): $(OBJS) $(HEADER) $(LIBFT_DIR)$(LIBFT)
	ar -rc $(PIPEX_LIB) $^

$(SRCS_DIR)%.o: $(SRCS_DIR)%.c $(HEADER) $(LIBFT_DIR)$(LIBFT)
	cc $(CFLAGS) -I. -I$(LIBFT_DIR) -c $< -o $@

$(NAME): $(PIPEX_LIB) $(LIBFT) $(OBJS)
	@if [ ! -f $(NAME) ] || [ $(LIBFT) -nt $(NAME) ] \
		|| [ $(PIPEX_LIB) -nt $(NAME) ]; then \
		cc $(PIPEX_LIB) -L$(LIBFT_DIR) -lft -o $(NAME); fi

.PHONY: clean fclean re bonus clean_bonus fclean_bonus re_bonus

bonus: $(LIBFT) $(PIPEX_LIB_B) $(NAME_B)

$(PIPEX_LIB_B): $(OBJS_B) $(HEADER_B) $(LIBFT_DIR)$(LIBFT)
	ar -rc $(PIPEX_LIB_B) $^

$(SRCS_DIR_B)%.o: $(SRCS_DIR_B)%.c $(HEADER_B) $(LIBFT_DIR)$(LIBFT)
	cc $(CFLAGS) -I. -I$(LIBFT_DIR) -c $< -o $@

$(NAME_B): $(PIPEX_LIB_B) $(LIBFT) $(OBJS_B)
	@if [ ! -f $(NAME_B) ] || [ $(LIBFT) -nt $(NAME_B) ] \
		|| [ $(PIPEX_LIB_B) -nt $(NAME_B) ]; then \
		cc $(PIPEX_LIB_B) -L$(LIBFT_DIR) -lft -o $(NAME_B); fi
clean:
	rm -f $(OBJS)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(PIPEX_LIB)
	rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

clean_bonus:
	rm -f $(OBJS_B)
	@make clean -C $(LIBFT_DIR)

fclean_bonus: clean_bonus
	rm -f $(PIPEX_LIB_B)
	rm -f $(NAME_B)
	@make fclean -C $(LIBFT_DIR)

re_bonus: fclean_bonus bonus
