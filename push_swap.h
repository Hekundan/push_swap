/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:21:32 by johartma          #+#    #+#             */
/*   Updated: 2025/04/27 20:59:02 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H 
# define PUSH_SWAP_H
# include "libft/libft.h"

typedef struct t_stack_element
{
	int						nb;
	struct t_stack_element	*next;
	struct t_stack_element	*former;
}	t_stack_element;

typedef struct t_stack
{
	struct t_stack_element	*head;
	int						stack_length;				
}	t_stack;

int				sa(char *operations, t_stack *stack_a);
int				sb(char *operations, t_stack *stack_b);
int				ss(char *operations, t_stack *stack_a, t_stack *stack_b);
int				pa(char *operations, t_stack *stack_a, t_stack *stack_b);
int				pb(char *operations, t_stack *stack_a, t_stack *stack_b);
int				ra(char *operations, t_stack *stack_a);
int				rb(char *operations, t_stack *stack_b);
int				rr(char *operations, t_stack *stack_a, t_stack *stack_b);
int				rra(char *operations, t_stack *stack_a);
int				rrb(char *operations, t_stack *stack_b);
int				rrr(char *operations, t_stack *stack_a, t_stack *stack_b);

int				add_to_operations(char **operations, char *to_add);
void			stack_add_element(t_stack_element *element, t_stack *stack);
t_stack_element	*stack_fetch(t_stack *stack);
void			burnit(int **n, char **s, t_stack **a, t_stack **b);
int				build_stacks(t_stack **a, t_stack **b,
					int *numbers, int length);
int				*read_to_arr(int arr_len, char *args[]);
void			insert_from_b(t_stack *a, t_stack *b, char **op);
int				min_pos(t_stack *s);
char			*lis_flag(t_stack *a, char *keep);
int				sort_ranks(t_stack *a);
int				sort(t_stack *a, t_stack *b, char **ops);
void			move_b_top(t_stack *b, char **op, int idx);
void			rotate_to(t_stack *s, int idx, char **ops, char stack);
void			sort_array_ranks(int **arrs, int stack_len);


#endif