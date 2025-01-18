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

int	ft_exit(t_data *data)
{
	int (i) = 0;
	while (++i < data->n_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].lock);
		i++;
	}
	pthread_mutex_destroy(&data->end);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
	if (data->thread)
		free(data->thread);
	if (data->forks)
		free(data->forks);
	if (data->philo)
		free(data->philo);
	return (0);
}

int	ft_error(char *str, t_data *data)
{
	printf("%s\n", str);
	if (data)
		ft_exit(data);
	return (1);
}

int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == ' ')
			{
				j++;
				continue ;
			}
			if ((argv[i][j] < '0' || argv[i][j] > '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	philosophers(t_data *data)
{
	int (i) = 0;
	while (i < data->n_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			ft_error("Failed to join thread", data);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
		return (ft_error("Wrong argument count\n", NULL));
	if (check_args(argv))
		return (ft_error("Invalid argument(s)\n", NULL));
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_error("Failed to allocate memory\n", NULL);
	init_data(argc, argv, data);
	return (philosophers(data));
}
