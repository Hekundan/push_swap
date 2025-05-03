/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:31:44 by johartma          #+#    #+#             */
/*   Updated: 2025/05/03 12:02:06 by johartma         ###   ########.fr       */
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
	int	count;
	int	len;

	count = 0;
	len = a->stack_length;
	while (count < len)
	{
		if (keep[count])
			ra(ops, a);
		else
			pb(ops, a, b);
		count++;
	}
}

int	sort(t_stack *a, t_stack *b, char **ops)
{
	char	*keep;

	keep = ft_calloc(a->stack_length, 1);
	if (!keep)
		return (-1);
	if (!((a->stack_length < 2) || check_sorted(a)))
	{
		sort_ranks(a);
		lis_flag(a, keep);
		push_non_lis(a, b, ops, keep);
		insert_from_b(a, b, ops);
		rotate_to(a, min_pos(a), ops, 'a');
	}
	free(keep);
	return (0);
}
