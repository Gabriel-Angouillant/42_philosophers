/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangouil <gangouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 21:07:01 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/10 21:07:08 by gangouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec);
}

void	set_dead(t_philo *philo)
{
	philo->state = S_DEAD;
	print_state(philo);
	pthread_mutex_lock(&philo->ctx->dead_m);
	philo->ctx->is_dead = true;
	pthread_mutex_unlock(&philo->ctx->dead_m);
}

bool	is_dead(t_philo *philo)
{
	bool	dead;

	if (get_time() - philo->last_eat > philo->ctx->time_to_die * 1000)
	{
		set_dead(philo);
		return (1);
	}
	pthread_mutex_lock(&philo->ctx->dead_m);
	dead = philo->ctx->is_dead;
	pthread_mutex_unlock(&philo->ctx->dead_m);
	return (dead);
}

void	print_state(t_philo *philo)
{
	long	time;
	int		dead;

	pthread_mutex_lock(&philo->ctx->print_m);
	time = (get_time() - philo->ctx->start_time) / 1000;
	pthread_mutex_lock(&philo->ctx->dead_m);
	dead = philo->ctx->is_dead;
	pthread_mutex_unlock(&philo->ctx->dead_m);
	if (!dead && philo->state == S_DEAD)
		printf("%ld %d died\n", time, philo->num);
	else if (!dead && philo->state == S_SLEEP)
		printf("%ld %d is sleeping\n", time, philo->num);
	else if (!dead && philo->state == S_FORK)
		printf("%ld %d has taken a fork\n", time, philo->num);
	else if (!dead && philo->state == S_EAT)
		printf("%ld %d is eating\n", time, philo->num);
	else if (!dead && philo->state == S_THINK)
		printf("%ld %d is thinking\n", time, philo->num);
	pthread_mutex_unlock(&philo->ctx->print_m);
}
