/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_add_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 18:12:01 by bleveque          #+#    #+#             */
/*   Updated: 2019/05/04 13:21:17 by andrewrze        ###   ########.fr       */
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
		return (M_FAIL);
	add->node = link->child;
	add->next = NULL;
	tmp = queue;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = add;
	return (1);
}

/*
 ** map[node][wasintroducedby]
 ** permet de partir du hash de end pour remonter jusqu'a la source ! HEHEH
 */ 

void	add_to_parent_map(t_node *pos, t_link *link, int *map)
{
	map[link->child->hash] = pos->hash;
}

/*
 ** Ne regarde pas seulement si le lien est visite, mais check si une fourmi
 ** peut prendre le chemin
 */

int		is_visited(t_link *link, int *visited, t_node *node)
{
	int		i;
	t_link	*check;

	if (link->flow >= 1)
		return (1);
	i = -1;
	while (visited[++i] != -1)
		if (visited[i] == link->child->hash)
			return (1);
	check = node->links;
	while (check)
	{
		if (check->flow == -1)
			break;
		check = check->next;
	}
	if (check)
	{
		if (link->child == check->child)
		{
			link->child->visited = 1;
			return (0);
		}
		else if (node->visited == 1)
				return (0);
		else
			return (1);
	}
	return (0);
}
