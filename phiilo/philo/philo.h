/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majmani <majmani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 13:25:23 by majmani           #+#    #+#             */
/*   Updated: 2023/04/04 15:45:29 by majmani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_arg
{
	int	number_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	tour;
}	t_arg;
typedef struct s_philo
{
	int				id;
	int				check_eat;
	long			begin;
	long			eat;
	pthread_mutex_t	*w;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	l_fork;
	pthread_t		p;
	t_arg			ar;
}	t_philo;

int		ft_atoi(const char *str);
void	ft_initialisation(t_philo *a, char **argv,
			int argc, pthread_mutex_t *p);
void	*global(void *hp);
int		check_arg(char **argv);
int		check_tour(t_philo *p);
long	get_time(void);
int		is_dead(t_philo *p);
void	my_usleep(long t);
int		ft_isdigit(int c);
long	get_time(void);
int		norm(void);
#endif
