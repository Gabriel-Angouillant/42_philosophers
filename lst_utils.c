/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangouil <gangouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 20:17:32 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/10 20:17:38 by gangouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_lstnew(int num, t_state state, t_philo *next)
{
	t_philo	*lst;

	lst = malloc(sizeof(t_philo));
	if (!lst)
		return (NULL);
	pthread_mutex_init(&lst->fork, NULL);
	lst->num = num;
	lst->available = true;
	lst->last_eat = 0;
	lst->eat_count = 0;
	lst->state = state;
	lst->next = next;
	return (lst);
}

t_philo	*ft_lstlast(t_philo *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*last;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

void	ft_lstadd_front(t_philo **lst, t_philo *new)
{
	t_philo	*new_last;

	if (!new)
		return ;
	new_last = ft_lstlast(new);
	new_last->next = *lst;
	*lst = new;
}

void	ft_lstclear(t_philo *lst, int philo_count)
{
	t_philo	*tmp;
	int		i;

	i = 0;
	while (lst && i < philo_count)
	{
		tmp = lst->next;
		pthread_mutex_destroy(&lst->fork);
		free(lst);
		lst = tmp;
		i++;
	}
}
