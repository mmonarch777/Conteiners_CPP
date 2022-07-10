NAME	= program

SRC		=	main.cpp

OBJ		= $(SRC:.cpp=.o)

HEADR	=	other_tools/iterators_traits.hpp\
			other_tools/reverse_iterator.hpp\
			other_tools/lexicographical_compare.hpp\
			other_tools/equal.hpp\
			vector/vector.hpp\
			vector/vector_iterator.hpp

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