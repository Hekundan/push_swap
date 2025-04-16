/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:52:29 by johartma          #+#    #+#             */
/*   Updated: 2025/04/16 14:00:23 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

int	add_to_operations(char *operations, char *to_add)
{
	char	*result;

	result = ft_strjoin(operations, to_add);
	if (result)
	{
		free(operations);
		operations = result;
		return (0);
	}
	else
		return (-1);
}
