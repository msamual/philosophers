#include "header.h"
#include <errno.h>

int	main(int ac, char **av)
{
	t_philosopher	**phil;
	t_rules			rules;
	sem_t			*sem;
	sem_t			*console;

	if (!is_valid(ac, av))
	{
		printf("invalid arguments!\nexit\n");
		return (0);
	}
	sem = NULL;
	console = NULL;
	phil = init_all(av, &rules, sem, console);
	start_simulation(phil);
	sem_close(sem);
	sem_close(console);
	sem_unlink("sem");
	sem_unlink("console");
	return (0);
}
