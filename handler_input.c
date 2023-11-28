/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igenial <igenial@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:26:37 by igenial           #+#    #+#             */
/*   Updated: 2023/11/28 18:40:41 by igenial          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handler_input(char *input)
{
	if (!ft_strncmp(input, "history", 10))
		ft_printf("Have a working history\n");
	else if (*input == '\'')
		ft_printf("Handle ’ (single quote)\n");
	else if (*input == '\"')
		ft_printf("Handle (double quote)\n");
}
