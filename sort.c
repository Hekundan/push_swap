/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:31:44 by johartma          #+#    #+#             */
/*   Updated: 2025/04/26 13:04:39 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>
#include <limits.h>

static int	max(int x, int y)
{
	if (x > y)
		return (x);
	else
		return (y);
}


static int	sort_ranks(t_stack *a)
{
	int				*raw;
	int				*rank;
	int				count;
	int				count2;
	t_stack_element	*cur;

	raw = malloc(sizeof(int) * a->stack_length);
	if (!raw)
		return (-1);
	cur = a->head;
	count = 0;
	while (count < a->stack_length)
	{
		raw[count] = cur->nb;
		cur = cur->next;
		count++;
	}
	rank = malloc(sizeof(int) * a->stack_length);
	if (!rank)
	{
		free(raw);
		return (-1);
	}
	count = 0;
	while (count < a->stack_length)
	{
		count2 = 0;
		while (count2 < a->stack_length)
		{
			if (raw[count2] > raw[count])
			{
				rank[count]++;
				count2++;
			}
		}
	}
	cur = a->head;
	count = 0;
	while (count < a->stack_length)
	{
		cur->nb = rank[count];
		cur = cur->next;
		count++;
	}
	free(raw);
	free(rank);
	return (0);
}

static char	*lis_flag(t_stack *a)
{
	int				*val;
	t_stack_element	*cur;
	int				*dp;
	int				*pr;
	int				best;
	char			*keep;

	val = xcalloc(a->stack_length, sizeof *val);
	cur = a->head;
	for(int i=0;i<n;++i){
		val[i]=cur->nb; cur=cur->next;
	}

    int *dp = xcalloc(a->stack_length, sizeof *dp);
    int *pr = xcalloc(a->stack_length, sizeof *pr);
    for(int i=0;i<n;++i){ dp[i]=1; pr[i]=-1; }

    int best=0;
    for(int i=0;i<n;++i)
        for(int j=0;j<i;++j)
            if(val[j]<val[i]&&dp[j]+1>dp[i]){ dp[i]=dp[j]+1; pr[i]=j; best=i; }

    char *keep=xcalloc(a->stack_length,1);
    for(int k=best;k!=-1;k=pr[k]) keep[k]=1;
    free(val);free(dp);free(pr); return keep;
}

/*──────────────── basic stack helpers ───────────────────────────*/
static int	min_pos(t_stack *s)
{
	int				pos;
	int				best;
	int				count;
	t_stack_element	*current;

	pos = 0;
	best = INT_MAX;
	current = s->head;
	count = 0;
	while (count < s->stack_length)
	{
		if (current->nb < best)
		{
			best = current->nb;
			pos = count;
		}
		current = current->next;
		count++;
	}
	return (pos);
}

static int target_pos(t_stack *a,int v)
{
	t_stack_element	*current;
	int idx=-1; int best=INT_MAX; t_stack_element *c=a->head;
    for(int i=0;i<(int)a->stack_length;++i){ if(c->nb>v&&c->nb<best){best=c->nb;idx=i;} c=c->next; }
    if(idx!=-1) return idx; /* falls between two */
    /* otherwise behind current max */
    return min_pos(a); /* rotate to smallest, then insert */
}

/* rotate stack so that index becomes new head */
static void rotate_to(t_stack *s,int idx,char **ops,int (*up)(char**,t_stack*),int (*down)(char**,t_stack*))
{
    int n=s->stack_length;
    if(idx<=n/2) while(idx--) up(ops,s);
    else         while(idx++<n) down(ops,s);
}

/*──────────────── step 1: push non‑LIS to B ─────────────────────*/
static void push_non_lis(t_stack *a,t_stack *b,char **ops,char *keep)
{
    int n=a->stack_length;
    for(int i=0;i<n;++i)
    {
        if(keep[i]) ra(ops,a);
        else         pb(ops,a,b);
    }
}

/*──────────────── step 2: re‑insert B into A ────────────────────*/
static void insert_from_b(t_stack *a,t_stack *b,char **ops)
{
    while(b->stack_length)
    {
        int v=b->head->nb;
        int pos=target_pos(a,v);
        rotate_to(a,pos,ops,ra,rra);
        pa(ops,a,b);
    }
}

/*──────────────── step 3: final rotate so that 0 is top ─────────*/
static void finish_rotate(t_stack *a,char **ops)
{
    rotate_to(a,min_pos(a),ops,ra,rra);
}

/*──────────────── public orchestrator ───────────────────────────*/
int sort_large(t_stack *a,t_stack *b,char **ops)
{
    if(a->stack_length<2) return 0;

    rank_compress(a);                 /* 1 */
    char *keep=lis_flag(a);           /* 2 */
    push_non_lis(a,b,ops,keep);       /* 3 */
    free(keep);
    insert_from_b(a,b,ops);           /* 4 */
    finish_rotate(a,ops);             /* 5 */
    return 0;
}
