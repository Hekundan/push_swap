/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:34:34 by johartma          #+#    #+#             */
/*   Updated: 2025/05/08 16:56:06 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>

int	get_val_at_pos(t_stack *s, int pos)
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

int	get_extr(t_stack *a, char kind)
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

int	get_val_pos(t_stack *a, int val)
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

int	get_min_offset(t_stack *a, int off)
{
	int	count;
	int	extr;
	int	best_val;

	count = 0;
	extr = INT_MAX;
	while (count < a->stack_length)
	{
		if (((get_val_at_pos(a, count) - off) < extr)
			&& ((get_val_at_pos(a, count) - off) > 0))
		{
			extr = get_val_at_pos(a, count) - off;
			best_val = get_val_at_pos(a, count);
		}
		count++;
	}
	return (best_val);
}

int	best_insert_to_a(t_stack *a, int val)
{
	if (val < get_extr(a, 's'))
		return (get_val_pos(a, get_extr(a, 's')));
	if (val > get_extr(a, 'l'))
		return (get_val_pos(a, get_extr(a, 'l')) + 1);
	return (get_val_pos(a, get_min_offset(a, val)));
}
