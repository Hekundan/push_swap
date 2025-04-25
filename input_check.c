/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:33:03 by johartma          #+#    #+#             */
/*   Updated: 2025/04/25 11:46:48 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

int	is_numeric(char *c)
{
	if (!c)
		return (-1);
	while (*c)
	{
		if (*c < '0' || *c > '9')
		{
			ft_printf("Non-Numeric Input");
			return (-1);
		}
		c++;
	}
	return (0);
}

int	is_dup(int i, int *a, int len_a)
{
	int	count;

	while (count < len_a)
	{
		if (a[count] == i)
		{
			ft_printf("Duplicated Input: %i", i);
			return (-1);
		}
	}
	return (0);
}

int *read()