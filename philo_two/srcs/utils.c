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
	if (g_finish)
		return ;
	print("is sleeping", get_time(p->time), p->name, p->console);
	if (g_finish)
		return ;
	ft_usleep(p->rules->time_to_sleep * 1000);
	if (g_finish)
		return ;
}

void	*kill_thread(t_philosopher *p)
{
	sem_wait(p->console);
	printf(ANSI_COLOR_RED "%lu %d died" ANSI_COLOR_RESET "\n",
		get_time(p->time), p->name);
	g_finish = true;
	return (NULL);
}

void	print(char *msg, unsigned long time, int name, sem_t *console)
{
	sem_wait(console);
	printf("%lu %d %s\n", time, name, msg);
	sem_post(console);
}

void	*dead_control(void *phil)
{
	t_philosopher	**p;
	int				i;
	int				n;
	bool			continue_simulation;

	p = (t_philosopher **)phil;
	n = p[0]->rules->number_of_philosophers;
	continue_simulation = true;
	while (continue_simulation)
	{
		continue_simulation = false;
		i = 0;
		while (i < n)
		{
			if (p[i]->rules->time_to_die < (get_time(p[i]->time)
					- p[i]->time_last_eat) && p[i]->finish == false)
				return (kill_thread(p[i]));
			if (p[i]->finish == false)
				continue_simulation = true;
			i++;
		}
	}
	return (NULL);
}
