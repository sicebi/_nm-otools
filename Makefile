# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antini <antini@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/16 10:51:10 by antini            #+#    #+#              #
#    Updated: 2019/08/17 13:01:54 by antini           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_NM = ft_nm
NAME_OT = ft_otool

H_DIR = includes/

C_DIR_NM = src_nm/
O_DIR_NM = obj_nm/

C_DIR_OT = src_ot/
O_DIR_OT = obj_ot/

LIBFT = libft/
LBT = libft/libft.a
LBRY = (cd $(LIBFT) && make)
CC = gcc
FLAGS = -Wall -Wextra -Werror

C_FILES_NM = main.c
C_FILES_NM += nm_64.c
C_FILES_NM += nm_32.c
C_FILES_NM += nm_list.c
C_FILES_NM += nm_tools.c

C_FILES_OT = main.c
C_FILES_OT += otool_64.c
C_FILES_OT += otool_32.c
C_FILES_OT += otool.c

O_FILES_NM = $(addprefix  $(O_DIR_NM),$(C_FILES_NM:.c=.o))
O_FILES_OT = $(addprefix $(O_DIR_OT),$(C_FILES_OT:.c=.o))

all: $(NAME_NM) $(NAME_OT) 
# all: $(LBRY) $(NAME_NM) $(NAME_OT)


$(NAME_NM): $(O_FILES_NM)
	$(CC) -o $(NAME_NM) $(O_FILES_NM) $(LBT)

$(NAME_OT): $(O_FILES_OT)
	$(CC) -o $(NAME_OT) $(O_FILES_OT) $(LBT)

$(O_FILES_NM): $(O_DIR_NM)%.o: $(C_DIR_NM)%.c
	@mkdir -p $(O_DIR_NM)
	$(CC) -o $@ -c $< -Iincludes

$(O_FILES_OT): $(O_DIR_OT)%.o: $(C_DIR_OT)%.c
	@mkdir -p $(O_DIR_OT)
	$(CC) -o $@ -c $< -Iincludes

clean:
	make -C $(LIBFT) clean
	@rm -rf $(O_DIR_NM)
	@rm -rf $(O_DIR_OT)

fclean: clean
	make -C $(LIBFT) fclean
	@rm -f $(NAME_NM) 
	@rm -f $(NAME_OT)
re: fclean all