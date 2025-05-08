/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_both.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:49:52 by johartma          #+#    #+#             */
/*   Updated: 2025/05/08 17:20:48 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rot_both_bkwd(t_stack *a, t_stack *b, int *idxs, char **ops)
{
	while (idxs[2] > 0 & idxs[3] > 0)
	{
		rrr(ops, a, b);
		idxs[2]--;
		idxs[3]--;
	}
	while (idxs[3] > 0)
	{
		rra(ops, a);
		idxs[3]--;
	}
	while (idxs[2] > 0)
	{
		rrb(ops, b);
		idxs[2]--;
	}
}

static void	rot_both_fwd(t_stack *a, t_stack *b, int *idxs, char **ops)
{
	while (idxs[0] > 0 && idxs[1] > 0)
	{
		rr(ops, a, b);
		idxs[0]--;
		idxs[1]--;
	}
	while (idxs[1] > 0)
	{
		ra(ops, a);
		idxs[1]--;
	}
	while (idxs[0] > 0)
	{
		rb(ops, b);
		idxs[0]--;
	}
}

static void	rot_a_ind(t_stack *a, int *idxs, char **ops)
{
	if (idxs[1] <= (a->stack_length / 2))
	{
		while (idxs[1] > 0)
		{
			ra(ops, a);
			idxs[1]--;
		}
	}
	else
	{
		while (idxs[3] > 0)
		{
			rra(ops, a);
			idxs[3]--;
		}
	}
}

static void	rot_b_ind(t_stack *b, int *idxs, char **ops)
{
	if (idxs[0] <= (b->stack_length / 2))
	{
		while (idxs[0] > 0)
		{
			rb(ops, b);
			idxs[0]--;
		}
	}
	else
	{
		while (idxs[2] > 0)
		{
			rrb(ops, b);
			idxs[2]--;
		}
	}
}

void	rot_both_min_cost(t_stack *a, t_stack *b, int *idxs, char **ops)
{
	idxs++;
	idxs[3] = a->stack_length - idxs[1];
	idxs[2] = b->stack_length - idxs[0];
	if (idxs[1] <= (a->stack_length / 2)
		&& idxs[0] <= (b->stack_length / 2))
		rot_both_fwd(a, b, idxs, ops);
	else if (idxs[3] <= (a->stack_length / 2)
		&& idxs[2] <= (b->stack_length / 2))
		rot_both_bkwd(a, b, idxs, ops);
	else
	{
		rot_a_ind(a, idxs, ops);
		rot_b_ind(b, idxs, ops);
	}
}
