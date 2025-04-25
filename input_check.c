/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:33:03 by johartma          #+#    #+#             */
/*   Updated: 2025/04/25 13:36:06 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

static int	is_not_numeric(char *c)
{
	if (!c)
		return (-1);
	while (*c)
	{
		if (*c < '0' || *c > '9')
		{
			ft_printf("Non-Numeric Input");
			return (1);
		}
		c++;
	}
	return (1);
}

static int	is_dup(int i, int *a, int len_a)
{
	int	count;

	while (count < len_a)
	{
		if (a[count] == i)
		{
			ft_printf("Duplicated Input: %i", i);
			return (1);
		}
	}
	return (0);
}

int	*read_to_arr(int arr_len, char *args[])
{
	int		count;
	int		*a;
	int		num;

	count = 1;
	a = malloc(sizeof(int) * arr_len);
	if (!a)
		return (NULL);
	while (count < arr_len)
	{
		num = ft_atoi(args[count]);
		if (is_not_numeric(args[count]) || is_dup(num, a, count - 1))
		{
			free(a);
			return (NULL);
		}
		a[count] = num;
	}
	return (a);
}
