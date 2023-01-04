SRCFILES := main.cpp checkVector.cpp checkMap.cpp checkReverseIt.cpp##myIterator.cpp

NAME := Container

HEADERFILES := vector.hpp map.hpp pair.hpp vector.tpp reverseIterator.hpp iterator_traits.hpp

CC := c++

FLAGS := -Wall -Wextra -std=c++98 -g #-Werror

RM := rm -f

DIR_SRC := src

DIR_HEADER := src

DIR_OBJS := .objs

LST_OBJS := ${SRCFILES:.cpp=.o}

OBJS := $(addprefix $(DIR_OBJS)/,$(LST_OBJS))

##FILES := $(addprefix $(DIR_SRC)/,$(SRCFILES))

HEADER := $(addprefix $(DIR_HEADER)/,$(HEADERFILES))

all: $(DIR_OBJS) ${NAME}

${NAME}: ${OBJS}
	${CC} ${FLAGS} -o ${NAME} ${OBJS}

$(DIR_OBJS)/%.o: ${DIR_SRC}/%.cpp Makefile ${HEADER}
	${CC} ${FLAGS} -I includes -c $< -o $@


#%.cpp:

clean:
	rm -f ${OBJS}
	rmdir $(DIR_OBJS)

fclean: clean
	rm -f ${NAME}

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)

re: fclean all

.PHONY: all clean fclean re
