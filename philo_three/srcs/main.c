#include "header.h"
#include <errno.h>

void	close_sems(sem_t *sem, sem_t *console, sem_t *die)
{
	sem_close(sem);
	sem_close(console);
	sem_close(die);
	sem_unlink("sem");
	sem_unlink("console");
	sem_unlink("die");
}

int	main(int ac, char **av)
{
	t_philosopher	**phil;
	t_rules			rules;
	sem_t			**sem;

	sem = (sem_t **)malloc(3 * sizeof(sem_t *));
	if (!is_valid(ac, av))
	{
		printf("invalid arguments!\nexit\n");
		return (0);
	}
	phil = init_all(av, &rules, sem);
	start_simulation(phil);
	close_sems(sem[0], sem[1], sem[2]);
	return (0);
}
