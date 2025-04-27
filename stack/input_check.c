/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:33:03 by johartma          #+#    #+#             */
/*   Updated: 2025/04/27 09:19:11 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdlib.h>
#include <limits.h> 

static int	is_whitespace(char c)
{
	if (((c >= 9) && (c <= 13)) || (c == 32))
		return (1);
	else
		return (0);
}

static long long	ft_atoll(const char *str)
{
	long long	to_rtrn;
	int			sign;

	to_rtrn = 0;
	sign = 1;
	while (is_whitespace(*str) == 1)
		str++;
	if ((*str == '-') || (*str == '+'))
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while ((*str >= '0') && (*str <= '9'))
	{
		to_rtrn *= 10;
		to_rtrn += (*str - '0');
		str++;
	}
	to_rtrn *= sign;
	return (to_rtrn);
}

static int	is_overflow(char *s)
{
	long long	v;

	v = ft_atoll(s);
	if (v < INT_MIN || v > INT_MAX)
	{
		ft_printf("Overflow\n");
		return (1);
	}
	return (0);
}

static int	is_not_numeric(char *c)
{
	if (!c)
		return (-1);
	while (*c)
	{
		if (*c < '0' || *c > '9')
		{
			ft_printf("Non-Numeric Input\n");
			return (1);
		}
		c++;
	}
	return (0);
}

static int	is_dup(int i, int *a, int len_a)
{
	int	count;

	count = 0;
	while (count < len_a)
	{
		if (a[count] == i)
		{
			ft_printf("Duplicated Input: %i", i);
			return (1);
		}
		count++;
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
		if (is_not_numeric(args[count]) || is_dup(num, a, count - 1) ||
			is_overflow(args[count]))
		{
			free(a);
			return (NULL);
		}
		a[count-1] = num;
		count++;
	}
	return (a);
}
