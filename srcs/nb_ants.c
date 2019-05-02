/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nb_ants.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <bleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:06:21 by bleveque          #+#    #+#             */
/*   Updated: 2019/05/02 11:07:30 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <limits.h>


/*
** Le but est d'avoir + ou - le meme nombre de steps par chemin (len du chemin +
** nb de fourmis dans ce chemin) dans une strcture a n chemins.
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
		i = -1;
		while (++i < nb_chemins && ants > 0)
		{
			if (i == nb_chemins - 1 && tab_paths[i]->len + tab_paths[i]->nb_ants 
				<= tab_paths[i - 1]->len + tab_paths[i - 1]->nb_ants)
				{
					ants--;
					tab_paths[i]->nb_ants += 1;
				}
			else if (i != nb_chemins - 1 && 
					tab_paths[i]->len + tab_paths[i]->nb_ants <= 
					tab_paths[i + 1]->len + tab_paths[i + 1]->nb_ants)
				{
					ants--;
					tab_paths[i]->nb_ants += 1;
				}
		}
	}
	return (tab_paths[0]->nb_ants + tab_paths[0]->len);
}	

/*
** On va calculer le nombre de steps requis pour chaque combinaison de chemin
** en fonction du nombre de fourmis. Et return la struct Edmond la plus rapide.
*/

t_edmond		*find_best_path(t_graph *graph, t_edmond *edmond)
{
	int			steps;
	int			ants;
	int 		tmp_steps;
	int			edmond_nb;
	t_edmond	*tmp;

	ants = graph->ants;
	tmp = edmond;
	tmp_steps = INT_MAX;
	while (tmp)
	{
		steps = number_of_steps(tmp->tab_paths, tmp->nb_chemin, ants);
		if (steps < tmp_steps) // rajouter condition : pas de chemin a 0 ants
		{
			edmond_nb = tmp->nb_chemin;
			tmp_steps = steps;
		}
		tmp = tmp->next;
	}
	tmp = edmond;
	while (tmp->nb_chemin != edmond_nb)
		tmp = tmp->next;
	return (tmp);
}

/*
** Ants in My pants = va lancer toute la machine
*/ 

void	ants_in_my_pants(t_graph *graph, t_edmond *edmond)
{
	t_edmond	*best_edmond;
	int			steps;

	best_edmond = find_best_path(graph, edmond);
	steps = best_edmond->tab_paths[0]->len + best_edmond->tab_paths[0]->nb_ants;
	ft_printf("\n\n>>> %d fourmis parcoureront %d chemins en %d steps <<<\n\n",
			graph->ants, best_edmond->nb_chemin, steps);
	print_tab_paths(best_edmond->tab_paths, best_edmond->nb_chemin, graph->ants);
	// ON A LA MEILLEURE COMBINAISON DE FOURMIS MAINTENANT COMMENT SUIVRE LES
	// FOURMIS AU FUR ET A MESURE QU'ELLES TRAVERSENT LE GRAPH ?

	// A CODER :print_results(best_edmond)
}
