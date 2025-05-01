/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_helpers_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:52:07 by johartma          #+#    #+#             */
/*   Updated: 2025/04/27 21:16:18 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>

static int	rot_cost(int len, int idx)
{
	if (idx < (len - idx))
		return (idx);
	else
		return (len - idx);
}

static int	target_pos(t_stack *a, int v)
{
	t_stack_element	*current;
	int				idx;
	int				best;
	int				count;

	idx = -1;
	best = INT_MAX;
	count = 0;
	current = a -> head;
	while (current != a->head && count < a->stack_length)
	{
		if (current->nb > v && current->nb < best)
		{
			best = current -> nb;
			idx = count;
		}
		current = current->next;
		count++;
	}
	if (idx != -1)
		return (idx);
	return (min_pos(a));
}

static int	best_idx_b(t_stack *a, t_stack *b)
{
	int				best;
	int				cbest;
	int				count;
	t_stack_element	*current;

	best = 0;
	cbest = INT_MAX;
	current = b->head;
	count = 0;
	while (count < b->stack_length)
	{
		if (rot_cost(a->stack_length, target_pos(a, current->nb)
				+ rot_cost(b->stack_length, count)) < cbest)
		{
			cbest = rot_cost(a->stack_length, target_pos(a, current->nb)
					+ rot_cost(b->stack_length, count));
			best = count;
		}
		current = current->next;
		count++;
	}
	return (best);
}

int	min_pos(t_stack *s)
{
	int				pos;
	int				best;
	int				count;
	t_stack_element	*current;

	pos = 0;
	best = INT_MAX;
	current = s->head;
	count = 0;
	while (count < (s->stack_length))
	{
		if (current->nb < best)
		{
			best = current->nb;
			pos = count;
		}
		current = current->next;
		count++;
	}
	return (pos);
}

void	insert_from_b(t_stack *a, t_stack *b, char **op)
{
	while (b->stack_length)
	{
		move_b_top(b, op, best_idx_b(a, b));
		rotate_to(a, target_pos(a, b->head->nb), op, 'a');
		pa(op, a, b);
	}
}
