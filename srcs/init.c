/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gartanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 15:58:24 by gartanis          #+#    #+#             */
/*   Updated: 2020/06/27 17:53:58 by gartanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void				free_stack(t_stack *stack)
{
	t_linklist	*tmp;
	int			i;

	i = 0;
	while (i < 2)
	{
		tmp = stack->stack[i];
		while (tmp->head)
		{
			free(tmp->head);
			tmp->head = tmp->head->next;
		}
		free(tmp);
		i++;
	}
}

static void			ft_push(t_linklist *list, int data)
{
	t_node *tmp;

	if (!(tmp = (t_node*)malloc(sizeof(t_node))))
		exit(1);
	tmp->data = data;
	tmp->next = NULL;
	tmp->prev = list->tail;
	if (list->tail)
		list->tail->next = tmp;
	list->tail = tmp;
	if (!list->head)
		list->head = tmp;
	list->size += 1;
}

t_linklist			*creat_linkedlist(char stack)
{
	t_linklist *tmp;

	if (!(tmp = (t_linklist*)malloc(sizeof(t_linklist))))
		exit(1);
	tmp->size = 0;
	tmp->letter = stack;
	tmp->head = NULL;
	tmp->tail = NULL;
	return (tmp);
}

static void			creat_stack(t_stack *stack, char **str)
{
	stack->stack[0] = creat_linkedlist('a');
	stack->stack[1] = creat_linkedlist('b');
	while (*str)
	{
		ft_push(stack->stack[0], ft_atoi(*str));
		str += 1;
	}
	stack->num_a = 0;
	stack->num_b = 0;
	ft_bzero(stack->push[A], 64);
	ft_bzero(stack->push[B], 64);
	stack->push[A][0] = stack->stack[A]->size;
}

int					init_stack(t_stack *stack, char *av[], int ac)
{
	char	**str;
	int		ret;
	int		i;

	stack->opt = 0;
	str = get_arg(stack, ac, av);
	if (!str[0])
		return (NOARG);
	if ((ret = check_stack(str)))
		return (ret);
	creat_stack(stack, str);
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
	return (ret);
}