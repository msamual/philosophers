#ifndef HEADER_H
# define HEADER_H

# include <stdbool.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <semaphore.h>
# include <fcntl.h>

# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct s_rules
{
	int				number_of_philosophers;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
}					t_rules;

typedef struct s_philosopher
{
	pthread_t		id;
	struct timeval	*time;
	sem_t			*sem;
	sem_t			*console;
	sem_t			*die;
	int				name;
	unsigned long	time_last_eat;
	bool			finish;
	t_rules			*rules;
}					t_philosopher;

int				ft_atoi(const char *str);
bool			is_valid(int ac, char **av);

t_philosopher	**init_all(char **av, t_rules *rules, sem_t **sem);
void			start_simulation(t_philosopher **phil);
unsigned long	get_time(struct timeval *time);
void			thinking(t_philosopher *p);
void			sleeping(t_philosopher *p);
void			*dead_control(void *phil, sem_t *dead);
void			print(char *msg, unsigned long time, int name, sem_t *console);
void			ft_usleep(unsigned int n);
void			*dead_check(void *dead);

#endif