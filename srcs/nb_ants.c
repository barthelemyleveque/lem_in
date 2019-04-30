/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nb_ants.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <bleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:06:21 by bleveque          #+#    #+#             */
/*   Updated: 2019/04/30 19:01:54 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <limits.h>


/*
** Quid de rajouter un nb_fourmis dans la structure paths pour suive ?
*/

int		number_of_steps(t_path **tab_paths, int nb_chemins, int ants)
{
	int		nb_steps;
	int		i;
	
	nb_steps = 0;
	if (nb_chemins == 1)
	{
		tab_paths[0]->nb_ants = ants;
		return (tab_paths[0]->nb_ants + tab_paths[0]->len);
	}
	while (ants > 0)
	{
		i = 0;
		while (i < nb_chemins && ants > 0)
		{
			if (i == nb_chemins - 1)
			{
				if (tab_paths[i]->len + tab_paths[i]->nb_ants <= 
						tab_paths[i - 1]->len + tab_paths[i - 1]->nb_ants)
				{
					ants--;
					tab_paths[i]->nb_ants += 1;
				}
			}
			else if (tab_paths[i]->len + tab_paths[i]->nb_ants <= 
					tab_paths[i + 1]->len + tab_paths[i + 1]->nb_ants)
			{
				ants--;
				tab_paths[i]->nb_ants += 1;
			}
			i++;
		}
	}
	return (tab_paths[0]->nb_ants + tab_paths[0]->len);
}	

/*
** On va calculer le nombre de steps requis pour chaque combinaison de chemin
** en fonction du nombre de fourmis. Et return la combinaison la plus rapide.
*/

void	find_best_path(t_graph *graph, t_edmond *edmond)
{
	int		steps;
	int		ants;
	int 	tmp_steps;
	int		edmond_nb;

	ants = graph->ants;
	tmp_steps = INT_MAX;
	while (edmond)
	{
		steps = number_of_steps(edmond->tab_paths, edmond->nb_chemin, ants);
		//print_tab_paths(edmond->tab_paths, edmond->nb_chemin, ants);
		if (steps < tmp_steps)
		{
			edmond_nb = edmond->nb_chemin;
			tmp_steps = steps;
		}
		edmond = edmond->next;
	}
}
