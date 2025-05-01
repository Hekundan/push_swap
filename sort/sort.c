/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:31:44 by johartma          #+#    #+#             */
/*   Updated: 2025/04/27 21:46:39 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>
#include <limits.h>

void	sort_array_ranks(int **arrs, int stack_len)
{
	int	count[2];

	count[0] = 0;
	while (count[0] < stack_len)
	{
		count[1] = 0;
		while (count[1] < stack_len)
		{
			if (arrs[0][count[1]] < arrs[0][count[0]])
				arrs[1][count[0]]++;
			count[1]++;
		}
		count[0]++;
	}
}

void	rotate_to(t_stack *s, int idx, char **ops, char stack)
{
	int	n;

	n = s->stack_length;
	if (idx <= (n / 2))
	{
		while (idx)
		{
			if (stack == 'a')
				ra(ops, s);
			else
				rb(ops, s);
			idx--;
		}
	}
	else
	{
		while (idx < n)
		{
			if (stack == 'a')
				rra(ops, s);
			else
				rrb(ops, s);
			idx++;
		}
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

static void	push_non_lis(t_stack *a, t_stack *b, char **ops, char *keep)
{
	int	n;
	int	count;
	char first;

	n = a->stack_length;
	count = 0;
	if(keep)
	{
		while (count < n)
		{
			first = keep[0];
			if (first)
				ra(ops, a);
			else
				pb(ops, a, b);
			count++;
		}
		ft_memmove(keep, keep+1, count-1);
		keep[count - 1] = first;
	}
}

int	sort(t_stack *a, t_stack *b, char **ops)
{
	char	*keep;

	keep = ft_calloc(a->stack_length, 1);
	if (!keep)
		return (-1);
	if (a->stack_length < 2) 
		return (0);
	sort_ranks(a);
	lis_flag(a, keep);
	push_non_lis(a, b, ops, keep);
	insert_from_b(a, b, ops);
	rotate_to(a, min_pos(a), ops, 'a');
	free(keep);
	return (0);
}
