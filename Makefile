# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/08 09:11:21 by nkamolba          #+#    #+#              #
#    Updated: 2017/11/22 17:20:00 by nkamolba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all $(NAME) clean fclean re

NAME = libft.a

all : $(NAME)

$(NAME) :
	make -C libft/

clean :
	make clean -C libft/

fclean : 
	make fclean -C libft/

re : fclean all
