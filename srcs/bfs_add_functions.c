/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_add_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 18:12:01 by bleveque          #+#    #+#             */
/*   Updated: 2019/04/26 16:37:37 by bleveque         ###   ########.fr       */
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

int		is_visited(t_link *link, int *tab, t_node *node)
{
	int	i;
	t_link	*tmp;
	t_node 	*opp_node;
	t_link	*opp_link;

	if (link->flow == 1 || link->flow == -2 || link->flow == -1)
		return (1);
	i = 0;
	opp_link = link->child->links;
	tmp = node->links;
	while (tmp)
	{
		if (tmp->flow == 1)
		{
			i = 1;
			break ;
		}
		tmp = tmp->next;
	}
	while ((opp_link) && (opp_link->child!= node))
		opp_link = opp_link->next;
	/*
	if (i == 1)
	{
		ft_printf("Node de depart : %s\n", node->name);
		ft_printf("Child a l'etude : %s\n", link->child->name);
		ft_printf("Node alreay as a flow to: %s\n", tmp->child->name);
		if (opp_link)
			ft_printf("Opposite link is going to : %s\n", opp_link->child->name);
		if (opp_link->flow == 0)
		{
			ft_printf("no go to queue or parent\n\n");
			return (1);
		}
		ft_printf("will go to queue\n\n");
	}*/
	// if le node a deja un flow sortant, seulement si c'est le link oppose tu
	// peux y aller
	i = 0;
	while (tab[i] != -1)
	{
		if (tab[i] == link->child->hash)
			return (1);
		i++;
	}
	return (0);
}
