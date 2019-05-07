/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 12:13:49 by bleveque          #+#    #+#             */
/*   Updated: 2019/05/07 16:53:39 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_path(t_path *path)
{
	int 	i;

	i = 0;
	ft_printf("(Len of this path : %d)\n\n", path->len);
	while (path)
	{
		ft_printf("node num %d : %s\n", i, path->node->name);
		i++;
		path = path->next;
	}
}

void	print_tab_paths(t_path **tab_paths, int len, int nb_ants)
{
	int 	i;
	int		y;
	t_path	*path;

	y = -1;
	while (++y < len)
	{
		path = tab_paths[y];
		i = 0;
		ft_printf("---- PATH %d of %d -----\n\n", y + 1, len); 
		ft_printf("(Len of this path : %d)\n", path->len);
		ft_printf("Ants going through : %d\n", path->nb_ants);
		while (path)
		{
			ft_printf("node num %d : %s\n", i, path->node->name);
			i++;
			path = path->next;
		}
		ft_printf("\n\n");
	}
}

t_path	*get_path(t_graph *graph, int *parent_map)
{
	int		node;
	int		introduced_by;
	t_path	*path;
	t_path	*tmp;

	if (!(path = (t_path*)malloc(sizeof(t_path))))
		return (NULL);
	node = graph->end->hash;
	path->node = graph->end;
	path->next = NULL;
	while (graph->start->hash != node)
	{
		introduced_by = parent_map[node];
		if (!(tmp = (t_path*)malloc(sizeof(t_path))))
			return (NULL);
		tmp->node = graph->tab[introduced_by];
		tmp->next = path;
		node = introduced_by;
		path = tmp;
	}
	return (path);
}

/*
** Rajouter flow oppose dans le cas ou 1 | 1 s'annulent 
** Modifier pour avoir le lien oppose direct la on comprend R
*/

void	ek_update_flux(t_graph *graph, t_path *path)
{
	t_node	*next;
	t_link	*link_update;
	t_path	*tmp;
	
	while (path->next)
	{
		link_update = path->node->links;
		next = path->next->node;
		while (link_update->child != next)
			link_update = link_update->next;
		link_update->flow += 1;
		link_update->opposite->flow -= 1;
		//ft_printf("parent [%s] to child [%s] flow = %d closed : %d\n", path->node->name, link_update->child->name, link_update->flow, link_update->closed);
		//ft_printf("child [%s] to parent [%s] flow = %d closed : %d\n", link_update->child->name, path->node->name, link_update->opposite->flow, link_update->opposite->closed);
		tmp = path;
		path = path->next;
		free(tmp);
	}
}
