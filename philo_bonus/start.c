/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 12:20:12 by thsembel          #+#    #+#             */
/*   Updated: 2021/07/01 17:00:37 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	philo_eats(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	sem_wait(info->forks);
	ft_display_action(info, philo->id, FORK);
	sem_wait(info->forks);
	ft_display_action(info, philo->id, FORK);
	sem_wait(info->is_mealed);
	ft_display_action(info, philo->id, EAT);
	philo->mealed_t = ft_get_time();
	sem_post(info->is_mealed);
	ft_sleep(info, info->eat_t);
	philo->mealed++;
	sem_post(info->forks);
	sem_post(info->forks);
}

/*
** This function is killing a philo and setting the death variable to 1
** if the time minus the time the philo took to eat his last meal i greater than
** his lifetime.
** the meal semaphore is locked during the death checking to avoid the philo
** to start eating and dying at the same time.
*/

int	ft_dead_check(t_info *info, t_philo *philo)
{
	sem_wait(info->is_mealed);
	if (ft_get_time() - philo->mealed_t > info->death_t)
	{
		ft_display_action(info, philo->id, DEAD);
		info->dead = 1;
		sem_wait(info->displayer);
		return (-1);
	}
	sem_post(info->is_mealed);
	return (1);
}

/*
** This function checks if the philosopher took all of his meal and set the
** full_mealed variable if so.
*/

void	*ft_stop(void *v_philo)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)v_philo;
	info = philo->info;
	while (info->full_mealed == 0)
	{
		if (ft_dead_check(info, philo) < 0)
			exit (1);
		usleep(800);
		if (philo->mealed >= info->n_meal && info->n_meal != -667)
			info->full_mealed = 1;
	}
	return (0);
}

/*
** a thread is created for each philosopher, and the stop loop is given as
**	routine function. Then the philosopher begin his daily activity while
** he is alive and stops if he is dead or if he took all of his meal.
*/

void	ft_exec_process(void *v_philo)
{
	t_info	*info;
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	info = philo->info;
	philo->mealed_t = ft_get_time();
	pthread_create(&(philo->is_dead), NULL, ft_stop, v_philo);
	if (philo->id % 2)
		usleep(10000);
	while (info->dead == 0)
	{
		philo_eats(philo);
		if (philo->mealed >= info->n_meal && info->n_meal != -667)
		{
			ft_display_action(info, philo->id, FULL);
			break ;
		}
		ft_display_action(info, philo->id, SLEEP);
		ft_sleep(info, info->sleep_t);
		ft_display_action(info, philo->id, THINK);
	}
	pthread_join(philo->is_dead, NULL);
	if (info->dead)
		exit(1);
	exit(0);
}

/*
** each pid (philo) is fork, if any fork failed, then the program stops.
** else the exec_process function will be called for each philo
*/

int	ft_start(t_info *info, int i)
{
	t_philo	*philo;

	philo = info->philo;
	info->timestamp = ft_get_time();
	while (i < info->nb_philo)
	{
		philo[i].id_pid = fork();
		if (philo[i].id_pid < 0)
			return (-1);
		else if (philo[i].id_pid == 0)
			ft_exec_process(&(philo[i]));
		usleep(100);
		i++;
	}
	ft_exit(info, 0, 0);
	return (1);
}
