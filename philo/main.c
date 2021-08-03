/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 11:17:18 by thsembel          #+#    #+#             */
/*   Updated: 2021/08/03 15:46:02 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_init_mutex_and_philo(t_info *info, int i)
{
	while (i >= 0)
	{
		if ((pthread_mutex_init(&(info->forks[i]), NULL)) != 0)
			return (-1);
		i--;
	}
	if ((pthread_mutex_init(&(info->displayer), NULL)) != 0)
		return (-1);
	else if ((pthread_mutex_init(&(info->is_mealed), NULL)) != 0)
		return (-1);
	i = info->nb_philo - 1;
	while (i >= 0)
	{
		info->philo[i].id = i;
		info->philo[i].mealed_t = 0;
		info->philo[i].mealed = 0;
		info->philo[i].l_fork = i;
		info->philo[i].r_fork = i + 1 % info->nb_philo;
		info->philo[i].info = info;
		i--;
	}
	return (1);
}

int	ft_init_info(t_info *info, char **av)
{
	info->nb_philo = ft_atoi(av[1]);
	info->death_t = ft_atoi(av[2]);
	info->eat_t = ft_atoi(av[3]);
	info->sleep_t = ft_atoi(av[4]);
	info->n_meal = -667;
	info->full_mealed = 0;
	info->init = 0;
	if (av[5])
	{
		info->n_meal = ft_atoi(av[5]);
		info->init++;
	}
	if (info->nb_philo < 0 || info->nb_philo > 200)
	{
		ft_putstr_fd(2, "Error: nb_philo  must be a positive number");
		ft_putstr_fd(2, " not greater than 200, and composed of digits only\n");
		return (-1);
	}
	else if (info->sleep_t < 0 || info->eat_t < 0 || info->death_t < 0
		|| (info->n_meal < 0 && info->init != 0))
	{
		ft_putstr_fd(2, "Error: Invalid argument\n");
		return (-1);
	}
	return (1);
}

int	ft_init(t_info *info, char **av)
{
	int	i;

	if (ft_init_info(info, av) < 0)
		return (-1);
	i = info->nb_philo - 1;
	if ((ft_init_mutex_and_philo(info, i)) < 0)
	{
		ft_putstr_fd(2, "Error: Unable to create mutexs\n");
		return (-1);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_info	info;
	int		j;

	info.dead = 0;
	j = 0;
	if (ac != 5 && ac != 6)
	{
		ft_putstr_fd(2, "Error: only 5 or 6 arguments accepted\n");
		return (0);
	}
	if ((ft_init(&info, av)) < 0)
		return (0);
	j = info.nb_philo;
	if ((ft_start(&info, 0, j)) < 0)
	{
		ft_putstr_fd(2, "Error: Unable to create the threads\n");
		return (0);
	}
	return (0);
}
