.PHONY: all clean fclean re libft

# ------ COLORS ------

_END			= \033[0m
_GREY			= \033[0;30m
_RED			= \033[0;31m
_GREEN			= \033[0;32m
_YELLOW			= \033[0;33m
_BLUE			= \033[0;34m
_PURPLE			= \033[0;35m
_CYAN			= \033[0;36m
_BOLD			= \e[1m


# ------ VARIABLES ------

NAME			= Minitalk
NAME_C			= client
NAME_S			= server
CC				= cc
AR				= ar -rcs
CFLAGS			= -Wall -Wextra -Werror

# ------ PATHS ------

P_OBJ 			= obj/
P_SRC 			= src/
P_INC			= includes/
P_LIB			= libft/

# ------ FILES ------

CLIENT			= client

SERVER			= server

HDR_SRC			= libft					minitalk

SRC_CLIENT		= $(addprefix $(P_SRC), $(addsuffix .c, $(CLIENT)))
SRC_SERVER		= $(addprefix $(P_SRC), $(addsuffix .c, $(SERVER)))

HEADERS			= $(addprefix $(P_INC), $(addsuffix .h, $(HDR_SRC)))
LIBFT			= $(P_LIB)libft.a

# ------ RULES ------

all: 			libft $(NAME_C) $(NAME_S)
#				@echo -n "$(_CYAN)$(_BOLD)]$(_END)"
#				@echo "$(_GREEN)$(_BOLD) => $(NAME) compiled!$(_END)"

$(NAME_C): 		$(SRC_CLIENT) Makefile $(HEADERS)
				@$(CC) $(CFLAGS) -I $(P_INC) $(SRC_CLIENT) $(LIBFT) -o $@
				@echo "$(_YELLOW)Compiling $(SRC_CLIENT)$(_END)"
				@echo "$(_GREEN)$(_BOLD)=> $(NAME_C) compiled!$(_END)"

$(NAME_S): 		$(SRC_SERVER) Makefile $(HEADERS)
				@$(CC) $(CFLAGS) -I $(P_INC) $(SRC_SERVER) $(LIBFT) -o $@
				@echo "$(_YELLOW)Compiling $(SRC_SERVER)$(_END)"
				@echo "$(_GREEN)$(_BOLD)=> $(NAME_S) compiled!$(_END)"

libft:		
				@$(MAKE) -C $(P_LIB) --no-print-directory
#				@echo -n "$(_CYAN)$(_BOLD)[$(_END)"

# ------ BASIC RULES ------

clean: 
				@rm -rf $(P_OBJ)
				@$(MAKE) -C $(P_LIB) clean --no-print-directory
				@echo "$(_CYAN)$(NAME) cleaned!$(_END)"

fclean:
				@$(MAKE) clean --no-print-directory
				@$(MAKE) -C $(P_LIB) fclean --no-print-directory
				@rm -rf $(LIBFT)
				@rm -rf $(NAME_C)
				@rm -rf $(NAME_S)
				@echo "$(_CYAN)$(NAME) full cleaned!$(_END)"

re:
				@$(MAKE) fclean --no-print-directory
				@$(MAKE) all --no-print-directory
