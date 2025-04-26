/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:24:56 by johartma          #+#    #+#             */
/*   Updated: 2025/04/26 10:11:40 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


int	main(int argc, char **argv)
{
	int		*numbers;
	char	*moves;
	t_stack	*stack_a;
	t_stack	*stack_b;

	stack_a = NULL;
	stack_b = NULL;
	moves = NULL;
	numbers = read_to_arr(argc, argv);
	if (!numbers)
	{
		burnit(&numbers, &moves, &stack_a, &stack_b);
		return (-1);
	}
	if (build_stacks(stack_a, stack_b, numbers, argc - 1) == -1)
	{
		burnit(&numbers, &moves, &stack_a, &stack_b);
		return (-1);
	}
}