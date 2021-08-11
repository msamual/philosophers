#include "header.h"

unsigned long	get_time(struct timeval *start)
{
	struct timeval	current;
	unsigned long	cur;
	unsigned long	srt;

	gettimeofday(&current, NULL);
	cur = current.tv_sec * 1000 + current.tv_usec / 1000;
	srt = start->tv_sec * 1000 + start->tv_usec / 1000;
	return (cur - srt);
}

void	*dead_check(void *dead)
{
	sem_t	*d;

	d = (sem_t *)dead;
	sem_wait(d);
	sem_post(d);
	exit(0);
	return (NULL);
}
