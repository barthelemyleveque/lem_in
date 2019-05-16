/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <bleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:41:28 by bleveque          #+#    #+#             */
/*   Updated: 2019/05/16 16:39:37 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/libft.h"
# include "../libft/header.h"
# include "../libft/get_next_line.h"
# define PRIME 9931

/* ERROR RETURNS */
# define _MIN_INT_			-2147483648
# define _MAX_INT_			2147483647
# define LINK_ERROR			0
# define M_FAIL 			-1
# define O_FAIL				-2
# define A_FAIL				-3
# define NODE_ERROR			-4
# define NODE_ERROR_NAME	-5
# define NODE_ERROR_CORD	-6
# define END_ERROR			-7
# define START_ERROR		-8
# define NO_IO				-9

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
	int				closed;
	struct s_link	*opposite;
	struct s_node	*child;
	struct s_link	*next;
}					t_link;

typedef struct		s_node
{
	int				hash;
	int				curr_ant;
	int				visited;
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
** Structure pour le BFS :
** t_queue  = quel node doit etre visite ensuite (indispensable)
*/ 

typedef struct		s_queue
{
	struct s_node	*node;
	struct s_queue	*next;
}					t_queue;

/* WIP : Structures pour garder en memoire chaque chemin parcouru lors de
** chaque BFS
*/

typedef struct		s_path
{
	int				len;
	int				nb_ants;
	struct s_node	*node;
	struct s_path	*next;
}					t_path;

typedef struct		s_edmond
{
	int				nb_chemin;
	struct s_path	**tab_paths;
	struct s_edmond	*next;
}					t_edmond;

int			init_graph(t_graph *g);
int			ft_first_link(t_graph *graph, char **line);
int			ft_links(t_graph *graph, int fd, char **line);
int			jenkins_hash(char *name);
void		ft_print_links(t_graph *graph, t_node *room);
int			init_bfs(t_graph *graph);
int			bfs_launcher(t_graph *graph, int *parent_map);
void		add_to_visited(t_link *link, int *tab);
int			add_to_queue(t_link *link, t_queue *queue);
void		add_to_parent_map(t_node *pos, t_link *link, int *map);
int 		is_visited(t_link *link, t_node *node, int *map, t_graph *graph);
t_queue		*init_queue();
t_path		*get_path(t_graph *graph, int *parent_map);
void		ek_update_flux(t_path *path);
void		reinit_tabs(int *map, int len_map);
t_edmond	*update_edmond(t_graph *graph, t_edmond *old_eddy, int boucle);
void		print_path(t_path *path);
void		check_multiple_rooms(t_graph *graph, t_edmond *edmond);
void		ants_in_my_pants(t_graph *graph, t_edmond *edmond);
void		print_tab_paths(t_path **tab_paths, int len, int nb_ants);
void		ft_push_ants(t_graph *g, t_edmond *res, int ant);
int			queue_free(t_queue *queue, int **visited);

/*  PARSING TOOLS  */
int			parse_link(t_graph *g, char **tab);
int			parse_node(t_graph *g, char **tab, t_node *node, int spec);
int			ft_parse_comment(char *s);
int			ft_number_arg(char *s);
int			ft_tablen(char **tab);
void		ft_free_tab(char **tab);

int			return_error(int err, t_graph *g);
void		free_graph(t_graph *g);
void		free_edmond(t_edmond *edmond);
void		free_paths(t_path **tab, int len);
#endif
