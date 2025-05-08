/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:24:56 by johartma          #+#    #+#             */
/*   Updated: 2025/05/08 20:48:41 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int		*numbers;
	char	*moves;
	t_stack	*stack_a;
	t_stack	*stack_b;

	stack_a = NULL;
	stack_b = NULL;
	moves = ft_calloc(1, 1);
	if (!moves || argc == 0)
	{
		burnit(&numbers, &moves, &stack_a, &stack_b);
		free(moves);
		return (-1);
	}
	numbers = read_to_arr(&argc, argv);
	if (!numbers
		|| (build_stacks(&stack_a, &stack_b, numbers, argc - 1) == -1)
		|| (sort(stack_a, stack_b, &moves) == -1))
		ft_putstr_fd("Error\n", 2);
	ft_printf("%s", moves);
	burnit(&numbers, &moves, &stack_a, &stack_b);
	return (0);
}
