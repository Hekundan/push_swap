/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:41:51 by johartma          #+#    #+#             */
/*   Updated: 2025/05/08 16:53:22 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>
#include <limits.h>

void	clear_md_arrays(int ***arrr, int n_arrays)
{
	int	count;

	count = 0;
	while (count < n_arrays)
	{
		free((*arrr)[count]);
		(*arrr)[count] = NULL;
		count++;
	}
	free(*arrr);
	*arrr = 0;
}

int	sort_ranks(t_stack *a)
{
	int				**arrs;
	int				count;
	t_stack_element	*cur;

	if (init_md_arrays(&arrs, a->stack_length, 2) == -1)
		return (-1);
	cur = a->head;
	count = 0;
	while (count < a->stack_length)
	{
		arrs[0][count] = cur->nb;
		cur = cur->next;
		count++;
	}
	sort_array_ranks(arrs, a->stack_length);
	cur = a->head;
	count = 0;
	while (count < a->stack_length)
	{
		cur->nb = arrs[1][count];
		cur = cur->next;
		count++;
	}
	clear_md_arrays(&arrs, 2);
	return (0);
}

int	init_md_arrays(int ***arrr, int len_arr, int n_arrays)
{
	int	count;

	count = 0;
	*arrr = malloc(sizeof(*arrr) * n_arrays);
	if (!*arrr)
		return (-1);
	while (count < n_arrays)
	{
		(*arrr)[count] = ft_calloc(len_arr, sizeof(int));
		if (!(*arrr)[count])
		{
			clear_md_arrays(arrr, count);
			return (-1);
		}
		count++;
	}
	return (0);
}

void	init_arrs(int **arrs, int len, t_stack_element *cur)
{
	int	count;

	count = 0;
	while (count < len)
	{
		arrs[0][count] = cur->nb;
		arrs[1][count] = 1;
		arrs[2][count] = -1;
		count++;
		cur = cur->next;
	}
}
