/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:22:36 by johartma          #+#    #+#             */
/*   Updated: 2025/04/26 10:27:53 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(t_stack *stack)
{
	int	buf;

	buf = stack->head->nb;
	stack->head->nb = stack->head->next->nb;
	stack->head->next->nb = buf;
}

int	sa(char *operations, t_stack *stack_a)
{
	swap(stack_a);
	return (add_to_operations(&operations, "sa\n"));
}

int	sb(char *operations, t_stack *stack_b)
{
	swap(stack_b);
	return (add_to_operations(&operations, "sb\n"));
}

int	ss(char *operations, t_stack *stack_a, t_stack *stack_b)
{
	swap(stack_a);
	swap(stack_b);
	return (add_to_operations(&operations, "ss\n"));
}
