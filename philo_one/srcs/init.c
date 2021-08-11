#include "header.h"

void	init_forks(t_philosopher *phil, int i, int n, pthread_mutex_t *mutex)
{
	if (i == 0)
	{
		phil->right = &mutex[n - 1];
		phil->left = &mutex[i];
	}
	else
	{
		phil->right = &mutex[i - 1];
		phil->left = &mutex[i];
	}
}

void	parse(char **av, t_rules *rules, int number_of_philosophers)
{
	rules->number_of_philosophers = number_of_philosophers;
	rules->time_to_die = ft_atoi(av[2]);
	rules->time_to_eat = ft_atoi(av[3]);
	rules->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		rules->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		rules->number_of_times_each_philosopher_must_eat = 99999999;
}

t_philosopher	**init_all(char **av, t_rules *rules, pthread_mutex_t *mutex)
{
	int					i;
	int					number_of_philosophers;
	t_philosopher		**phil;

	i = -1;
	number_of_philosophers = ft_atoi(av[1]);
	parse(av, rules, number_of_philosophers);
	while (++i < number_of_philosophers)
		pthread_mutex_init(&mutex[i], NULL);
	pthread_mutex_init(&mutex[i], NULL);
	phil = malloc(number_of_philosophers * sizeof(t_philosopher *));
	i = -1;
	while (++i < number_of_philosophers)
	{
		phil[i] = malloc(sizeof(t_philosopher));
		phil[i]->name = i + 1;
		phil[i]->rules = rules;
		phil[i]->finish = false;
		phil[i]->time_last_eat = 0;
		phil[i]->console = &mutex[number_of_philosophers];
		init_forks(phil[i], i, number_of_philosophers, mutex);
	}
	return (phil);
}
