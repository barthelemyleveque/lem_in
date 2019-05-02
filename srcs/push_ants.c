/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrewrzepecki <anrzepec@student.42.f      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 19:41:15 by andrewrze         #+#    #+#             */
/*   Updated: 2019/05/02 21:26:48 by andrewrze        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			ft_recuring_probe(t_edmond *e)
{
	int		i;
	t_path	*tracer;

	i = -1;
	while (++i < e->nb_chemin)
	{
		tracer = e->tab_paths[i];
		while (tracer)
		{
			if (tracer->node->curr_ant != -1)
				return (1);
			tracer = tracer->next;
		}
	}
	return (0);
}

int			ft_push_from_start(t_edmond *res, int ant)
{
	int i;

	i = -1;
	while (++i < res->nb_chemin)
	{
		if (res->tab_paths[i]->nb_ants)
		{
			res->tab_paths[i]->next->node->curr_ant = ant;
			res->tab_paths[i]->nb_ants--;
			printf("L%d-%s ", res->tab_paths[i]->next->node->curr_ant, res->tab_paths[i]->next->node->name);
			ant++;
		}
	}
	return (ant);
}

void		ft_push_paths(t_path *path)
{
	t_path	*tracer;
	int		tmp;
	int		first;
	int		c_tmp;

	tracer = path;
	tmp = -1;
	first = 1;
	while (tracer)
	{
		if (tracer->node->curr_ant != -1 || !first)
		{
			c_tmp = tracer->node->curr_ant;
			tracer->node->curr_ant = tmp;
			tmp = c_tmp;
			first = 0;
			if (tracer->node->curr_ant != -1)
				ft_printf("L%d-%s ", tracer->node->curr_ant, tracer->node->name);
		}
		tracer = tracer->next;
	}
}

void		ft_push_ants(t_graph *g, t_edmond *res, int ant)
{
	int i;

	i = -1;
	while (++i < res->nb_chemin)
		ft_push_paths(res->tab_paths[i]);
	ant = ft_push_from_start(res, ant);
	printf("\n");
	if (ft_recuring_probe(res))
		ft_push_ants(g, res, ant);
}
