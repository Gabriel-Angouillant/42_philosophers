/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangouil <gangouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:53:50 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/10 19:54:05 by gangouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_context	t_ctx;

typedef enum e_state
{
	S_SLEEP,
	S_FORK,
	S_EAT,
	S_THINK,
	S_DEAD,
}							t_state;

typedef struct s_philosopher
{
	pthread_mutex_t			fork;
	t_state					state;
	bool					available;
	int						num;
	long					last_eat;
	int						eat_count;
	t_ctx					*ctx;
	struct s_philosopher	*next;
}							t_philo;

typedef struct s_context
{
	pthread_mutex_t			print_m;
	pthread_mutex_t			dead_m;
	bool					is_dead;
	long					start_time;
	long					philo_count;
	long					time_to_die;
	long					time_to_eat;
	long					time_to_sleep;
	long					max_eat;
}							t_ctx;

t_ctx						*init_ctx(int argc, char **argv);
t_philo						*create_philos(t_ctx *ctx);

void						*start_routines(void *philo_v);
void						get_forks(t_philo *philo);
void						release_forks(t_philo *philo);

void						print_state(t_philo *philo);
long						get_time(void);
bool						is_dead(t_philo *philo);
void						set_dead(t_philo *philo);

t_philo						*ft_lstnew(int num, t_state state, t_philo *next);
t_philo						*ft_lstlast(t_philo *lst);
void						ft_lstadd_back(t_philo **lst, t_philo *new);
void						ft_lstadd_front(t_philo **lst, t_philo *new);
void						ft_lstclear(t_philo *lst, int philo_count);

#endif