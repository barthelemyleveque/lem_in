/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_graph.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 11:01:50 by bleveque          #+#    #+#             */
/*   Updated: 2019/05/09 17:10:57 by anrzepec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		get_ants(t_graph *graph, int fd, char **line)
{
	if (get_next_line(fd, &(*line)) < 1)
		return (A_FAIL);
	if (!ft_number_arg((*line)))
		return (A_FAIL);
	if ((graph->ants = (int)ft_atoll(*line)) < 1)
		return (A_FAIL);
	ft_putendl(*line);
	ft_strdel(&(*line));
	*line = NULL;
	return (1);
}

int		jenkins_hash(char *name)
{
	int				i;
	unsigned int	hash;

	i = 0;
	hash = 0;
	while (name[i] != '\0')
	{
		hash += name[i++];
		hash += hash << 10;
		hash += hash >> 6;
	}
	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;
	hash = hash % PRIME;
	return (hash);
}

int		ft_fill_node(t_graph *graph, char **tab, t_node *node, int spec)
{
	int		ret;

	if ((ret = parse_node(graph, tab, node, spec)) < 1)
		return (ret);
	node->links = NULL;
	node->curr_ant = -1;
	node->hash = jenkins_hash(tab[0]);
	while (graph->tab[node->hash])
		node->hash = node->hash < PRIME ? (node->hash + 1) : 0;
	graph->tab[node->hash] = node;
	graph->nb_nodes++;
	return (1);
}

// Modifier declaration de *node dans fill_node pour leaks en cas d'erreurs 

int		ft_create_node(t_graph *graph, char *line, int spec, int fd)
{
	t_node	*node;
	char	**tab;
	int		ret;

	if (!(tab = ft_strsplit(line, ' ')) || !(node = malloc(sizeof(t_node))))
		return (M_FAIL);
	if ((ret = ft_tablen(tab)) == 1 || (ret = ft_tablen(tab)) != 3)
	{
		free(node);
		ft_free_tab(tab);
		return (ret);
	}
	if (ft_fill_node(graph, tab, node, spec) < 1)
	{
		ft_free_tab(tab);
		free(node);
		return (N_FAIL);
	}
	ft_putendl(line);
	ft_free_tab(tab);
	return (0);
}

int		get_nodes(t_graph *graph, int fd, char **line)
{
	int		spec;
	int		ret;

	ret = 1;
	spec = 0;
	while (get_next_line(fd, &(*line)))
	{
		if (*line && (*line)[0] == '#')
			spec = ft_parse_comment(*line);
		else if (*line)
		{
			if ((ret = ft_create_node(graph, *line, spec, fd)) == 1)
				return (ft_first_link(graph, line));
			else if (!ret)
				spec = ret;
			else
				return ((ret = (ret > 1) ? NODE_PERROR : ret));
		}
		ft_strdel(&(*line));
		*line = NULL;
	}
	return (1);
}

int		init_graph(char **av, t_graph *graph)
{
	int		i;
	int		ret;
	char	*line;

	line = NULL;
	if (!(graph->tab = (t_node**)malloc(sizeof(t_node*) * PRIME)))
		return (M_FAIL);
	i = -1;
	while (++i < PRIME)
		graph->tab[i] = NULL;
	graph->nb_nodes = 0;
	graph->start = NULL;
	graph->end = NULL;
	if ((ret = get_ants(graph, 0, &line)) < 1)
	{
		ft_strdel(&line);
		return (ret);
	}
	if ((ret = get_nodes(graph, 0, &line)) < 1)
	{
		ft_strdel(&line);
		return (ret);
	}
	return (1);
}

int		valid_graph(t_graph *g)
{
	int	*map;

	if (!g->start || !g->end)
		return (0);
	if (!(map = (int*)malloc(sizeof(int) * PRIME)))
		return (0);
	reinit_tabs(map, PRIME);
	if (bfs_launcher(g, map) == 1)
	{
		free(map);
		return (1);
	}
	free(map);
	return (0);
}

int		main(int ac, char **av)
{
	int			ret;
	t_graph		graph;

	if ((ret = init_graph(av, &graph)) < 1)
		return (ret);
	if (valid_graph(&graph))
	{
		ft_putendl("");
		init_bfs(&graph);
	}
	else
		ft_putendl("INVALID GRAPH");
	return (0);
}
