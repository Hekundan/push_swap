/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:31:08 by johartma          #+#    #+#             */
/*   Updated: 2025/04/25 11:24:55 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

void	stack_add_element(t_stack_element *element, t_stack *stack)
{
	if (!stack->head)
	{
		element->next = element;
		element->former = element;
	}
	else
	{
		stack->head->former->next = element;
		element->next = stack->head;
		element->former = stack->head->former;
		stack->head->former = element;
	}
	stack->head = element;
	stack->stack_length++;
}

t_stack_element	*stack_fetch(t_stack *stack)
{
	t_stack_element	*to_fetch;

	if (!stack->head)
		return (NULL);
	to_fetch = stack->head;
	if (stack->stack_length == 1)
		stack->head = NULL;
	else
	{
		to_fetch->former->next = to_fetch->next; 
		to_fetch->next->former = to_fetch->former;
		stack->head = stack->head->next;
	}
	stack->stack_length--;
	return (to_fetch);
}


