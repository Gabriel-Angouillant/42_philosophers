/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangouil <gangouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:51:31 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/10 19:51:34 by gangouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	kill_philos(t_philo *philo, t_ctx *ctx)
{
	ft_lstclear(philo, ctx->philo_count);
	pthread_mutex_destroy(&ctx->print_m);
	pthread_mutex_destroy(&ctx->dead_m);
	free(ctx);
}

static void	lock_execution(pthread_t *tids)
{
	int	i;

	i = 0;
	while (tids[i])
	{
		pthread_join(tids[i], NULL);
		i++;
	}
	free(tids);
}

static int	start_philos(t_philo *philo, int philo_count)
{
	int			i;
	pthread_t	*tids;

	i = 1;
	tids = malloc((philo_count + 1) * sizeof(pthread_t));
	if (!tids)
		return (0);
	philo->ctx->start_time = get_time();
	while (i <= philo_count)
	{
		pthread_create(&tids[i - 1], NULL, start_routines, (void *)philo);
		i++;
		philo = philo->next;
	}
	tids[i - 1] = 0;
	lock_execution(tids);
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_ctx	*ctx;

	if (argc != 5 && argc != 6)
		return (1);
	philo = NULL;
	ctx = init_ctx(argc, argv);
	if (!ctx)
		return (1);
	if (ctx->time_to_die < 0 || ctx->time_to_eat < 0 || ctx->time_to_sleep < 0
		|| ctx->philo_count <= 0 || ctx->max_eat < -1)
	{
		write(2, "Error: invalid command\n", 23);
		kill_philos(philo, ctx);
		return (1);
	}
	philo = create_philos(ctx);
	if (!philo)
	{
		kill_philos(philo, ctx);
		return (1);
	}
	start_philos(philo, ctx->philo_count);
	kill_philos(philo, ctx);
	return (0);
}
