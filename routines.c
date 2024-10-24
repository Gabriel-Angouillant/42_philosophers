/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangouil <gangouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:12:11 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/24 17:12:12 by gangouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	spend_time(t_philo *philo, long us)
{
	long	start;

	if (is_dead(philo))
		return ;
	start = get_time();
	while (get_time() - start < us)
	{
		if (is_dead(philo))
			return ;
		usleep(64);
		if (get_time() - start > philo->ctx->time_to_die * 1000)
		{
			set_dead(philo);
			return ;
		}
	}
}

static void	sleep_routine(t_philo *philo)
{
	if (is_dead(philo))
		return ;
	philo->state = S_SLEEP;
	if (is_dead(philo))
		return ;
	print_state(philo);
	if (is_dead(philo))
		return ;
	spend_time(philo, philo->ctx->time_to_sleep * 1000);
	if (is_dead(philo))
		return ;
	usleep(128);
}

static void	eat_routine(t_philo *philo)
{
	if (is_dead(philo))
		return ;
	get_forks(philo);
	philo->state = S_EAT;
	if (is_dead(philo))
		return ;
	print_state(philo);
	if (is_dead(philo))
		return ;
	philo->last_eat = get_time();
	spend_time(philo, philo->ctx->time_to_eat * 1000);
	release_forks(philo);
	if (is_dead(philo))
		return ;
}

void	*start_routines(void *philo_v)
{
	t_philo	*philo;

	philo = (t_philo *)philo_v;
	philo->last_eat = get_time();
	if (philo->num % 2 == 0)
		usleep(128);
	while (philo->ctx->max_eat == -1 || philo->eat_count < philo->ctx->max_eat)
	{
		philo->state = S_THINK;
		print_state(philo);
		eat_routine(philo);
		if (is_dead(philo))
			return (philo_v);
		sleep_routine(philo);
		if (is_dead(philo))
			return (philo_v);
		philo->eat_count++;
	}
	return (philo_v);
}
