/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:31:44 by johartma          #+#    #+#             */
/*   Updated: 2025/05/07 21:50:24 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>
#include <limits.h>

void	sort_array_ranks(int **arrs, int stack_len)
{
	int	i;
	int	j;

	i = 0;
	while (i < stack_len)
	{
		j = 0;
		while (j < stack_len)
		{
			if (arrs[0][j] < arrs[0][i])
				arrs[1][i]++;
			j++;
		}
		i++;
	}
}

void	move_b_top(t_stack *b, char **op, int idx)
{
	if (idx <= (b->stack_length / 2))
	{
		while (idx)
		{
			rb(op, b);
			idx--;
		}
	}
	else
	{
		while (idx < (b->stack_length))
		{
			rrb(op, b);
			idx++;
		}
	}
}

static void	push_non_lis(t_stack *a, t_stack *b, char **ops, int *keep)
{
	int	i;
	int	j;
	int	push;
	int	len;

	i = 0;
	push = 0;
	len = a->stack_length;
	while (i < len)
	{
		j = keep[0];
		while (0 < j)
		{
			if (a->head->nb == keep[j])
				push = 1;
			j--;
		}
		if (push)
		{
			ra(ops, a);
			push = 0;
		}
		else
			pb(ops, a, b);
		i++;
	}
}

int	sort(t_stack *a, t_stack *b, char **ops)
{
	int	*keep;

	keep = ft_calloc(1000, sizeof(int));
	if (!keep)
		return (-1);
	if (!((a->stack_length < 2) || check_sorted(a)))
	{
		sort_ranks(a);
		lis_flag(a, &keep);
		if (!keep)
			return (-1);
		push_non_lis(a, b, ops, keep);
		insert_from_b(a, b, ops);
	}
	free(keep);
	return (0);
}
