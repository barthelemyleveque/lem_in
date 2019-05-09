/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrewrzepecki <anrzepec@student.42.f      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 19:41:15 by andrewrze         #+#    #+#             */
/*   Updated: 2019/05/09 13:00:30 by bleveque         ###   ########.fr       */
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

int			ft_push_from_start(t_edmond *res, int ant, int ret, int space)
{
	int i;

	i = -1;
	while (++i < res->nb_chemin)
	{
		if (res->tab_paths[i]->nb_ants)
		{
			res->tab_paths[i]->next->node->curr_ant = ant;
			res->tab_paths[i]->nb_ants--;
			if (space)
				ft_printf(" ");
			ft_printf("L%d-%s", res->tab_paths[i]->next->node->curr_ant, res->tab_paths[i]->next->node->name);
			ant++;
			ret = 1;
			space = 1;
		}
	}
	if (ret)
		ft_putendl("");
	return (ant);
}

void		ft_push_paths(t_path *path, int *ret, int *space)
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
			{
				if (*space)
					ft_printf(" ");
				ft_printf("L%d-%s", tracer->node->curr_ant, tracer->node->name);
				*ret = 1;
				*space = 1;
			}
		}
		tracer = tracer->next;
	}
}

void		ft_push_ants(t_graph *g, t_edmond *res, int ant)
{
	int i;
	int	ret;
	int	space;

	i = -1;
	ret = 0;
	space = 0;
	while (++i < res->nb_chemin)
		ft_push_paths(res->tab_paths[i], &ret, &space);
	ant = ft_push_from_start(res, ant, ret, space);
	if (ft_recuring_probe(res))
		ft_push_ants(g, res, ant);
}
