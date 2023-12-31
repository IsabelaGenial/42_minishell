/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rseelaen <rseelaen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:46:07 by rseelaen          #+#    #+#             */
/*   Updated: 2023/12/18 14:23:08 by rseelaen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define TABLE_SIZE 256
# define FALSE 0
# define TRUE 1

enum    e_my_error
{
        QUOTE,
        NOT_DIR,
        NOT_PARM,
        NOT_CMD,
        FORK_ERROR,
        PIPE_ERROR,
        PIPE_ND_ERROR,
        IS_DIR,
};
typedef enum s_token_type
{
	WORD,
	APPEND,
	HEREDOC,
	OUTFILE,
	INFILE,
	AND,
	OR,
	PIPE
}	t_token_type;

typedef enum s_builtin
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_builtin;

//--Structs--//
//Token list

typedef struct s_token
{
	char			*name;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

//Command list

typedef struct s_cmd
{
	char			*name;
	char			**args;
	int				argc;
	int				redir;
	int				fd_in;
	int				fd_out;
	int				type;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

//Cmd_info

typedef struct s_cmd_info
{
	char	*path;
	int		heredoc;
	int		heredoc_count;
	int		infile;
	int		outfile;
	int		append;
	int		pipe;
	int		pipe_count;
}	t_cmd_info;

//Hashtable

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

//Main

typedef struct s_main
{
	t_env		*env_var[TABLE_SIZE];
	t_token		*token_list;
	t_cmd		*cmd_list;
	t_cmd_info	cmd_info;
	char		*line;
	int			open_quote;
	int			status;
	int			is_heredoc_running;
}	t_main;


//Global variable

extern t_main	g_main;

//EXIT------------------------------------------
//exit.c

void	ft_exit(char **args, int argc);
void	ft_exit2(int status);

//INIT------------------------------------------
//init.c

void	init_hashtable(t_env **env_var);
void	init_global(void);

//SIGNALS---------------------------------------
//signal.c

int		signal_set(void);

//PARSER----------------------------------------
//lexer.c

int		lexer(char **str);

//tokenizer.c

char	*tokenizer(char *str);
int		check_quote(int quote, char c);

//token_utils.c

void	clear_token_list(void);
void	add_token(char *name, int type);
t_token	*new_token(char *name, int type);

//cmd_list.c

void	create_cmd_list(void);
void	clear_cmd_list(void);

//cmd_list_utils.c

t_cmd	*new_cmd(char *name, int type);
void	add_cmd(t_cmd *cmd);
void	clear_cmd_list(void);
void	print_cmd_list(void); //test function

//expand_var.c

char	*expand_var(char *name);
char	*expand_var2(char *str, int i);

//parser.c

int		parser(void);

//EXEC------------------------------------------
//builtin.c

int		exec_builtin(char *name, char **args, int argc);

//execute.c

void	execute_cmd_list(void);
char	*check_path(char *name);
void	exec(t_cmd *cmd, char *path);
int		check_if_builtin(char *name);

//BUILTINS--------------------------------------
//export.c

int		ft_export(char **args, int argc);

//echo.c

int		ft_echo(char **args, int fd);

//cd.c

int		ft_cd(char **args);

//HASHTABLE-------------------------------------
//hashtable.c

int		hash(char *key);
int		update_key(t_env **env_var, char *key, char *value);
t_env	*search(t_env **env_var, char *key);
char	*search_value(t_env **env_var, char *key);
void	clear_hashtable(t_env **env_var);
void	delete_key(t_env **env_var, char *key);
void	insert_key(t_env **env_var, char *key, char *value);

//ENV-------------------------------------------
//set_env.c

int		set_env(t_env **env_var, char **env);
int		free_tab(char **tab);

//HEREDOC---------------------------------------
//heredoc.c

char	*heredoc(char *delimiter);

//------------------TEST FUNCTIONS-----------------------
//------------------TEST FUNCTIONS-----------------------
void	print_hashtable(t_env **env_var);

#endif //SHELL_H