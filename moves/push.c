/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:38:23 by johartma          #+#    #+#             */
/*   Updated: 2025/04/26 10:26:55 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	swap(t_stack *x, t_stack *y)
{
	t_stack_element	*element;

	element = stack_fetch(y);
	if (!element)
		return (-1);
	else
		stack_add_element(element, x);
	return (0);
}

int	pa(char **operations, t_stack *stack_a, t_stack *stack_b)
{
	if (swap(stack_a, stack_b) == -1)
		return (-1);
	return (add_to_operations(operations, "pa\n"));
}

int	pb(char **operations, t_stack *stack_a, t_stack *stack_b)
{
	if (swap(stack_b, stack_a) == -1)
		return (-1);
	return (add_to_operations(operations, "pb\n"));
}