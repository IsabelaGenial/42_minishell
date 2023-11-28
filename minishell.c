/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igenial <igenial@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:53:55 by igenial           #+#    #+#             */
/*   Updated: 2023/11/28 17:49:01 by igenial          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (void)
{
	char *input;

	while(369)
	{
		ft_printf("$>");
		input = get_next_line(2);
		handler_input(input);
	}
	return (0);
}
