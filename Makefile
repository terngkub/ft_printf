# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/08 09:11:21 by nkamolba          #+#    #+#              #
#    Updated: 2017/11/23 13:24:24 by terng            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libftprintf.a

SRC = ft_printf.c getconv.c printer.c
SRCO = ${SRC:%.c=%.o}

FILES =	ft_memset ft_bzero ft_memcpy ft_memccpy ft_memmove ft_memchr ft_memcmp\
		ft_strlen ft_strdup ft_strcpy ft_strncpy\
		ft_strcat ft_strncat ft_strlcat\
		ft_strchr ft_strrchr ft_strstr ft_strnstr\
		ft_strcmp ft_strncmp ft_atoi\
		ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint\
		ft_toupper ft_tolower\
		ft_memalloc ft_memdel ft_strnew ft_strdel ft_strclr\
		ft_striter ft_striteri ft_strmap ft_strmapi ft_strequ ft_strnequ\
		ft_strsub ft_strjoin ft_strtrim ft_strsplit ft_itoa\
		ft_putchar ft_putstr ft_putendl ft_putnbr\
		ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd\
		ft_countword ft_wordlen ft_getword ft_skipc ft_skiptoc\
		ft_numlen ft_power\
		ft_lstnew ft_lstdelone ft_lstdel ft_lstadd ft_lstiter ft_lstmap\
		ft_lstpushback ft_lstprint ft_lstsearch ft_lstrev
		
LIBO = $(addprefix libft/, $(addsuffix .o, $(FILES)))

all : $(NAME)

$(NAME) :
	make -C libft/
	gcc -Wall -Wextra -Werror $(SRC)
	ar rc $(NAME) $(SRCO) $(LIBO)
	ranlib $(NAME)

clean :
	make clean -C libft/
	rm -f $(SRCO) 

fclean : 
	make fclean -C libft/
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
