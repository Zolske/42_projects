/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkepes <zkepes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:01:25 by zkepes            #+#    #+#             */
/*   Updated: 2024/03/18 12:21:00 by zkepes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_all(t_data *d)
{
	free_cmd_arg(d);
	free_path(d);
}

void	free_cmd_arg(t_data *d)
{
	int	cmd;
	int	arg;

	cmd = 0;
	if (d->cmd_arg)
	{
		while (d->cmd_arg[cmd])
		{
			arg = 0;
			while (d->cmd_arg[cmd][arg])
			{
				free(d->cmd_arg[cmd][arg]);
				d->cmd_arg[cmd][arg] = NULL;
				arg++;
			}
			free(d->cmd_arg[cmd]);
			d->cmd_arg[cmd] = NULL;
			cmd++;
		}
		free(d->cmd_arg);
		d->cmd_arg = NULL;
		cmd = 0;
	}
}

void	free_path(t_data *d)
{
	int	cmd;

	cmd = 0;
	if (d->cmd_path)
	{
		while (d->cmd_path[cmd])
		{
			free(d->cmd_path[cmd]);
			d->cmd_path[cmd] = NULL;
			cmd++;
		}
		free(d->cmd_path);
		d->cmd_path = NULL;
	}
}

void	free_tab(char **tab)
{
	int	idx;

	idx = 0;
	while (tab[idx])
	{
		free(tab[idx]);
		tab[idx] = NULL;
		idx++;
	}
	free(tab);
	tab = NULL;
}
