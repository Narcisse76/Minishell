/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abignals <abignals@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:04:22 by abignals          #+#    #+#             */
/*   Updated: 2025/10/27 17:55:17 by abignals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_data(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	data->env = malloc(sizeof(char *) * (i + 1));
	if (!data->env)
	{
		perror("malloc");
		exit(1);
	}
	i = -1;
	while (envp[++i])
	{
		data->env[i] = ft_strdup(envp[i]);
		if (!data->env[i])
		{
			perror("strdup");
			exit(1);
		}
	}
	data->env[i] = NULL;
	data->cmd = NULL;
	data->exit_code = 0;
	increment_shlvl(data);
}

static void	run_shell(t_data *data)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			data->cmd = parsing(line, data);
			if (data->cmd)
			{
				exec(data);
				free_cmd(data->cmd);
				data->cmd = NULL;
			}
		}
		free(line);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	setup_signals_interactive();
	init_data(data, env);
	run_shell(data);
	free_env(data->env);
	free(data);
	return (0);
}
//norme
