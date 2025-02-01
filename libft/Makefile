# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 10:42:06 by dgomez-a          #+#    #+#              #
#    Updated: 2024/04/26 17:48:16 by dgomez-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
       ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
       ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
       ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
       ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
       ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
       ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			 ft_atoi_base.c

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
	ft_lstmap.c

TEST = test_ft_isalpha.c test_ft_isdigit.c test_ft_isalnum.c test_ft_isascii.c \
		test_ft_isprint.c test_ft_atoi.c test_ft_bzero.c test_ft_calloc.c test_ft_itoa.c \
		test_ft_lstadd_back.c test_ft_lstadd_front.c test_ft_lstclear.c \
		test_ft_lstdelone.c test_ft_lstiter.c test_ft_lstlast.c \
		test_ft_lstmap.c test_ft_lstnew.c test_ft_lstsize.c test_ft_memchr.c \
		test_ft_memcmp.c test_ft_memcpy.c test_ft_memmove.c test_ft_memset.c \
		test_ft_putchar_fd.c test_ft_putendl_fd.c test_ft_putnbr_fd.c \
		test_ft_putstr_fd.c test_ft_split.c test_ft_strchr.c test_ft_strdup.c \
		test_ft_striteri.c test_ft_strjoin.c test_ft_strlcat.c test_ft_strlcpy.c \
		test_ft_strlen.c test_ft_strmapi.c test_ft_strncmp.c test_ft_strnstr.c \
		test_ft_strrchr.c test_ft_strtrim.c test_ft_substr.c test_main.c test_ft_tolower.c \
		test_ft_toupper.c

BON_OBJS = $(BONUS:.c=.o)

TEST_OBJS = $(TEST:.c=.o)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) 
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(NAME) $(BON_OBJS)
	ar rc $(NAME) $(BON_OBJS)
	ranlib $(NAME)

clean_bonus:
	rm -f $(BON_OBJS)

test: $(NAME) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(NAME) -o test

clean_test:
	rm -f $(TEST_OBJS)

fclean_test: clean_test
	rm -f test

.PHONY: all clean fclean re
