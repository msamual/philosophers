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
