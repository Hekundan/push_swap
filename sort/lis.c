/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:41:39 by johartma          #+#    #+#             */
/*   Updated: 2025/05/08 16:45:33 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "push_swap.h"

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
