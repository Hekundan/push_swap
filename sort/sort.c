/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:31:44 by johartma          #+#    #+#             */
/*   Updated: 2025/04/27 21:46:39 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>
#include <limits.h>

void	sort_array_ranks(int **arrs, int stack_len)
{
	int	count[2];

	count[0] = 0;
	while (count[0] < stack_len)
	{
		count[1] = 0;
		while (count[1] < stack_len)
		{
			if (arrs[0][count[1]] < arrs[0][count[0]])
				arrs[1][count[0]]++;
			count[1]++;
		}
		count[0]++;
	}
}

void	rotate_to(t_stack *s, int idx, char **ops, char stack)
{
	int	n;

	n = s->stack_length;
	if (idx <= (n / 2))
	{
		while (idx)
		{
			if (stack == 'a')
				ra(ops, s);
			else
				rb(ops, s);
			idx--;
		}
	}
	else
	{
		while (idx < n)
		{
			if (stack == 'a')
				rra(ops, s);
			else
				rrb(ops, s);
			idx++;
		}
	}
}

void	move_b_top(t_stack *b, char **op, int idx)
{
	if (idx <= (b->stack_length / 2))
	{
		while (idx)
		{
			rb(op, b);
			idx--;
		}
	}
	else
	{
		while (idx < (b->stack_length))
		{
			rrb(op, b);
			idx++;
		}
	}
}

static void	push_non_lis(t_stack *a,
	t_stack *b,
	char   **ops,
	char    *keep)
{
int len = a->stack_length;
int to_push = len;
/* count how many we actually need to push */
for (int i = 0; i < len; i++)
if (keep[i])
to_push--;
/* we’ll be shrinking len each time we pb() */
while (to_push-- > 0)
{
/* 1) find the cheapest non-LIS element in A to bring to top */
int best_idx  = -1;
int best_cost = INT_MAX;
for (int i = 0; i < len; i++)
{
if (keep[i] == 0)
{
int cost = (i <= len/2 ? i : len - i);
if (cost < best_cost)
{
best_cost = cost;
best_idx  = i;
}
}
}

/* 2) rotate A the minimal way to move best_idx → 0 */
if (best_idx <= len/2)
{
/* ra best_idx times */
while (best_idx-- > 0)
{
ra(ops, a);
/* rotate the keep[] window forward by one */
char first = keep[0];
ft_memmove(keep, keep + 1, len - 1);
keep[len - 1] = first;
}
}
else
{
int rev = len - best_idx;
/* rra rev times */
while (rev-- > 0)
{
rra(ops, a);
/* rotate the keep[] window backward by one */
char last = keep[len - 1];
ft_memmove(keep + 1, keep, len - 1);
keep[0] = last;
}
}

/* 3) push it */
pb(ops, a, b);
/* drop the first keep-flag, shrinking the window */
ft_memmove(keep, keep + 1, len - 1);
len--;
}
}


int	sort(t_stack *a, t_stack *b, char **ops)
{
	char	*keep;

	keep = ft_calloc(a->stack_length, 1);
	if (!keep)
		return (-1);
	if (a->stack_length < 2) 
		return (0);
	sort_ranks(a);
	lis_flag(a, keep);
	push_non_lis(a, b, ops, keep);
	insert_from_b(a, b, ops);
	rotate_to(a, min_pos(a), ops, 'a');
	free(keep);
	return (0);
}
