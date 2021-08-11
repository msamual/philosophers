#include "header.h"

bool	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (true);
	}
	return (false);
}

bool	is_number(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

bool	is_valid(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (false);
	i = 0;
	while (++i < ac)
		if (!is_number(av[i]))
			return (false);
	return (true);
}
