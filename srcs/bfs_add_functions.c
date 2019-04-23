/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_add_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 18:12:01 by bleveque          #+#    #+#             */
/*   Updated: 2019/04/23 19:00:47 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_to_visited(t_link *link, int *tab)
{
	int		i;

	i = 0;
	while (tab[i] != -1)
		i++;
	tab[i] = link->child->hash;
	ft_printf("Visited |nb %d |  %d\n", i, tab[i]);
}

int		add_to_queue(t_link *link, t_queue *queue)
{
	t_queue	*tmp;
	t_queue *add;

	if (!(queue->node))
	{
		queue->node = link->child;
		ft_printf("QUEUE | added to queue : %d\n", link->child->hash); 
		return (1);
	}
	if (!(add = (t_queue*)malloc(sizeof(t_queue))))
		return (0);
	add->node = link->child;
	add->next = NULL;
	tmp = queue;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = add;
	ft_printf("QUEUE | added to queue : %d\n", tmp->next->node->hash); 
	return (1);
}

int		add_to_parent_map(t_node *pos, t_link *link, t_parent *map)
{
	t_parent	*tmp;
	t_parent	*add;

	if (map->h_node == -1)
	{
		map->h_introby = pos->hash;
		map->h_node = link->child->hash;
		ft_printf("parent | node : [%s] intro par : [%s]\n", link->child->name, pos->name); 
		return (1);
	}
	if (!(add = (t_parent*)malloc(sizeof(t_parent))))
		return (0);
	add->h_introby = pos->hash;
	add->h_node = link->child->hash;
	add->next = NULL;
	tmp = map;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = add;
	ft_printf("parent | node : [%s] intro par : [%s]\n", link->child->name, pos->name); 
	return (1);
}

/*
** Ne regarde pas seulement si le lien est visite, mais check si une fourmi
** peut prendre le chemin
*/

int		is_visited(t_link *link, int *tab)
{
	int	i;

	if (link->flow == 1 || link->flow == -2)
		return (1);
	i = 0;
	while (tab[i] != -1)
	{
		if (tab[i] == link->child->hash)
			return (1);
		i++;
	}
	return (0);
}
