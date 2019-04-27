/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_graph.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 11:01:50 by bleveque          #+#    #+#             */
/*   Updated: 2019/04/27 16:06:27 by anrzepec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		get_ants(t_graph *graph, int fd)
{
	char	*line;

	get_next_line(fd, &line);
	if (!ft_strnum(line))
		return (A_FAIL);
	graph->ants = ft_atoi(line);
	free(line);
	if (graph->ants <= 0)
		return (A_FAIL);
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
	if (!ft_strnum(tab[1]) || !ft_strnum(tab[2]))
	{
		ft_free_tab(tab);
		return (0);
	}
	node->name = ft_strdup(tab[0]);
	node->x_coord = ft_atoi(tab[1]);
	node->y_coord = ft_atoi(tab[2]);
	node->visited = 0;
	node->special = spec;
	if (spec == 1)
		graph->start = node;
	else if (spec == 2)
		graph->end = node;
	node->links = NULL;
	//ft_printf("name : %s\n", node->name);
	node->hash = jenkins_hash(node->name);
	//ft_printf("hash %d\n", node->hash);
	printf("node->hash: %d\n", node->hash);
	while (graph->tab[node->hash])
	{
		//printf("yes and hash is : %d, name : %s\n", node->hash, graph->tab[node->hash]->name);
		node->hash = node->hash < PRIME ? node->hash + 1 : 0;
	}
	graph->tab[node->hash] = node;
	graph->nb_nodes++;
	return (1);
}

// Modifier declaration de *node dans fill_node pour leaks en cas d'erreurs 

int		ft_create_node(t_graph *graph, char *line, int spec, int fd)
{
	t_node	*node;
	char	**tab;

	if (!(tab = ft_strsplit(line, ' ')) || !(node = malloc(sizeof(t_node))))
	{
		ft_strdel(&line);
		return (M_FAIL);
	}
	if (ft_tablen(tab) == 1)
	{
		printf("tab[0]: %s\n", tab[0]);
		ft_free_tab(tab);
		return (0);
	}
	if (ft_tablen(tab) != 3)
	{
		ft_strdel(&line);
		ft_free_tab(tab);
		return (N_FAIL);
	}
	if (!ft_fill_node(graph, tab, node, spec))
		return (N_FAIL);
	ft_free_tab(tab);
	return (1);
}

int		get_nodes(t_graph *graph, int fd)
{
	char	*line;
	int		spec;
	int 	links;
	int		ret;

	ret = 1;
	spec = 0;
	while (get_next_line(fd, &line))
	{
		if (!(ft_strcmp(line, "##start")))
			spec = 1;
		else if (!(ft_strcmp(line, "##end")))
			spec = 2;
		else if (line[0] != '#')
		{
			if ((ret = ft_create_node(graph, line, spec, fd)) < 0)
				return (ret);
			spec = 0;
		}
		if (!(ret))
		{
			if ((ret = ft_first_link(graph, line)) > 0)
				ret = ft_links(graph, fd);
			return (ret);
		}
		free(line);
		if (ret < 1)
			return (ret);
	}
	return (1);
}

int		init_graph(char **av, t_graph *graph)
{
	int		i;
	int		fd;
	int		ret;

	i = -1;
	if (!(graph->tab = (t_node**)malloc(sizeof(t_node*) * PRIME)))
		return (M_FAIL);
	while (++i < PRIME)
		graph->tab[i] = NULL;
	graph->nb_nodes = 0;
	if (!(fd = open(av[1], O_RDONLY)))
		return (O_FAIL);
	if ((ret = get_ants(graph, fd)) < 1)
		return (ret);
	if ((ret = get_nodes(graph, fd)) < 1)
		return (ret);
	return (1);
}


int		main(int ac, char **av)
{
	int			ret;
	t_graph		graph;

	if (ac != 2)
		return (0);
	if ((ret = init_graph(av, &graph)) < 1)
		return (ret);
	init_bfs(&graph);
	return (0);
}
