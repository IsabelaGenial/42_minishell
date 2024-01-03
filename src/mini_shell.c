/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igenial <igenial@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:06:07 by igenial           #+#    #+#             */
/*   Updated: 2024/01/03 14:06:09 by igenial          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_main	g_main;

int	main(__attribute__((unused))int argc, __attribute__((unused))char **argv,
			char **env)
{
	char	*line;

	signal_set();
	init_global();
	set_env(g_main.env_var, env);
	while (1)
	{
		line = get_line();
		if (!line)
			ft_exit2(g_main.status);
		if (ft_strlen(line) > 0)
		{
			g_main.line = line;
			lexer(&line);
			parser();
			execute_cmd_list();
			clear_token_list();
			clear_cmd_list();
			add_history(g_main.line);
		}
		ft_safe_free((void **)&line);
	}
	return (g_main.status);
}