# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/21 18:32:58 by oufarah           #+#    #+#              #
#    Updated: 2025/06/24 22:04:19 by oufarah          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
RM = rm -rf

CFLAGS = -Wall -Wextra -Werror


SRC = minishell.c \
	parse/utils/ft_strlen.c \
	parse/ft_check_quots.c \
	parse/ft_parse_command.c \
	parse/utils/ft_strjoin.c \
	parse/utils/ft_lst_utils.c \
	parse/utils/ft_syntax_error.c \
	parse/ft_split_command.c \
	parse/ft_token_type.c \
	parse/utils/ft_substr.c \
	parse/utils/ft_is_space.c \
	parse/utils/ft_split.c \
	parse/utils/ft_strchr.c \
	parse/utils/ft_strdup.c \
	parse/utils/ft_strlcpy.c \
	garbage.c \
	parse/ft_quotes_type.c \
	parse/ft_expend.c \
	parse/utils/ft_strlcat.c \
	exec/exec_main.c \
	exec/exec_child.c \
	exec/builtins.c \
	exec/exec_list.c \
	exec/exec_more_list.c \
	exec/parse_to_exec.c \
	exec/exec_utils.c \
	exec/export.c \
	exec/unset.c \
	exec/echo.c \
	exec/env.c \
	exec/cd.c \
	exec/ft_split_exec.c \
	parse/ft_redirection_operators.c \
	parse/utils/ft_strcomp.c \
	exec/exit.c \
	exec/ft_itoa_atoi.c \
	exec/pwd.c \
	exec/export_more.c \
	exec/parse_to_exec_more.c \
	exec/find_cmd_path.c \
	parse/ft_expand_value.c \
	parse/ft_check_bracets.c \
	parse/ft_remove_bracets.c \
	parse/ft_logic_syntax.c \
	parse/utils/ft_isalpha.c \
	parse/ft_getenv.c \
	parse/utils/split_expn.c \
	parse/utils/ft_acctual_split.c \
	parse/utils/split_var.c \
	parse/skip_till_pipe.c

OBJ = $(SRC:.c=.o)

HEADER = minishell.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ -lreadline

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean
