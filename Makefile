# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gphilips <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/29 19:19:11 by gphilips          #+#    #+#              #
#    Updated: 2017/11/29 18:19:28 by gphilips         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1

SRC = main.c scene.c object.c get.c ray.c draw.c closest_t.c inter.c \
	  inter_utils.c color.c vector_op.c vector_op2.c hook.c display.c \
	  translate.c rotate.c

CFLAGS = -Wall -Werror -Wextra
MLX = -lmlx -framework OpenGL -framework AppKit
LIBDIR = libft/
LIB = libft.a
LIBPATH = $(addprefix $(LIBDIR), $(LIB))
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	@make -C $(LIBDIR)
	@gcc -o $(NAME) $(OBJ) $(LIBPATH) $(MLX)
	@echo "$@ created"

all: $(NAME)

clean:
	@make clean -C $(LIBDIR)
	@rm -f $(OBJ)
	@echo "Erasing .o files from rtv1"

fclean:
	@make fclean -C $(LIBDIR)
	@rm -f $(OBJ)
	@echo "Erasing .o files from rtv1"
	@rm -f $(NAME)
	@echo "Erasing $(NAME)"

re: fclean all

.PHONY: all clean fclean re
