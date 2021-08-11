#ifndef HEADER_H
# define HEADER_H

# include <stdbool.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>

# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"

bool	g_finish;

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
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	*console;
	int				name;
	unsigned long	time_last_eat;
	bool			finish;
	t_rules			*rules;
}					t_philosopher;

int				ft_atoi(const char *str);
bool			is_valid(int ac, char **av);

t_philosopher	**init_all(char **av, t_rules *rules, pthread_mutex_t *mutex);
void			start_simulation(t_philosopher **phil);
unsigned long	get_time(struct timeval *time);
void			thinking(t_philosopher *p);
void			sleeping(t_philosopher *p);
void			*dead_control(void *phil);
void			print(char *msg, unsigned long time, int name,
					pthread_mutex_t *mutex);
void			ft_usleep(unsigned int n);

#endif