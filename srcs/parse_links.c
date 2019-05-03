/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrewrzepecki <anrzepec@student.42.f      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 23:02:55 by andrewrze         #+#    #+#             */
/*   Updated: 2019/05/03 23:40:54 by andrewrze        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		parse_link(t_graph *g, char **tab)
{
	int	i;
	int	link;

	i = 0;
	link = 0;
	if (ft_tablen(tab) != 2)
		return (0);
	while (i < PRIME)
	{
		if (g->tab[i] && !ft_strcmp(g->tab[i]->name, tab[0]))
			link++;
		else if (g->tab[i] && !ft_strcmp(g->tab[i]->name, tab[1]))
			link++;
		i++;
	}
	if (link == 2)
		return (1);
	return (0);
}
