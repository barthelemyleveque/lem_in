/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_add_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 18:12:01 by bleveque          #+#    #+#             */
/*   Updated: 2019/04/27 17:27:47 by anrzepec         ###   ########.fr       */
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
	//ft_printf("Visited |nb %d |  %d\n", i, tab[i]);
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
	//ft_printf("QUEUE | added to queue : %d\n", tmp->next->node->hash); 
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
		{
			//ft_printf("-- node : %s, a un flow vers : %s de %d -- \n", node->name, check->child->name, check->flow);
			break;
		}
		//ft_printf("XX node : %s, a un flow vers : %s de %d -- \n", node->name, check->child->name, check->flow);
		check = check->next;
	}
	if (check)
	{
		// Si check existe, on a le lien sortant du node qui a un opposite entrant avec un flow == 1;
		ft_printf("road from %s to %s is : ", node->name, link->child->name);
		if (link->child == check->child)
		{
			ft_printf("cancelling flow | \nlink->cheld : %s  check->child : %s\n", link->child->name, check->child->name);
			return (0);
		}
		else
		{
			ft_printf("not cancelling flow\n");
			return (1);
		}
	}
	return (0);
}

	/*
	while (tmp)
	{
		if (tmp->flow == 1 && node->special != 1)
		{
			i = 1;
			break;
		}
		tmp = tmp->next;
	}
	
	if (i == 1)
	{
		ft_printf("node special: %s, hash: %s\n", node->name, link->child->name);
		if (node->special != -1 && link->opposite->flow != 1)
			return (1);
		ft_printf("special : %s\n", link->child->name);
		link->child->special = -1;
	}*/
