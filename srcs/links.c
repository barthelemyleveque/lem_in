/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 18:46:51 by bleveque          #+#    #+#             */
/*   Updated: 2019/05/03 23:43:58 by andrewrze        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** flow pour les liens vers start = -2 pour eviter de revenir a la source ?
*/

int		ft_create_link(t_graph *graph, t_node *parent, t_node *enfant, t_link **opp)
{
	t_link	*link;
	t_link	*tmp;

	if (!(link = (t_link*)malloc(sizeof(t_link))))
		return (M_FAIL);
	link->flow = 0;
	link->child = enfant;
	link->closed = 0;
	link->next = NULL;
	if (!(parent->links))
		parent->links = link;
	else
	{
		tmp = parent->links;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = link;
	}
	*opp = link;
	return (1);
}

/*
** Verifier qu'on ne tombe pas sur une collision grace a la valeur de hash dans
** le noeud (cf : fonction ft_fill_node)
*/ 

int		ft_link_link(char **tab, t_graph *graph)
{
	int		hash_0;
	int 	hash_1;
	t_link	*l1;
	t_link	*l2;

	l1 = NULL;
	l2 = NULL;
	hash_0 = jenkins_hash(tab[0]);
	hash_1 = jenkins_hash(tab[1]);
	while (ft_strcmp(tab[0], graph->tab[hash_0]->name))
		hash_0 = hash_0 < PRIME ? hash_0 + 1 : 0;
	while (ft_strcmp(tab[1], graph->tab[hash_1]->name))
		hash_1 = hash_1 < PRIME ? hash_1 + 1 : 0;
	if (ft_create_link(graph, graph->tab[hash_0], graph->tab[hash_1], &l1) < 1)
		return (M_FAIL);
	if (ft_create_link(graph, graph->tab[hash_1], graph->tab[hash_0], &l2) < 1)
		return (M_FAIL);
	l1->opposite = l2;
	l2->opposite = l1;
	return (1);
}

int		ft_first_link(t_graph *graph, char **line)
{
	char	**tab;
	int		i;

	if (!(tab = ft_strsplit(*line, '-')))
		return (M_FAIL);
	if ((ft_link_link(tab, graph)) < 1)
		return (M_FAIL);
	ft_free_tab(tab);
	ft_strdel(&(*line));
	return (ft_links(graph, 0));
}

int		ft_links(t_graph *graph, int fd)
{
	char	**tab;
	char	*line;
	int		ret;

	ret = 1;
	while (get_next_line(fd, &line) > 0)
	{
		if (!(tab = ft_strsplit(line, '-')))
			return (M_FAIL);
		if (ft_tablen(tab) > 0 && tab[0][0] != '#'
				&& parse_link(graph, tab))
				ret = ft_link_link(tab, graph);
		ft_free_tab(tab);
		ft_strdel(&line);
		if (ret < 1)
			return (ret);
	}
	ft_print_links(graph, graph->start);
	return (1);
}

void	ft_print_links(t_graph *graph, t_node *room)
{
	t_link	*link;
	int		i;

	link = room->links;
	i = 0;
	ft_printf("%d ants will start from : '%s' [H:%d] | Dest : '%s' [H:%d] \n\n", 
			graph->ants, graph->start->name, graph->start->hash, graph->end->name, graph->end->hash);
	ft_printf("check hash : %d\n", jenkins_hash(room->name));
	ft_printf("--- '%s' [H:%d] LINKS --- \n\n", room->name, room->hash);
	while (link)
	{
		ft_printf("Salle connectee n°%d : %s [H:%d]\n", i, link->child->name, link->child->hash);
		link = link->next;
		i++;
	}
	ft_printf("\nThere is %d nodes in the map\n\n", graph->nb_nodes);
}
