/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:52:29 by johartma          #+#    #+#             */
/*   Updated: 2025/05/03 10:20:20 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>
#include <limits.h>

int	add_to_operations(char **operations, char *to_add)
{
	char	*result;

	if (*operations == NULL)
		*operations = ft_strdup("");
	result = ft_strjoin(*operations, to_add);
	if (result)
	{
		free(*operations);
		*operations = result;
		return (0);
	}
	else
	{
		return (-1);
	}
}

int	check_sorted(t_stack *stack)
{
	int				buf;
	int				count;
	t_stack_element	*cur;

	buf = INT_MIN;
	count = 0;
	cur = stack->head;
	while (count < stack->stack_length)
	{
		if (cur->nb > buf)
			buf = cur->nb;
		else
			return (0);
		cur = cur->next;
		count++;
	}
	return (1);
}

