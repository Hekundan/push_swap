/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:24:56 by johartma          #+#    #+#             */
/*   Updated: 2025/04/27 20:52:56 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>
#include <stdio.h>

void print_sorted(t_stack *stack_a)
{
	for (int i = 0; i < (stack_a->stack_length); i++)
	{
		printf("%i\n", stack_a->head->nb);
		stack_a->head = stack_a->head->next;
	}
}

int	main(int argc, char **argv)
{
	int		*numbers;
	char	*moves;
	t_stack	*stack_a;
	t_stack	*stack_b;

	stack_a = NULL;
	stack_b = NULL;
	moves = malloc(1);
	if (!moves)
	{
		burnit(&numbers, &moves, &stack_a, &stack_b);
		return (-1);
	}
	*moves = 0;
	numbers = read_to_arr(argc, argv);
	if (!numbers
		|| (build_stacks(&stack_a, &stack_b, numbers, argc - 1) == -1)
		|| (sort(stack_a, stack_b, &moves) == -1))
	{
		burnit(&numbers, &moves, &stack_a, &stack_b);
		return (-1);
	}
	//print_sorted(stack_a);
	ft_printf("%s", moves);
	burnit(&numbers, &moves, &stack_a, &stack_b);
	return (0);
}
