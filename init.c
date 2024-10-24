/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangouil <gangouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:47:40 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/11 16:47:57 by gangouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static void	ft_atoi(const char *str, long *number)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
		{
			*number = -2;
			return ;
		}
	}
	while (str[i])
	{
		if (((unsigned int)((*number * 10 + (str[i] - '0'))) > INT_MAX)
			|| !ft_isdigit(str[i]))
		{
			*number = -2;
			return ;
		}
		*number = *number * 10 + (str[i] - '0');
		i++;
	}
}

t_ctx	*init_ctx(int argc, char **argv)
{
	t_ctx	*ctx;

	ctx = malloc(sizeof(t_ctx));
	if (!ctx)
		return (NULL);
	*ctx = (t_ctx){0};
	if (pthread_mutex_init(&ctx->print_m, NULL))
		return (NULL);
	if (pthread_mutex_init(&ctx->dead_m, NULL))
	{
		free(ctx);
		pthread_mutex_destroy(&ctx->print_m);
		return (NULL);
	}
	ft_atoi(argv[1], &ctx->philo_count);
	ft_atoi(argv[2], &ctx->time_to_die);
	ft_atoi(argv[3], &ctx->time_to_eat);
	ft_atoi(argv[4], &ctx->time_to_sleep);
	if (argc == 6)
		ft_atoi(argv[5], &ctx->max_eat);
	else
		ctx->max_eat = -1;
	return (ctx);
}

t_philo	*create_philos(t_ctx *ctx)
{
	t_philo	*new_philo;
	t_philo	*philo;
	int		i;

	i = 1;
	philo = NULL;
	while (i <= ctx->philo_count)
	{
		new_philo = ft_lstnew(i, S_THINK, NULL);
		if (!new_philo)
		{
			ft_lstclear(philo, ctx->philo_count);
			return (NULL);
		}
		new_philo->ctx = ctx;
		ft_lstadd_back(&philo, new_philo);
		i++;
	}
	new_philo->next = philo;
	return (philo);
}
