#include "header.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	negative;

	negative = 1;
	res = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t'
			|| *str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	if (*str == '-')
		negative = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
	return (res * negative);
}

void	sleeping(t_philosopher *p)
{
	print("is sleeping", get_time(p->time), p->name, p->console);
	ft_usleep(p->rules->time_to_sleep * 1000);
}

void	*kill_all_processes(t_philosopher *p, sem_t *dead)
{
	sem_wait(p->console);
	printf(ANSI_COLOR_RED "%lu %d died" ANSI_COLOR_RESET "\n",
		get_time(p->time), p->name);
	sem_post(dead);
	return (NULL);
}

void	print(char *msg, unsigned long time, int name, sem_t *console)
{
	sem_wait(console);
	printf("%lu %d %s\n", time, name, msg);
	sem_post(console);
}

void	*dead_control(void *phil, sem_t *dead)
{
	t_philosopher	*p;
	int				n;

	p = (t_philosopher *)phil;
	n = p->rules->number_of_philosophers;
	while (true)
	{
		sem_wait(p->die);
		if (p->rules->time_to_die < (get_time(p->time)
				- p->time_last_eat) && p->finish == false)
			return (kill_all_processes(p, dead));
		sem_post(p->die);
	}
	return (NULL);
}
