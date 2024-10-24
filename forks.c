/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangouil <gangouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:21:40 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/24 17:21:41 by gangouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	is_available(t_philo *philo, int *i)
{
	if (philo->available == true && philo->next->available == true)
	{
		philo->available = false;
		philo->next->available = false;
		philo->state = S_FORK;
		print_state(philo);
		print_state(philo);
		(*i) += 2;
	}
}

static void	take_forks(t_philo *philo, int *i)
{
	if (is_dead(philo))
		return ;
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->next->fork);
	is_available(philo, i);
	pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_unlock(&philo->fork);
}

static void	take_odd_forks(t_philo *philo, int *i)
{
	if (is_dead(philo))
		return ;
	pthread_mutex_lock(&philo->next->fork);
	pthread_mutex_lock(&philo->fork);
	is_available(philo, i);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

void	get_forks(t_philo *philo)
{
	int		i;
	long	start;

	i = 0;
	start = get_time();
	while (i != 2 && !is_dead(philo))
	{
		if (get_time() - start > philo->ctx->time_to_die * 1000)
		{
			set_dead(philo);
			return ;
		}
		if (philo->num % 2 == 0 && philo != philo->next)
			take_forks(philo, &i);
		else if (philo != philo->next)
			take_odd_forks(philo, &i);
	}
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	philo->available = true;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_lock(&philo->next->fork);
	philo->next->available = true;
	pthread_mutex_unlock(&philo->next->fork);
}
