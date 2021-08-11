#include "header.h"
#include <errno.h>

int	main(int ac, char **av)
{
	t_philosopher	**phil;
	t_rules			rules;
	pthread_mutex_t	mutex[201];

	if (!is_valid(ac, av))
	{
		printf("invalid arguments!\nexit\n");
		return (0);
	}
	phil = init_all(av, &rules, mutex);
	start_simulation(phil);
	return (0);
}
