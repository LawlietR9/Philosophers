/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenito <kenito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 22:33:28 by kenito            #+#    #+#             */
/*   Updated: 2023/12/19 22:33:28 by kenito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/philo.h"

void	*routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (pthread_create(&philo->thread, NULL, &check_death, philo))
		return ((void *)1);
	while (!is_dead(philo))
	{
		if (eat(philo))
			return ((void *)1);
		print_message(philo, "is sleeping");
		ft_usleep(philo->time_sleep);
		print_message(philo, "is thinking");
		if (philo->eat_count == philo->n_meals)
		{
			pthread_mutex_lock(&philo->data->lock);
			if (++philo->data->finished == philo->n_philo)
			{
				pthread_mutex_lock(&philo->data->end);
				philo->data->dead = 2;
				pthread_mutex_unlock(&philo->data->end);
			}
			pthread_mutex_unlock(&philo->data->lock);
		}
	}
	return ((void *)0);
}

void	*check_death(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	ft_usleep(philo->time_death + 1);
	while (!is_dead(philo))
	{
		if (get_time() >= philo->time_to_die && philo->eating == 0)
		{
			pthread_mutex_lock(&philo->data->end);
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->data->end);
			print_message(philo, "died");
		}
	}
	return ((void *)0);
}

int	is_dead(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->data->end);
	dead = philo->data->dead;
	pthread_mutex_unlock(&philo->data->end);
	return (dead);
}

int	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
	}
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_to_die = get_time() + philo->time_death;
	philo->eat_count++;
	pthread_mutex_unlock(&philo->lock);
	ft_usleep(philo->time_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	philo->eating = 0;
	return (0);
}
