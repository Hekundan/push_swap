/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_helpers_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:52:07 by johartma          #+#    #+#             */
/*   Updated: 2025/05/08 19:12:17 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>
#include <stdlib.h>

void	get_best_idx(int *nbs, t_stack *a, t_stack *b)
{
	int	nbs2[5];

	nbs2[0] = -1;
	while (nbs2[0]++ < (b->stack_length - 1))
	{
		nbs2[1] = best_insert_to_a(a, get_val_at_pos(b, nbs2[0]));
		if (nbs2[1] <= (a->stack_length / 2))
			nbs2[3] = nbs2[1];
		else
			nbs2[3] = a->stack_length - nbs2[1];
		if (nbs2[0] <= (b->stack_length / 2))
			nbs2[4] = nbs2[0];
		else
			nbs2[4] = b->stack_length - nbs2[0];
		if (nbs2[3] > nbs2[4])
			nbs2[2] = nbs2[3];
		else
			nbs2[2] = nbs2[4];
		if (nbs2[2] < nbs[0])
		{
			nbs[0] = nbs2[2];
			nbs[1] = nbs2[0];
			nbs[2] = nbs2[1];
		}
	}
}

int	insert_from_b(t_stack *a, t_stack *b, char **ops)
{
	int	*nbs;

	nbs = ft_calloc(5, sizeof(int));
	if (!nbs)
		return (-1);
	while (b->stack_length)
	{
		nbs[0] = INT_MAX;
		get_best_idx(nbs, a, b);
		rot_both_min_cost(a, b, nbs, ops);
		pa(ops, a, b);
	}
	nbs[2] = get_val_pos(a, get_extr(a, 's'));
	nbs[1] = 0;
	rot_both_min_cost(a, b, nbs, ops);
	free(nbs);
	return (0);
}
