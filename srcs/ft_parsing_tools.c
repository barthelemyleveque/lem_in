/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrzepec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:43:02 by anrzepec          #+#    #+#             */
/*   Updated: 2019/04/26 14:10:35 by anrzepec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_free_tab(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
		ft_strdel(&tab[i]);
	free(tab);
}

int			ft_tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;	
	return (i);
}
