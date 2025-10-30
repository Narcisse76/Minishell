/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abignals <abignals@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:56:05 by abignals          #+#    #+#             */
/*   Updated: 2025/10/27 16:56:19 by abignals         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_sigint_interactive(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_execution(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	handle_sigquit_execution(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit (core dumped)\n", 2);
}
