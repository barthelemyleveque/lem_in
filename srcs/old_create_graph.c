/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_graph.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 11:01:50 by bleveque          #+#    #+#             */
/*   Updated: 2019/04/22 12:22:12 by bleveque         ###   ########.fr       */
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

int		get_nodes(t_graph *graph, int fd)
{
	t_node *new_node;
	char	*line;
	int		spec;
	int 	links;
	
	while (get_next_line(fd, &line) && !(ft_strchr(line, ' ')))
	{
		spec = 0;
		if (!(ft_strcmp(line, "##start")))
			spec = 1;
		else if (!(ft_strcmp(line, "##end")))
			spec = 2;
		else if (line[0] != '#')
			ft_create_node(&new_node, line, spec);
		free(line);
	}
	return (1);
}

t_graph		*init_graph(char **av)
{
	int		fd;
	t_graph	*graph;

	if (!(graph = malloc(sizeof(t_graph))))
		return (NULL);
	if (!(fd = open(av[1], O_RDONLY)))
		return (0);
	if (!(get_ants(graph, fd)))
		return (0);
	if (!(get_nodes(graph, fd)))
		return (0);
	ft_printf("%d\n", graph->ants);
	return (graph);
}


int		main(int ac, char **av)
{
	t_graph		*graph;

	if (ac != 2)
		return (0);
	if (!(graph = init_graph(av)))
		return (0);
	return (0);
}
