#include "header.h"

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

t_philosopher	**init_all(char **av, t_rules *rules, sem_t *sem,
					sem_t *console)
{
	int					i;
	int					number_of_philosophers;
	t_philosopher		**phil;

	i = -1;
	number_of_philosophers = ft_atoi(av[1]);
	sem_unlink("sem");
	sem_unlink("console");
	sem = sem_open("sem", O_CREAT, 0666, number_of_philosophers);
	console = sem_open("console", O_CREAT, 0666, 1);
	parse(av, rules, number_of_philosophers);
	phil = malloc(number_of_philosophers * sizeof(t_philosopher *));
	i = -1;
	while (++i < number_of_philosophers)
	{
		phil[i] = malloc(sizeof(t_philosopher));
		phil[i]->name = i + 1;
		phil[i]->rules = rules;
		phil[i]->finish = false;
		phil[i]->time_last_eat = 0;
		phil[i]->sem = sem;
		phil[i]->console = console;
	}
	return (phil);
}
