/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:08:41 by johartma          #+#    #+#             */
/*   Updated: 2025/04/26 10:27:34 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate_front(t_stack *stack)
{
	stack->head = stack->head->next;
}

int	ra(char *operations, t_stack *stack_a)
{
	rotate_front(stack_a);
	return (add_to_operations(&operations, "ra\n"));
}

int	rb(char *operations, t_stack *stack_b)
{
	rotate_front(stack_b);
	return (add_to_operations(&operations, "rb\n"));
}

int	rr(char *operations, t_stack *stack_a, t_stack *stack_b)
{
	rotate_front(stack_a);
	rotate_front(stack_b);
	return (add_to_operations(&operations, "rr\n"));
}
