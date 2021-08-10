/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 14:33:03 by thsembel          #+#    #+#             */
/*   Updated: 2021/08/10 14:41:03 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
** each of the mutex for the right and left forks a locked during the time when
** a philosopher is eating, then unlocked. Actions are of course displayed
** during this interval.
*/

void	ft_lunch_time(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	pthread_mutex_lock(&(info->forks[philo->l_fork]));
	ft_display_action(info, philo->id, FORK);
	pthread_mutex_lock(&(info->forks[philo->r_fork]));
	ft_display_action(info, philo->id, FORK);
	pthread_mutex_lock(&(info->is_mealed));
	ft_display_action(info, philo->id, EAT);
	philo->mealed_t = ft_get_time();
	pthread_mutex_unlock(&(info->is_mealed));
	ft_sleep(info, info->eat_t);
	philo->mealed++;
	pthread_mutex_unlock(&(info->forks[philo->l_fork]));
	pthread_mutex_unlock(&(info->forks[philo->r_fork]));
}

/*
** Returns 1 if not dead, -1 if dead. A philosopher is dead if his lifetime 
** minus the time he took to eat his last meal exceed the lifetime given as an
** argument.
*/

int	ft_dead_check(t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (info->dead == 0 && i < info->nb_philo)
	{
		pthread_mutex_lock(&(info->is_mealed));
		if (ft_get_time() - philo[i].mealed_t > info->death_t)
		{
			ft_display_action(info, i, DEAD);
			info->dead = 1;
			return (-1);
		}
		pthread_mutex_unlock(&(info->is_mealed));
		usleep(200);
		i++;
	}
	return (1);
}

/*
** Stop the loop if a philosopher is dead or if the number of meal they had is
** equal to the number of meal asked as the [5]argument.
*/

void	ft_stop_loop(t_info *info, t_philo *philo, int i)
{
	while (info->full_mealed != 1)
	{
		if (ft_dead_check(info, philo) < 0)
			return ;
		i = 0;
		while (info->n_meal != -667 && i < info->nb_philo
			&& ((philo[i].mealed == info->n_meal - 1 && info->n_meal > 1)
				|| (info->n_meal == 1 && philo[i].mealed == 1)))
			i++;
		if (i == info->nb_philo)
			info->full_mealed = 1;
	}
}

/*
** Thread's routine fork->eat->sleep->think
*/
void	*routine(void *philo_v)
{
	t_info	*info;
	t_philo	*philo;

	philo = (t_philo *)philo_v;
	info = philo->info;
	if (philo->id % 2)
		usleep(10000);
	while (info->dead == 0)
	{
		ft_lunch_time(philo);
		if (info->full_mealed != 0)
		{
			ft_display_action(info, philo->id, FULL);
			break ;
		}
		ft_display_action(info, philo->id, SLEEP);
		ft_sleep(info, info->sleep_t);
		ft_display_action(info, philo->id, THINK);
	}
	return (0);
}

/*
**	Creates a thread by philo, starts the routine and the function
** to stop. Then destroy all of the threads and mutexs.
*/
int	ft_start(t_info *info, int i, int j)
{
	t_philo	*philo;

	info->timestamp = ft_get_time();
	philo = info->philo;
	while (i < info->nb_philo)
	{
		if (pthread_create(&(philo[i].id_thread), NULL,
				routine, &(philo[i])) != 0)
			return (-1);
		philo[i].mealed_t = ft_get_time();
		i++;
	}
	ft_stop_loop(info, philo, 0);
	usleep(1000000);
	while (j != 0)
	{
		if (pthread_join(philo[j].id_thread, NULL) != 0)
			break ;
		j--;
	}
	i = -1;
	while (i++ < info->nb_philo)
		pthread_mutex_destroy(&(info->forks[i]));
	pthread_mutex_destroy(&(info->displayer));
	return (0);
}
