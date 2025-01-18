#include "../inc/philosophers.h"

int init_forks(t_data *data)
{
    int (i) = 0;
    while (i < data->n_philo)
        pthread_mutex_init(&data->forks[i++], NULL);
    i = 0;
    while (i < data->n_philo)
    {
        if (i == 0)
        {
            data->philo[i].l_fork = &data->forks[0];
            data->philo[i].r_fork = &data->forks[data->n_philo - 1];
        }
        else
        {
            data->philo[i].l_fork = &data->forks[i];
            data->philo[i].r_fork = &data->forks[i - 1];
        }
        i++;
    }
    return (0);
}

int init_philo(t_data *data)
{
    int (i) = 0;
    while (i < data->n_philo)
    {
        data->philo[i].data = data;
        data->philo[i].n_philo = data->n_philo;
        data->philo[i].n_meals = data->n_meals;
        data->philo[i].time_death = data->time_death;
        data->philo[i].time_eat = data->time_eat;
        data->philo[i].time_sleep = data->time_sleep;
        data->philo[i].id = i + 1;
        data->philo[i].eat_count = 0;
        data->philo[i].eating = 0;
        data->philo[i].status = 0;
        data->is_over = 0;
        
        pthread_mutex_init(&data->philo[i].lock, NULL);
        if (pthread_create(&data->philo[i].thread, NULL, routine, &data->philo[i]))
            ft_error("Failed to create thread", data);
        ft_usleep(1);
        i++;
    }
    i = 0;
    while (i < data->n_philo)
    {
        if (pthread_join(data->philo[i].thread, NULL))
            ft_error("Failed to join thread", data);
        i++;
    }
    return (0);
}

int init_data(int argc, char **argv, t_data *data)
{
    data->n_philo = ft_atoi(argv[1]);
    data->time_death = ft_atoi(argv[2]);
    data->time_eat = ft_atoi(argv[3]);
    data->time_sleep = ft_atoi(argv[4]);
    data->n_meals = -1;
    if (argc == 6)
        data->n_meals = ft_atoi(argv[5]);
    data->time_start = get_time();
    data->dead = 0;
    data->finished = 0;
    pthread_mutex_init(&data->end, NULL);
    pthread_mutex_init(&data->write, NULL);
    pthread_mutex_init(&data->lock, NULL);
	data->thread = malloc(sizeof(pthread_t) * data->n_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->thread || !data->forks || !data->philo)
        ft_error("Failed to allocate memory", data);
    init_forks(data);
    init_philo(data);
    return (0);
}