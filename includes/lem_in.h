/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 11:00:20 by bleveque          #+#    #+#             */
/*   Updated: 2019/04/23 17:44:32 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/libft.h"
# include "../libft/header.h"
# include "../libft/get_next_line.h"
# define PRIME 9931

/*
** Structures pour construire le graph :
** t_link = liste des child_nodes d'une salle, et leur flow 
********************************************   -> ou capacite ?
** t_node = le node et ses caracteristiques
** t_graph = le graph, contenant un tableau des nodes indexes via leur hash
** ainsi que les valeurs clees : start, end
*/

typedef struct		s_link
{
	int				flow;
	struct s_node	*child;
	struct s_link	*next;
}					t_link;

typedef struct		s_node
{
	int				hash;
	int				x_coord;
	int				y_coord;
	int				special; // 0 node / 1 start / 2 end
	char			*name;
	struct s_link	*links;
}					t_node;

typedef struct		s_graph
{
	int				ants;
	int				nb_nodes;
	struct s_node	*start;
	struct s_node	*end;
	struct s_node	**tab;
}					t_graph;

/*
** Structures pour le BFS :
** t_queue  = quel node doit etre visite ensuite (indispensable)
** t_parent = quel node(n0) a introduit ce node(n1) , grace au hash
*/ 

typedef struct		s_queue
{
	struct s_node	*node;
	struct s_queue	*next;
}					t_queue;

typedef struct		s_parent
{
	int				h_node;
	int				h_introby;
	struct s_parent	*next;
}					t_parent;

/* WIP : Structures pour garder en memoire chaque chemin parcouru lors de
** chaque BFS

typedef struct		s_path
{
	int				len;
	struct s_node	*node;
	struct s_path	*next;
}					t_path;

typedef struct		s_edmond
{
	int				iteration;
	int				flow;
	struct s_path	*path;
	struct s_edmond	*next;
}					t_edmond;
*/

int		ft_first_link(t_graph *graph, char *line);
int		ft_links(t_graph *graph, int fd);
int		jenkins_hash(char *name);
void	ft_print_links(t_graph *graph, t_node *room);
int		init_bfs(t_graph *graph);

#endif
