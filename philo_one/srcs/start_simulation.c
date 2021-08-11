#include "header.h"

void	take_forks(t_philosopher *p)
{
	if (g_finish)
		return ;
	if (p->rules->number_of_philosophers % 2 == 0 && p->name == 1)
	{
		pthread_mutex_lock(p->left);
		print("has taken a fork", get_time(p->time), p->name, p->console);
		pthread_mutex_lock(p->right);
		print("has taken a fork", get_time(p->time), p->name, p->console);
	}
	else
	{
		pthread_mutex_lock(p->right);
		print("has taken a fork", get_time(p->time), p->name, p->console);
		pthread_mutex_lock(p->left);
		print("has taken a fork", get_time(p->time), p->name, p->console);
	}
}

void	eating(t_philosopher *p)
{
	if (g_finish)
		return ;
	print("is thinking", get_time(p->time), p->name, p->console);
	take_forks(p);
	p->time_last_eat = get_time(p->time);
	pthread_mutex_lock(p->console);
	if (g_finish)
		return ;
	printf(ANSI_COLOR_GREEN "%lu %d is eating"
		ANSI_COLOR_RESET "\n", get_time(p->time), p->name);
	pthread_mutex_unlock(p->console);
	if (g_finish)
		return ;
	ft_usleep(p->rules->time_to_eat * 1000);
	if (g_finish)
		return ;
	pthread_mutex_unlock(p->right);
	pthread_mutex_unlock(p->left);
}

void	*philosopher(void *phil)
{
	int				i;
	t_philosopher	*phi;

	i = 0;
	phi = (t_philosopher *)phil;
	while (i < phi->rules->number_of_times_each_philosopher_must_eat)
	{
		eating(phi);
		if (i == phi->rules->number_of_times_each_philosopher_must_eat - 1)
			break ;
		sleeping(phi);
		i++;
	}
	phi->finish = true;
	return (phil);
}

void	ft_usleep(unsigned int n)
{
	struct timeval	start;
	struct timeval	step;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(50);
		gettimeofday(&step, NULL);
		if ((size_t)(((size_t)(step.tv_sec - start.tv_sec)) * 1000000 +
			((size_t)(step.tv_usec - start.tv_usec))) > n)
			break ;
	}
}

void	start_simulation(t_philosopher **phil)
{
	int					i;
	struct timeval		time;

	gettimeofday(&time, NULL);
	i = -1;
	g_finish = false;
	while (++i < phil[0]->rules->number_of_philosophers)
	{
		phil[i]->time = &time;
		pthread_create(&phil[i]->id, NULL, philosopher, phil[i]);
		pthread_detach(phil[i]->id);
	}
	dead_control(phil);
}
