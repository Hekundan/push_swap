/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stacks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:24:24 by johartma          #+#    #+#             */
/*   Updated: 2025/04/26 11:07:12 by johartma         ###   ########.fr       */
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
		cur = malloc(sizeof(t_stack_element));
		if (!cur)
			return (-1);
		cur->nb = numbers[length - count - 1];
		stack_add_element(cur, a);
		count++;
	}
	a->stack_length = length;
	return (0);
}

static int	alloc_stacks(t_stack **a, t_stack **b)
{
	*a = malloc(sizeof(**a));
	*b = malloc(sizeof(**b));
	if (!*a || !*b)
		return (-1);

	(*a)->head = NULL;
	(*a)->stack_length = 0;
	(*b)->head = NULL;
	(*b)->stack_length = 0;
	return (0);
}

int	build_stacks(t_stack **a, t_stack **b, int *numbers, int length)
{
	if (alloc_stacks(a, b) == -1)
		return (-1);
	if (fill_stack(*a, numbers, length) == -1)
		return (-1);
	return (0);
}
