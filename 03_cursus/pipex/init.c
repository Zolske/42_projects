/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:55:25 by zkepes            #+#    #+#             */
/*   Updated: 2024/03/18 16:47:38 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*initialize structure with values*/
void	init_data_null(t_data *d, char **argv, int argc)
{
	d->in_fl = argv[1];
	d->out_fl = argv[argc -1];
	d->cmd_arg = NULL;
	d->cmd_path = NULL;
	d->pipes = NULL;
	// d->pid = NULL;
	if ( 0 == ft_strncmp(argv[1], "here_doc", 9))
	{
		d->read_cl = true;
		d->limiter = argv[2];
		d->n_cmd = argc - 4;
		d->offset = 3;
	}
	else
	{
		d->read_cl = false;
		d->limiter = NULL;
		d->n_cmd = argc - 3;
		d->offset = 2;
	}
}

/*set the values for "cmd_arg" and NULL terminate it for "execve()"*/
void	set_cmd_arg(t_data *d, char **argv)
{
	int		cmd;
	int		arg;
	char	**tab_arg;

	cmd = 0;
	d->cmd_arg = (char ***) malloc(sizeof(char **) * d->n_cmd + 1);
	e_ptr3_mal_exit(d->cmd_arg, d, "set_cmd_arg()/cmd_arg");
	while (cmd < d->n_cmd)
	{
		tab_arg = ft_split(argv[cmd + d->offset], ' ');
		e_ptr2_mal_exit(tab_arg, d, "set_cmd_arg()/tab_arg");
		d->cmd_arg[cmd] = (char**) malloc(sizeof(char*) * tab_len(tab_arg) + 1);
		e_ptr2_2x_mal_exit(d->cmd_arg[cmd], tab_arg, d,
		"set_cmd_arg()/d->cmd_arg[cmd]");
		arg = 0;
		while (tab_arg[arg])
		{
			d->cmd_arg[cmd][arg] = tab_arg[arg];
			arg++;
		}
		d->cmd_arg[cmd][arg] = NULL;
		free(tab_arg);
		tab_arg = NULL;
		cmd++;
	}
	d->cmd_arg[cmd] = NULL;
}

/*test which "path + command" passes access(), saves the correct one*/
void	set_cmd_path(char *envp[], t_data *d)
{
	char **tab_env;
	int	cmd;

	tab_env = init_env_path(envp);
	cmd = 0;
	d->cmd_path = (char **)malloc(sizeof(char *) * d->n_cmd + 1);
	e_ptr2_mal_exit(d->cmd_path, d, "set_cmd_path/d->cmd_path");
	while (cmd < d->n_cmd)
	{
		d->cmd_path[cmd] = get_command_path(d->cmd_arg[cmd][0], tab_env, envp);
		cmd++;
	}
	d->cmd_path[cmd] = NULL;
	free_tab(tab_env);
}

/*create for each command one pipe + one extra*/
void	set_pipes(t_data *d)
{
	int	idx;

	idx = 0;
	d->pipes = (int **) malloc(sizeof(int *) * d->n_cmd + 1);
	while (idx <= d->n_cmd)
	{
		d->pipes[idx] = (int *) malloc(sizeof(int) * 2);
		pipe(d->pipes[idx]);
		idx++;
	}
}
