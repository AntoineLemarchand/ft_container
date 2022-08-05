#------------------------------------------------------------------------------#
#                         EDIT THIS BLOCK                                      #
#------------------------------------------------------------------------------#

NAME			= 	compare_containers

# src definition
SRCDIR			= 	srcs/
# this is to define which compiler to use
SRCTYPE			=	.cpp
SRCFILES		=	unitTest main

INCDIR			= includes includes/vector includes/stack includes/map

RM				= rm -f

ADDFLAGS		=

#------------------------------------------------------------------------------#
#                         DO NOT EDIT BELOW THIS LINE                          #
#------------------------------------------------------------------------------#

define	header
	@printf "\e[38;5;2m┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
	@printf "┃ \e[38;5;12m $1\n"
	@printf "\e[38;5;2m┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
	@printf "\e[38;5;15m"
endef

define	subheader
	@printf "\e[38;5;5m$1\n"
	@printf "\e[38;5;15m"
endef

#------------------------------------------------------------------------------#
#                         UTILS PART				                           #
#------------------------------------------------------------------------------#

OBJS			= $(SRC:$(SRCTYPE)=.o)
SRC				= $(addsuffix $(SRCTYPE), $(addprefix $(SRCDIR), $(SRCFILES)))
INC				= $(addprefix -I, $(INCDIR))

CXX				= $(if $(filter-out .cpp, $(SRCTYPE)), cc, c++)
CXXFLAGS		= -Wall -Wextra -Werror -g
CXXFLAGS		+= $(if $(filter-out .cpp, $(SRCTYPE)),, -std=c++98)
CXXFLAGS		+= $(ADDFLAGS)

%.o : %$(SRCTYPE)
				$(call subheader,building $<)
				$(CXX) $(CXXFLAGS) $(INC) -c $< -o $(<:.cpp=.o)

${NAME}:		$(OBJS)
				$(call header, building $(NAME))
				$(CXX) $(CXXFLAGS) $(INC) $(OBJS) -o $(NAME) $(LIBS)

all:			$(NAME)

clean:	
				$(call subheader,removing .o files)
				$(RM) $(OBJS)

fclean:			clean
				$(call subheader,removing $(NAME))
				$(RM) $(NAME)

re:				fclean all
