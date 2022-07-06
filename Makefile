NAME	= program

SRC		=	main.cpp

OBJ		= $(SRC:.cpp=.o)

HEADR	=	my_containers/other_tools/iterators_traits.hpp\
			my_containers/other_tools/reverse_iterator.hpp

CC		= c++

CFLAGS	= -Wall -Wextra -Werror -std=c++98

all		: $(NAME)

$(NAME)	: $(OBJ) $(HEADR)
		$(CC) $(CFAGS) $(OBJ) -o $(NAME)

.cpp.o	: $(HEADR)
		$(CC) $(CFLAGS) -c $< -o $@

clean	:
		rm -f $(OBJ)

fclean	: clean
		rm -f $(NAME)

re		: fclean all

.PHONY	: clean fclean re all