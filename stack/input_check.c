/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:33:03 by johartma          #+#    #+#             */
/*   Updated: 2025/05/08 20:30:48 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <limits.h> 

static int	is_not_numeric(char *c)
{
	if (!c)
		return (-1);
	if (*c == '+' || *c == '-')
		c++;
	if (!*c)
		return (-1);
	while (*c)
	{
		if (*c < '0' || *c > '9')
			return (1);
		c++;
	}
	return (0);
}

int	*read_separate(int arr_len, char *args[])
{
	int		count;
	int		*a;
	int		num;

	count = 1;
	a = malloc(sizeof(int) * arr_len);
	if (!a)
		return (NULL);
	while (count < arr_len + 1)
	{
		num = ft_atoi(args[count]);
		if (is_not_numeric(args[count]) || is_dup(num, a, count - 1)
			|| is_overflow(args[count]))
		{
			free(a);
			return (NULL);
		}
		a[count - 1] = num;
		count++;
	}
	return (a);
}

static void	free_split(char **arr_strs, size_t words_allocated)
{
	size_t	i;

	i = 0;
	while (i < words_allocated)
	{
		free(arr_strs[i]);
		i++;
	}
	if (arr_strs)
		free(arr_strs);
}

int	*read_combined(int *arr_len, char *arg)
{
	char	**splited;
	int		count;
	int		*a;
	int		num;

	count = 0;
	splited = ft_split(arg, ' ');
	*arr_len = 0;
	while (splited && splited[*arr_len])
		(*arr_len)++;
	a = malloc(sizeof(int) * *arr_len);
	while (a && count < *arr_len)
	{
		num = ft_atoi(splited[count]);
		if (is_not_numeric(splited[count]) || is_dup(num, a, count)
			|| is_overflow(splited[count]))
			break ;
		a[count++] = num;
	}
	free_split(splited, *arr_len);
	if ((count == (*arr_len)++ && count > 0) || !a)
		return (a);
	free(a);
	return (NULL);
}

int	*read_to_arr(int *argc, char *argv[])
{
	int	arr_len;

	arr_len = *argc - 1;
	if (arr_len < 1)
		return (NULL);
	if (*argc == 2)
		return (read_combined(argc, argv[1]));
	else
		return (read_separate(arr_len, argv));
}
