NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

# Source files
SRCS		= src/exec/main.c \
			  src/exec/exec.c \
			  src/exec/exec_cmd.c \
			  src/exec/exec_pipeline.c \
			  src/exec/exec_heredoc.c \
			  src/exec/exec_redir.c \
			  src/exec/exec_utils.c \
			  src/parsing/split.c \
			  src/parsing/split_check.c \
			  src/parsing/split_special.c \
			  src/parsing/split_quotes.c \
			  src/parsing/split_extract.c \
			  src/parsing/tokenization.c \
			  src/parsing/parse_cmd.c \
			  src/parsing/parse_args.c \
			  src/parsing/parse_redir.c \
			  src/parsing/parse_expand.c \
			  src/parsing/expand_utils.c \
			  src/parsing/expand_size.c \
			  src/parsing/expand_var.c \
			  src/parsing/expand_quotes.c \
			  src/parsing/syntax_check.c \
			  src/parsing/parse_utils.c \
			  src/utils/gb_malloc.c \
			  src/utils/signals.c \
			  src/utils/signal2.c \
			  src/utils/env_utils.c \
			  src/builtins/builtins.c \
			  src/builtins/builtins_basic.c \
			  src/builtins/builtins_exit.c \
			  src/builtins/cd.c \
			  src/builtins/export.c \
			  src/builtins/export2.c \
			  src/builtins/unset.c \
			  src/builtins/builtin_utils.c \
			  src/parsing/syntax_check_utils.c

OBJS		= $(SRCS:.c=.o)

# Includes & Libraries
INCLUDES	= -I includes -I includes/libft
LIBFT		= includes/libft/libft.a
LIBS		= $(LIBFT) -lreadline

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "✓ Minishell compiled successfully!"

%.o: %.c
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C includes/libft --no-print-directory

clean:
	@$(RM) $(OBJS)
	@$(MAKE) clean -C includes/libft --no-print-directory
	@echo "✓ Object files removed"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C includes/libft --no-print-directory
	@echo "✓ Executable removed"

re: fclean all

.PHONY: all clean fclean re
