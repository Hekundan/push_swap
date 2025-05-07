/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:41:51 by johartma          #+#    #+#             */
/*   Updated: 2025/05/07 16:24:01 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "push_swap.h"

static void	clear_md_arrays(int ***arrr, int n_arrays)
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

static int	init_md_arrays(int ***arrr, int len_arr, int n_arrays)
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

static int	lis_core(int **arrs, int len)
{
	int	lol[4];

	lol[0] = 0;
	lol[2] = 0;
	while (lol[0] < len)
	{
		lol[1] = 0;
		while (lol[1] < lol[0])
		{
			if ((arrs[0][lol[1]] < arrs[0][lol[0]])
				& (arrs[1][lol[1]] + 1 > arrs[1][lol[0]]))
			{
				arrs[1][lol[0]] = arrs[1][lol[1]] + 1;
				arrs[2][lol[0]] = lol[1];
			}
			lol[1]++;
		}
		if (arrs[1][lol[0]] > lol[2])
		{
			lol[2] = arrs[1][lol[0]];
			lol[3] = lol[0];
		}
		lol[0]++;
	}
	return (lol[3]);
}

static void	lis_single(int len, int **arrs, int *lis)
{
	int	lis_best_idx;

	lis[0] = 0;
	lis_best_idx = lis_core(arrs, len);
	while (lis_best_idx != -1)
	{
		lis[0]++;
		lis[lis[0]] = arrs[0][lis_best_idx];
		lis_best_idx = arrs[2][lis_best_idx];
	}
}

static void	init_arrs(int **arrs, int len, t_stack_element *cur)
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

static int	get_best(int **arrs, int len, t_stack *stack, int *keep)
{
	int				*buf;
	int				count;
	t_stack_element	*cur;

	count = 0;
	cur = stack -> head;
	buf = malloc(sizeof(int) * 1000);
	if (!buf)
		return (0);
	while (count < len)
	{
		init_arrs(arrs, len, cur);
		lis_single(stack->stack_length, arrs, buf);
		if (count == 0 || buf[0] > keep[0])
			ft_memcpy(keep, buf, sizeof(int) * 1000);
		count++;
		cur = cur->next;
	}
	free (buf);
	return (1);
}

void	lis_flag(t_stack *a, int **keep)
{
	int				**arrs;
	t_stack_element	*cur;

	cur = a->head;
	if ((init_md_arrays(&arrs, (a->stack_length), 3) == -1) 
		|| !get_best(arrs, a->stack_length, a, *keep))
	{
		free(*keep);
		*keep = NULL;
	}
	clear_md_arrays(&arrs, 3);
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
