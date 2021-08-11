#include "header.h"

void	take_forks(t_philosopher *p)
{
	sem_wait(p->sem);
	print("has taken a fork", get_time(p->time), p->name, p->console);
	sem_wait(p->sem);
	print("has taken a fork", get_time(p->time), p->name, p->console);
}

void	eating(t_philosopher *p)
{
	print("is thinking", get_time(p->time), p->name, p->console);
	take_forks(p);
	p->time_last_eat = get_time(p->time);
	printf(ANSI_COLOR_GREEN "%lu %d is eating"
		ANSI_COLOR_RESET "\n", get_time(p->time), p->name);
	ft_usleep(p->rules->time_to_eat * 1000);
	sem_post(p->sem);
	sem_post(p->sem);
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
	exit(0);
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
	pid_t				pid;
	sem_t				*dead;

	gettimeofday(&time, NULL);
	sem_unlink("dead");
	dead = sem_open("dead", O_CREAT, 0666, 0);
	i = -1;
	while (++i < phil[0]->rules->number_of_philosophers)
	{
		phil[i]->time = &time;
		pid = fork();
		if (pid == 0)
		{
			pthread_create(&phil[i]->id, NULL, philosopher, phil[i]);
			pthread_detach(phil[i]->id);
			pthread_create(&phil[i]->id, NULL, dead_check, (void *)dead);
			pthread_detach(phil[i]->id);
			dead_control(phil[i], dead);
			break ;
		}
	}
	while (wait(NULL) > 0)
		;
}
