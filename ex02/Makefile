############################################################
#                                                          #
#   ██████╗ ██████╗ ███╗   ██╗                             #
#   ██╔══██╗╚════██╗████╗  ██║                             #
#   ██████╔╝ █████╔╝██╔██╗ ██║                             #
#   ██╔══██╗██╔═══╝ ██║╚██╗██║                             #
#   ██████╔╝███████╗██║ ╚████║                             #
#   ╚═════╝ ╚══════╝╚═╝  ╚═══╝                             #
#                                                          #
#   File    : Makefile                                     #
#   Created : 2026-01-30 17:16                             #
#   Updated : 2026-01-30 17:16                             #
#                                                          #
############################################################

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = PmergeMe.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)
NAME = PmergeMe

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
