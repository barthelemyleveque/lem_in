/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_graph.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 11:01:50 by bleveque          #+#    #+#             */
/*   Updated: 2019/04/24 13:40:30 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		get_ants(t_graph *graph, int fd)
{
	char	*line;

	get_next_line(fd, &line);
	graph->ants = ft_atoi(line);
	free(line);
	if (graph->ants <= 0)
		return (0);
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

void	ft_fill_node(t_graph *graph, char **tab, t_node *node, int spec)
{
	node->name = ft_strdup(tab[0]);
	node->x_coord = ft_atoi(tab[1]);
	node->y_coord = ft_atoi(tab[2]);
	node->special = spec;
	if (spec == 1)
		graph->start = node;
	else if (spec == 2)
		graph->end = node;
	node->links = NULL;
	//ft_printf("name : %s\n", node->name);
	node->hash = jenkins_hash(node->name);
	//ft_printf("hash %d\n", node->hash);
	while (graph->tab[node->hash])
	{
		//printf("yes and hash is : %d, name : %s\n", node->hash, graph->tab[node->hash]->name);
		node->hash = node->hash < PRIME ? node->hash + 1 : 0;
	}
	graph->tab[node->hash] = node;
	graph->nb_nodes++;
}

// Modifier if (!(tab[1]) car un nom de salle peut avoir des espaces

int		ft_create_node(t_graph *graph, char *line, int spec, int fd)
{
	t_node	*node;
	char	**tab;
	int		i;

	i = -1;
	if (!(tab = ft_strsplit(line, ' ')) || !(node = malloc(sizeof(t_node))))
		return (0);
	if (!(tab[1]))
		return (0);
	ft_fill_node(graph, tab, node, spec);
	while (tab[++i])
		free(tab[i]);
	free(tab);
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
			ret = ft_create_node(graph, line, spec, fd);
			spec = 0;
		}
		if (!(ret))
		{
			ft_first_link(graph, line);
			ft_links(graph, fd);
			return (1);
		}
		free(line);
	}
	return (1);
}

t_graph		*init_graph(char **av)
{
	int		fd;
	t_graph	*graph;

	if (!(graph = (t_graph*)malloc(sizeof(t_graph))))
		return (NULL);
	if (!(graph->tab = (t_node**)malloc(sizeof(t_graph) * PRIME)))
		return (NULL);
	graph->nb_nodes = 0;
	if (!(fd = open(av[1], O_RDONLY)))
		return (0);
	if (!(get_ants(graph, fd)))
		return (0);
	if (!(get_nodes(graph, fd)))
		return (0);
	return (graph);
}


int		main(int ac, char **av)
{
	t_graph		*graph;

	if (ac != 2)
		return (0);
	if (!(graph = init_graph(av)))
		return (0);
	init_bfs(graph);
	return (0);
}
