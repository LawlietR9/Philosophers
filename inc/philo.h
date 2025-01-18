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

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		thread;
	int				n_philo;
	int				n_meals;
	u_int64_t		time_death;
	u_int64_t		time_eat;
	u_int64_t		time_sleep;
	int				id;
	int				eat_count;
	int				status;
	int				eating;
	uint64_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_data
{
	pthread_t		*thread;
	int				dead;
	int				finished;
	int				is_over;
	int				n_philo;
	int				n_meals;
	t_philo			*philo;
	u_int64_t		time_death;
	u_int64_t		time_eat;
	u_int64_t		time_sleep;
	u_int64_t		time_start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	end;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}	t_data;

int		ft_exit(t_data *data);
int		ft_error(char *str, t_data *data);
int		check_args(char **argv);
int		philosophers(t_data *data);

int		init_forks(t_data *data);
int		init_philo(t_data *data);
int		init_data(int argc, char **argv, t_data *data);

int		ft_strcmp(char *s1, char *s2);
int		ft_atoi(char *str);
int		print_message(t_philo *philo, char *message);
size_t	get_time(void);
void	ft_usleep(size_t ms);

void	*routine(void *philo_pointer);
void	*check_death(void *pointer);
int		is_dead(t_philo *philo);
int		eat(t_philo *philo);

#endif
