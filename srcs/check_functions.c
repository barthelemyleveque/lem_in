/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <bleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 11:05:25 by bleveque          #+#    #+#             */
/*   Updated: 2019/05/07 17:03:11 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void check_multiple_rooms(t_graph *graph, t_edmond *edmond)
{
	int		i;
	int		j;
	int		*tab;
	t_path	*path;

	i = -1;
	tab = malloc(sizeof(int) * PRIME);
	while (++i < PRIME)
		tab[i] = -1;
	i = -1;
	while (++i < edmond->nb_chemin)
	{
		path = edmond->tab_paths[i]->next;
		while (path->node != graph->end)
		{
			j = -1;
			//ft_printf("%s is checked\n", path->node->name);
			while (tab[++j] != -1)
			{
				if (path->node->hash == tab[j])
					ft_printf("Room : %s is multiple\n", path->node->name);
			}
			tab[j] = path->node->hash;
			path = path->next;
		}
	}
	ft_printf("Check des multiple rooms done\n");
}
