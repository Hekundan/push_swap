/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stacks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:24:24 by johartma          #+#    #+#             */
/*   Updated: 2025/04/25 11:30:15 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

static int	fill_stack(t_stack *a, int *numbers, int length)
{
	int				count;
	t_stack_element	*cur;

	count = 0;
	while (count < length)
	{
		cur = malloc(sizeof(t_stack));
		if (!cur)
			return (-1);
		cur->nb = numbers[count];
		stack_add_element(cur, a);
	}
	return (0);
}

static int	alloc_stacks(t_stack *a, t_stack *b)
{
	a = malloc(sizeof(t_stack));
	b = malloc(sizeof(t_stack));
	if (!a || !b)
		return (-1);
	else
	{
		a->stack_length = 0;
		b->stack_length = 0;
		return (0);
	}
}

int	build_stacks(t_stack *a, t_stack *b, int *numbers, int length)
{
	if (alloc_stacks(a, b) == -1)
		return (-1);
	if (fill_stack(a, numbers, length) == -1)
		return (-1);
	return (0);
}
