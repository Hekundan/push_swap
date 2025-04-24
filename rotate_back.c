/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:30:21 by johartma          #+#    #+#             */
/*   Updated: 2025/04/23 19:32:13 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate_back(t_stack *stack)
{
	stack->head = stack->head->former;
}

int	rra(char *operations, t_stack *stack_a)
{
	rotate_back(stack_a);
	return (add_to_operations(operations, "rra\n"));
}

int	rrb(char *operations, t_stack *stack_b)
{
	rotate_back(stack_b);
	return (add_to_operations(operations, "rrb\n"));
}

int	rrr(char *operations, t_stack *stack_a, t_stack *stack_b)
{
	rotate_back(stack_a);
	rotate_back(stack_b);
	return (add_to_operations(operations, "rrr\n"));
}
