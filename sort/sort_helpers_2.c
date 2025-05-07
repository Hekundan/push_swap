/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_helpers_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:52:07 by johartma          #+#    #+#             */
/*   Updated: 2025/05/07 23:07:08 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>
#include <stdlib.h>

static int	get_val_at_pos(t_stack *s, int pos)
{
	int				i;
	t_stack_element	*cur;

	i = 0;
	cur = s->head;
	while (i < pos)
	{
		cur = cur->next;
		i++;
	}
	return (cur->nb);
}

static int	get_extr(t_stack *a, char kind)
{
	int	count;
	int	extr;

	count = 0;
	if (kind == 's')
		extr = INT_MAX;
	else
		extr = INT_MIN;
	while (count < a->stack_length)
	{
		if ((kind == 's') && (get_val_at_pos(a, count) < extr))
			extr = get_val_at_pos(a, count);
		else if ((kind == 'l') && (get_val_at_pos(a, count) > extr))
			extr = get_val_at_pos(a, count);
		count++;
	}
	return (extr);
}

static int	get_val_pos(t_stack *a, int val)
{
	t_stack_element	*cur;
	int				pos;

	cur = a -> head;
	pos = 0;
	while (pos < a->stack_length)
	{
		if (get_val_at_pos(a, pos) == val)
			return (pos);
		pos++;
		cur = cur->next;
	}
	return (-1);
}

static int	get_min_offset(t_stack *a, int off)
{
	int	count;
	int	extr;

	count = 0;
	extr = INT_MAX;
	while (count < a->stack_length)
	{
		if ((get_val_at_pos(a, count) - off) < extr
			&& (get_val_at_pos(a, count) - off) > 0)
			extr = get_val_at_pos(a, count);
		count++;
	}
	return (extr);
}

static int	best_insert_to_a(t_stack *a, t_stack *b, int val)
{
	if (val < get_extr(a, 's'))
		return (get_val_pos(a, get_extr(a, 's')));
	if (val > get_extr(a, 'l'))
		return (get_val_pos(a, get_extr(a, 'l')) + 1);
	return (get_val_pos(a, get_min_offset(a, get_val_pos(b, val))));
}

void	get_best_idx(int *nbs, t_stack *a, t_stack *b)
{
	int	nbs2[5];

	nbs2[0] = -1;
	while (nbs2[0]++ < (b->stack_length - 1))
	{
		nbs2[1] = best_insert_to_a(a, b, get_val_at_pos(b, nbs2[0]));
		if (nbs2[1] <= (a->stack_length / 2))
			nbs2[3] = nbs2[1];
		else
			nbs2[3] = a->stack_length - nbs2[1];
		if (nbs2[0] <= (b->stack_length / 2))
			nbs2[4] = nbs2[0];
		else
			nbs2[4] = b->stack_length - nbs2[0];
		if (nbs2[3] > nbs2[4])
			nbs2[2] = nbs2[3];
		else
			nbs2[2] = nbs2[4];
		if (nbs2[2] < nbs[0])
		{
			nbs[0] = nbs2[2];
			nbs[1] = nbs2[0];
			nbs[2] = nbs2[1];
		}
	}
}

int	insert_from_b(t_stack *a, t_stack *b, char **ops)
{
	int	*nbs;

	nbs = ft_calloc(3, sizeof(int));
	if (!nbs)
		return (-1);
	while (b->stack_length)
	{
		nbs[0] = INT_MAX;
		get_best_idx(nbs, a, b);
		rot_both_min_cost(a, b, nbs, ops);
		pa(ops, a, b);
	}
	nbs[1] = get_val_pos(a, get_extr(a, 'l'));
	nbs[2] = 0;
	rot_both_min_cost(a, b, nbs, ops);
	free(nbs);
	return (0);
}
