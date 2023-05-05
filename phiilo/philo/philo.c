/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majmani <majmani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:00:09 by majmani           #+#    #+#             */
/*   Updated: 2023/04/06 15:27:00 by majmani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->l_fork);
	pthread_mutex_lock(ph->w);
	printf("%ld ms %d has taken a fork\n", (get_time() - ph->begin), ph->id);
	pthread_mutex_unlock(ph->w);
	pthread_mutex_lock(ph->r_fork);
	pthread_mutex_lock(ph->w);
	printf("%ld ms %d has taken a fork\n", (get_time() - ph->begin), ph->id);
	pthread_mutex_unlock(ph->w);
	pthread_mutex_lock(ph->w);
	ph->ar.tour--;
	ph->eat = get_time();
	ph->check_eat = 1;
	printf("%ld ms %d is eating\n", get_time() - ph->begin, ph->id);
	pthread_mutex_unlock(ph->w);
	my_usleep(ph->ar.t_eat);
	pthread_mutex_unlock(&ph->l_fork);
	pthread_mutex_unlock(ph->r_fork);
}

void	ft_sleep(t_philo *ph)
{
	pthread_mutex_lock(ph->w);
	ph->check_eat = 0;
	printf("%ld ms %d is sleeping\n", get_time() - ph->begin, ph->id);
	pthread_mutex_unlock(ph->w);
	my_usleep(ph->ar.t_sleep);
}

void	ft_thinking(t_philo *ph)
{
	pthread_mutex_lock(ph->w);
	printf("%ld ms %d is thinking\n", get_time() - ph->begin, ph[0].id);
	pthread_mutex_unlock(ph->w);
}

void	*global(void *hp)
{
	t_philo	*ph;
	int		i;
	int		y;

	i = 0;
	y = 0;
	ph = (t_philo *)hp;
	if (ph->id % 2 == 0)
		my_usleep(100);
	while (1)
	{
		eat(ph);
		ft_sleep(ph);
		ft_thinking(ph);
		if (0 == ph->ar.tour)
			break ;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo			*ph;
	int				i;
	pthread_mutex_t	*p;

	p = malloc(sizeof(pthread_mutex_t));
	i = -1;
	if ((argc != 5 && argc != 6) || check_arg(argv) == 0)
		return (norm());
	ph = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	(pthread_mutex_init(p, NULL), ft_initialisation(ph, argv, argc, p));
	while (++i < ph->ar.number_philo)
		pthread_create(&ph[i].p, NULL, global, ph + i);
	i = -1;
	while (++i < ph->ar.number_philo)
		pthread_detach(ph[i].p);
	while (1)
	{
		if (is_dead(ph) == 0)
			return (0);
		if (check_tour(ph) == 0 && argc == 6)
			break ;
	}
	return (0);
}
