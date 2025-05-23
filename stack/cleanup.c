/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:49:32 by johartma          #+#    #+#             */
/*   Updated: 2025/05/08 16:59:27 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

static void	stack_rem_elmnt(t_stack *stack)
{
	t_stack_element	*to_fetch;

	if (!stack->head)
		return ;
	to_fetch = stack->head;
	if (to_fetch == to_fetch->next)
		stack->head = NULL;
	else
	{
		to_fetch->former->next = to_fetch->next; 
		to_fetch->next->former = to_fetch->former;
		stack->head = stack->head->next;
	}
	stack->stack_length--;
	free (to_fetch);
}

static void	clear_stack(t_stack *s)
{
	if (s)
	{
		while (s->head)
			stack_rem_elmnt(s);
	}
	free(s);
}

void	burnit(int **n, char **s, t_stack **a, t_stack **b)
{
	if (*a)
		clear_stack(*a);
	if (*b)
		clear_stack(*b);
	if (*s)
		free(*s);
	if (*n)
		free(*n);
}
