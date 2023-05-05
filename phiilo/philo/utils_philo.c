/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majmani <majmani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:03:06 by majmani           #+#    #+#             */
/*   Updated: 2023/04/05 15:46:56 by majmani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (0);
			j++;
		}
		if (ft_atoi(argv[i]) < 0 || ft_atoi(argv[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_initialisation(t_philo *b, char **argv, int argc, pthread_mutex_t *p)
{
	int	i;

	i = -1;
	while (++i < ft_atoi(argv[1]))
	{
		pthread_mutex_init(&b[i].l_fork, NULL);
		b[i].begin = get_time();
		b[i].eat = get_time();
		b[i].check_eat = 0;
		b[i].w = p;
		b[i].id = i + 1;
		b[i].ar.number_philo = ft_atoi(argv[1]);
		b[i].ar.t_die = ft_atoi(argv[2]);
		b[i].ar.t_eat = ft_atoi(argv[3]);
		b[i].ar.t_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			b[i].ar.tour = ft_atoi(argv[5]);
	}
	i = 0;
	while (i < b[i].ar.number_philo - 1)
	{
		b[i].r_fork = &b[i + 1].l_fork;
		i++;
	}
	b[i].r_fork = &b[0].l_fork;
}

int	is_dead(t_philo *p)
{
	int		i;
	long	t;

	i = 0;
	while (i < p->ar.number_philo)
	{
		pthread_mutex_lock(p[i].w);
		t = get_time();
		if ((t - p[i].eat) > p[i].ar.t_die && p[i].check_eat == 0)
		{
			printf("%ld ms %d has died\n", t - p[i].begin, p[i].id);
			return (0);
		}
		pthread_mutex_unlock(p[i].w);
		i++;
	}
	return (1);
}

int	check_tour(t_philo *p)
{
	int	i;
	int	j;

	i = 0;
	while (i < p->ar.number_philo)
	{
		pthread_mutex_lock(p[i].w);
		j = p[i].ar.tour;
		pthread_mutex_unlock(p[i].w);
		if (j != 0)
			return (1);
		i++;
	}
	return (0);
}
