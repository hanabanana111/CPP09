CXX = c++
CXX_FLAGS = -g -Wall -Wextra -Werror -std=c++98

PROGRAM_NAME = PmergeMe
SRCDIR := ./src
INCDIR := ./inc

SRC := $(SRCDIR)/main.cpp \
	   $(SRCDIR)/PmergeMe.cpp 

INCLUDES := -I$(INCDIR)

OBJDIR := obj
OBJ := $(addprefix $(OBJDIR)/, $(addsuffix .o,$(basename $(notdir $(SRC)))))

vpath %.cpp $(SRCDIR):$(CMDDIR)

all: $(PROGRAM_NAME)

$(PROGRAM_NAME): $(OBJ) $(wildcard $(INCDIR)/*.hpp) 
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -o $@ $(OBJ)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(PROGRAM_NAME)

re: fclean all

.PHONY: all clean fclean re
