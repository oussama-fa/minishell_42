/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:48:22 by oufarah           #+#    #+#             */
/*   Updated: 2025/06/24 22:05:00 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>

# define SINGLE 20
# define COUPLE 10
# define RED_OUT 30
# define RED_IN 31
# define APPE 32
# define HERED 33
# define ALLOC 1
# define CLEAR 2

typedef struct s_garbage
{
	void				*address;
	struct s_garbage	*next;

}	t_garbage;

typedef enum e_tokentype {
	WORD,
	PIPE,
	R_IN,
	R_OUT,
	APPEND,
	HERDOC,
	DOUBLEQ,
	SINGLEQ,
	DELEMTER,
	EXPAN,
	R_FILE,
}	t_tokentype;

typedef struct s_expand
{
	bool	s_q;
	bool	d_q;
	int		i;
	int		b;
	char	*c;
}	t_expand;

typedef struct s_env {
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token {
	t_tokentype		type;
	char			*value;
	struct s_token	*next;
	struct s_token	*previous;
	int				fd_reder;
	int				heredoc_expn;
	int				ambg;
	int				removed;
}	t_token;

typedef struct s_exec
{
	int				fd_in;
	int				fd_out;
	char			*cmd;
	char			**opt;
	struct s_exec	*next;
	int				flag;			
}	t_exec;

typedef struct s_main_ctx
{
	char	*input;
	char	*expn;
	t_token	*lst;
	t_exec	*exec;
	t_env	*envp;
}	t_main_ctx;

typedef struct s_expand_ctx
{
	char		*nv;
	char		*sub;
	int			b_x;
	bool		r;
	int			i;
	t_expand	e;
	t_env		*envp;
	char		*s;
}	t_expand_ctx;

typedef struct s_heredoc_ctx
{
	char	*f;
	int		fd_out;
	int		fd_in;
	int		st;
}	t_heredoc_ctx;

typedef struct s_cut
{
	t_token	*tmp;
	int		pip_i;
}	t_cut;

typedef struct s_spli_cmd
{
	char		*cmd;
	t_tokentype	type;
	int			j;
}	t_spli_cmd;

typedef enum s_vartype
{
	WORD_V,
	VAR,
}	t_vartype;

typedef struct s_var
{
	char			*value;
	struct s_var	*next;
	t_vartype		type;
}	t_var;

void		skip_till_pipe(t_token **lst);
void		skip_s(char *s, int *i);
char		*remove_q(char *tmp);
int			check_pip(char *s, int *i);
void		init_expan(t_expand_ctx *ctx, char *s, t_env *envp);
int			skip_spaces(char *s, int i);
void		ft_split_expanded(char *val, t_token **lst, t_env *env);
char		**a_split(char *s);
int			check_for_s(char	*string);
char		*g_env(char *value, t_env *envp);
int			ft_check_quotes_type(char *string);
int			ft_check_quots(char *command);
size_t		ft_strlen(char *str);
int			ft_parse_command(char *string);
char		*strj(char *s1, char *s2);
void		ft_syntax_error(void);
char		*subs(char *s, unsigned int start, size_t len);
t_token		*s_cmd(char **command, t_env *envp);
char		*ft_strchr( char *s, int c);
void		ft_lstnew(t_token **lst, t_spli_cmd s, t_env *e, int r);
t_token		*ft_lstlast(t_token *lst);
void		ft_lstadd_back(t_token **lst, t_token *new);
int			ft_is_space(char c);
char		**ft_split(char *s);
int			ft_is_space(char c);
bool		ft_check_pip(char *string);
bool		ft_check_redirect_in(char *string);
bool		ft_check_redirect_out(char *string);
bool		ft_check_append(char *string);
t_tokentype	ft_token_type(t_token *lst, char *string);
int			ft_check_var(char	*s);
char		*ft_strdup(char *src);
bool		ft_check_heredoc(char *string);
size_t		ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t		ft_strlcat(char *s1, char *s2, size_t n);
int			skip_variable(char *value, int index);
int			ft_expand(t_token *lst, t_env *envp);
int			ft_handle_heredoc(t_token *lst, t_env *env, int fd_out);
char		*exp_val(char *value, t_env *envp);
int			ft_check_braces(char *string);
int			ft_stop_redirect(t_token *lst, t_env *envp);
void		handler(int sig);
bool		should_expand(char *s, t_expand e);
int			delimter(char *s, size_t index);
bool		is_invalid_dollar_after_op(t_expand_ctx *c);
void		ambigous_red(void);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isdigit(int c);
int			id_check(char *var);
int			recevied_from_inp(int set, int st);
int			check_case_rp(char *string, int *i);
void		default_sig(void);
void		child_sig(char	*cmd);
size_t		skip_tillvar(char *val, size_t i);
int			check_type_exp(t_tokentype type);
int			dollar_case(char *string);
int			check_env(char *value, t_env *e);
int			ft_count_operator(char *string, int index, char c);
t_var		*s_var(char *s);
void		signal_heredoc(int sig);
int			handle_redirects(t_token **lst, t_exec *node);
// garbage
void		*ft_malloc(size_t size, int flag);
//builtins
char		**convert_t_env(t_env *env);
int			is_builtin(char *cmd);
void		execute_builtin(t_exec *exec, t_env **env, bool forked);
// cd
void		getcwd_fail(char *path, t_env **env, char **hold_pwd, char *newpwd);
void		update_oldpwd(t_env **env, char *oldpwd);
int			change_dir(char *path, t_env **env, char **hold_pwd);
char		*ft_cd(char **opt, t_env **env);
//echo
int			is_valid_option(char *str);
int			ft_echo(char **cmd, int fd);
//env
void		init_default_env(t_env **env, char *pwd);
t_env		*init_env(char **envp);
char		*get_env_value(t_env **env, char *path);
t_env		*find_env(t_env	*env, char *key);
int			ft_env(t_env *env, int fd);
// exec_child
int			check_exit_status(pid_t last_pid);
void		cmd_not_found(char *cmd);
int			parent_thing(int *fd, t_exec *head);
void		setup_child(int *fd, t_env *path, t_exec *head, int bltn);
// exec_list
int			ft_lstsize_env(t_env *env);
t_exec		*new_node(void);
void		ft_lstadd_back_exec(t_env **lst, t_env *new);
int			ignore_first_cmd(int res, int get);
// exec main
void		call_execve(t_exec *head, t_env *env);
void		in_child(t_exec *head, t_env **env, int *fd);
pid_t		execute_cmd(t_exec *head, t_env **env);
int			execution(t_exec *exec, t_env **env);
//exec_more_list
t_env		*ft_lstlast_exec(t_env *lst);
int			ft_lstsize(t_exec *exec);
void		add_back(t_exec **head, t_exec *new);
t_env		*ft_lstnew_exec(char *key, char *value);
//  exec_utils
void		ft_putstr_fd(char *s, int fd);
int			ft_strncmp(char *s1, char *s2, size_t n);
char		*ft_strstr(char *str, char *to_find);
char		*ft_strdup2(char *src);
int			is_empty(char *s);
// exit
void		ambigous_red(void);
int			e_status(int sts, int set);
int			is_valid_exit(char	*opt);
void		err_num(char *opt);
int			ft_exec_exit(char **opt, bool forked);
// export more
int			is_valid_export(char *opt);
void		swap_env(t_env *a, t_env *b);
void		bubble_sort_env(t_env *env);
void		print_sorted_env(t_env *env, int fd);
// export
void		handle_plus_equal(char *opt, t_env **env);
void		handle_equal_or_none(char *opt, t_env **env);
void		err_identifier(char *opt);
int			ft_export(char **opt, t_env **env, int fd);
//find_cmd_path
char		*search_cmd_in_path(char **arr, char *cmd);
char		*get_cmd_path(char *cmd, char *path);
// ft_itoa_atoi
char		*ft_itoa(int n);
int			ft_atoi(const char *str, int *flag);
// ft_split_exec
char		**ft_split_exec(char const *s, char c);
//parse_to_exec_more
int			init_heredoc_ctx(t_heredoc_ctx *ctx, t_token **lst);
int			handle_heredoc(t_token *lst, t_env *env);
int			handle_redirect_in(t_token **lst, t_exec *node);
int			handle_append(t_token **lst, t_exec *node);
int			handle_redirect_out(t_token **lst, t_exec *node);
//parse_to_exec
int			count_until_pipe(t_token *lst);
void		handle_word(t_token *lst, t_exec *node, int *i);
int			handle_redirects(t_token **lst, t_exec *node);
int			fill_node(t_token **lst, t_exec *node);
t_exec		*convert_token_to_exec(t_token *lst, t_env *env);
// pwd
int			pwd_and_oldpwd(t_env *env, int fd);
int			ft_pwd(t_env *env, int fd);
//unset
void		delet_node(t_env **env, char *key);
void		ft_unset(char **opt, t_env **env);
// in parse but used in exec
int			ft_strcmp(char *s1, char *s2);
void		handler(int sig);
char		*ft_remove_quotes(t_expand_ctx *c, char *tmp);
int			delimter(char *s, size_t index);
bool		handle_quotes(char *s, t_expand *e);
char		*remove_q(char *tmp);

#endif