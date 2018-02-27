COM_COLOR   = \033[1;34m
CLEAN_COLOR	= \033[1;31m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

OK_STRING    = "[OK]"
ERROR_STRING = "[ERROR]"
WARN_STRING  = "[WARNING]"
COM_STRING   = "Compiling"
CLEAN_STRING = "Cleaning"

NAME=pizza
FLAGS= -Wall -Wextra -Werror -I. -c
FLAGS= -c
LIBDIR=libft/
LIB=$(LIBDIR)libft.a
SRCS=pizza.c\
	 read.c\
	 ingr_count.c\
	 set_scopes.c\
	 sort.c\
	 error_handle.c\
	 get_next_line/get_next_line.c
OBJS=$(SRCS:%.c=%.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIB) $(PRINTF) $(OBJS)
	@gcc -o $(NAME) $(OBJS) $(LIB)> $@.log; \
        RESULT=$$?; \
        if [ $$RESULT -ne 0 ]; then \
            printf "%-20b%-40b%b" "$(COM_COLOR)$(COM_STRING)" "$(OBJ_COLOR)filler" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"; \
        elif [ -s $@.log ]; then \
            printf "%-20b%-40b%b" "$(COM_COLOR)$(COM_STRING)" "$(OBJ_COLOR)filler" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"; \
        else  \
            printf "%-20b%-40b%b" "$(COM_COLOR)$(COM_STRING)" "$(OBJ_COLOR)filler" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"; \
        fi; \
        rm -f $@.log; \
        exit $$RESULT

%.o: %.c
	@gcc $(FLAGS) $< -o $@> $@.log; \
        RESULT=$$?; \
        if [ $$RESULT -ne 0 ]; then \
            printf "%-20b%-40b%b" "$(COM_COLOR)$(COM_STRING)" "$(OBJ_COLOR)filler: $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"; \
        elif [ -s $@.log ]; then \
            printf "%-20b%-40b%b" "$(COM_COLOR)$(COM_STRING)" "$(OBJ_COLOR)filler: $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"; \
        fi; \
        rm -f $@.log; \
        exit $$RESULT

$(LIB):
	@make -C $(LIBDIR)

$(PRINTF):
	@make -C $(PRINTFDIR)

clean:
	@-rm -f $(OBJS)
	@make -C $(LIBDIR) fclean
	@printf "%-20b%b" "$(CLEAN_COLOR)$(CLEAN_STRING)" "$(OBJ_COLOR)filler$(NO_COLOR)\n"

fclean: clean
	@-rm -f $(NAME)
	@printf "%-20b%b" "$(CLEAN_COLOR)Removing" "$(OBJ_COLOR)omykolai.filler$(NO_COLOR)\n"

re: fclean all
