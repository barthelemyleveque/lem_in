/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 18:46:51 by bleveque          #+#    #+#             */
/*   Updated: 2019/04/23 17:44:28 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** flow pour les liens vers start = -2 pour eviter de revenir a la source ?
*/

int		ft_create_link(t_graph *graph, t_node *parent, t_node *enfant)
{
	t_link	*link;
	t_link	*tmp;

	if (!(link = (t_link*)malloc(sizeof(t_link))))
		return (0);
	link->flow = (enfant == graph->start) ? -2 : 0;
	link->child = enfant;
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
	return (1);
}

/*
** Verifier qu'on ne tombe pas sur une collision grace a la valeur de hash dans
** le noeud (cf : fonction ft_fill_node)
*/ 

int		ft_link_link(char **tab, t_graph *graph)
{
	int	hash_0;
	int hash_1;

	hash_0 = jenkins_hash(tab[0]);
	hash_1 = jenkins_hash(tab[1]);
	while (graph->tab[hash_0]->hash != hash_0)
		hash_0 = hash_0 < PRIME ? hash_0 + 1 : 0;
	while (graph->tab[hash_1]->hash != hash_1)
		hash_1 = hash_1 < PRIME ? hash_1 + 1 : 0;
	//ft_printf("hash 0 : %s hash 1 : %s\n", graph->tab[hash_0]->name, graph->tab[hash_1]->name);
	if (!(ft_create_link(graph, graph->tab[hash_0], graph->tab[hash_1])))
		return (0);
	if (!(ft_create_link(graph, graph->tab[hash_1], graph->tab[hash_0])))
		return (0);
	return (1);
}

int		ft_first_link(t_graph *graph, char *line)
{
	char	**tab;
	int		i;

	i = -1;
	if (!(tab = ft_strsplit(line, '-')))
		return (0);
	if (!(ft_link_link(tab, graph)))
		return (0);
	while (tab[++i])
		free(tab[i]);
	free(tab);
	free(line);
	return (1);
}

int		ft_links(t_graph *graph, int fd)
{
	char	**tab;
	int		i;
	char	*line;

	while (get_next_line(fd, &line))
	{
		i = -1;
		if (!(tab = ft_strsplit(line, '-')))
			return (0);
		if (tab[0][0] != '#')
			if (!(ft_link_link(tab, graph)))
				return (0);
		while (tab[++i])
			free(tab[i]);
		free(tab);
		free(line);
	}
	ft_print_links(graph, graph->start);
	return (1);
}

void	ft_print_links(t_graph *graph, t_node *room)
{
	t_link	*link;
	int		i;

	link = room ->links;
	i = 0;
	ft_printf("%d ants will start from : '%s' [H:%d] | Dest : '%s' [H:%d] \n\n", 
			graph->ants, graph->start->name, graph->start->hash, graph->end->name, graph->end->hash);
	ft_printf("--- '%s' [H:%d] LINKS --- \n\n", room->name, room->hash);
	while (link)
	{
		ft_printf("Salle connectee n°%d : %s [H:%d]\n", i, link->child->name, link->child->hash);
		link = link->next;
		i++;
	}
	ft_printf("\nThere is %d nodes in the map\n\n", graph->nb_nodes);
}
