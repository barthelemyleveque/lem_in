/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrewrzepecki <anrzepec@student.42.f      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 23:02:55 by andrewrze         #+#    #+#             */
/*   Updated: 2019/05/09 20:24:21 by anrzepec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		duplicate_link(t_node *node, char *name1)
{
	t_link *tracer;

	tracer = node->links;
	while (tracer)
	{
		ft_printf("%s and %s\n", tracer->child->name, name1);
		if (!ft_strcmp(tracer->child->name, name1))
			return (0);
		tracer = tracer->next;
	}
	return (1);
}

int		parse_link(t_graph *g, char **tab)
{
	int	i;
	int	link;

	i = 0;
	link = 0;
	if (ft_tablen(tab) != 2)
		return (LINK_ERROR);
	while (i < PRIME)
	{
		// to add duplicate link checker
		if (g->tab[i] && !ft_strcmp(g->tab[i]->name, tab[0]) && duplicate_link(g->tab[i], tab[1]))
			link++;
		else if (g->tab[i] && !ft_strcmp(g->tab[i]->name, tab[1]) && duplicate_link(g->tab[i], tab[0]))
			link++;
		i++;
	}
	ft_printf("links: %d\n", link);
	if (link == 2)
		return (1);
	return (LINK_ERROR);
}
