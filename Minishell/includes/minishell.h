/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abignals <abignals@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:02:45 by abignals          #+#    #+#             */
/*   Updated: 2025/10/27 17:26:49 by abignals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <string.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef enum e_token
{
	T_INVALID = -1,
	T_WORD = 0,
	T_REDIR_OUT = 1,
	T_REDIR_IN = 2,
	T_PIPE = 3,
	T_HEREDOC = 4,
	T_APPEND = 5,
	T_EOF = 6
}	t_token_type;

typedef struct s_quote_state
{
	int	in_squote;
	int	in_dquote;
}	t_quote_state;

typedef struct s_expand_qctx
{
	char			*str;
	char			*result;
	int				*i;
	int				*j;
	t_quote_state	*qs;
}	t_expand_qctx;

typedef struct s_token
{
	char	**words;
	int		*type;
	int		size;
}	t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	int				fd;
	int				expand_heredoc;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_gb_collector
{
	void					*data;
	struct s_gb_collector	*next;
}	t_gb_collector;

typedef struct s_data
{
	char	**env;
	t_cmd	*cmd;
	int		exit_code;
}	t_data;
// split.c
int		in_quotes(char c, int *quote_state);
int		is_whitespace(char c);
int		is_char(char c, int quote_state);
int		is_pipe(char c);
int		is_redir_out(char c);
int		is_redir_in(char c);
int		is_heredoc(char *str, int *i);
int		is_happend(char *str, int *i);
int		is_eof(char c);
int		is_special(char *str, int *i);
int		is_special_test(char *str, int i);
int		count_words(char *str);
char	*extract_special(char *str, int *len);
char	*extract_word(char *str, int *len);
char	*remove_quotes(char *str);
void	free_split(char **split);
char	**split(char *str);

// expand.c
char	*extract_var_name(char *str, int *len);
char	*get_var_value(char *var_name, t_data *data);
int		calculate_expanded_size(char *str, t_data *data);
char	*expand_variables(char *str, t_data *data);
int		should_expand(char *original_str, int pos);
char	*expand_with_quotes(char *str, t_data *data);

// tokenziation
t_token	*tokenize(char **args);
void	print_tokens(t_token *tokens);

//parse
void	free_redir(t_redir *redir);
void	free_cmd(t_cmd *cmd);
void	free_tokens(t_token *tokens);
void	cleanup_all(t_data *data);
t_cmd	*parse(t_token *tokens);
t_cmd	*parse_command(t_token *tokens, int *i);
char	**extract_args(t_token *tokens, int *i);
int		count_args(t_token *tokens, int start);
void	add_redir(t_cmd *cmd, t_redir *new_redir);
t_redir	*create_redir(t_token_type type, char *file);
t_cmd	*create_cmd(void);
t_cmd	*parsing(char *str, t_data *data);
void	exec(t_data *data);
void	exec_cmd(t_cmd *cmd, t_data *data);
void	exec_pipeline(t_data *data);
int		handle_heredoc(char *delimiter, int expand, t_data *data);
void	setup_redirections(t_cmd *cmd, t_data *data);
char	*join_path(char *dir, char *cmd);
char	*find_command_path(char *cmd, char **env);
int		count_cmds(t_cmd *cmd);

// builtins
int		is_builtin(char *cmd);
int		exec_builtin(t_cmd *cmd, t_data *data);
int		builtin_echo(char **args);
int		builtin_cd(char **args, t_data *data);
int		builtin_pwd(void);
int		builtin_export(char **args, t_data *data);
int		builtin_unset(char **args, t_data *data);
int		builtin_env(char **env);
int		builtin_exit(char **args, t_data *data);

// builtin_utils
char	*get_env_value(char **env, char *key);
char	**copy_env(char **env);
void	free_env(char **env);

// export utils
int		count_env(char **env);
int		find_env_index(char **env, char *key);
int		add_or_update_env(t_data *data, char *var);
int		is_valid_identifier(char *str);
void	print_export(char **env);

// syntax_check.c
int		is_operator(t_token_type type);
int		is_redirection(t_token_type type);
void	syntax_error(char *token);
int		check_syntax(t_token *tokens);
int		check_quotes(char *line);

// signals.c
void	handle_sigint_interactive(int sig);
void	handle_sigint_execution(int sig);
void	handle_sigquit_execution(int sig);
void	setup_signals_interactive(void);
void	setup_signals_execution(void);
void	setup_signals_default(void);

// env_utils.c
void	increment_shlvl(t_data *data);

#endif
