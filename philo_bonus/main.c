/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 11:17:18 by thsembel          #+#    #+#             */
/*   Updated: 2021/07/01 15:47:59 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_init_philos(t_info *info, int i)
{
	while (i >= 0)
	{
		info->philo[i].id = i;
		info->philo[i].mealed_t = 0;
		info->philo[i].mealed = 0;
		info->philo[i].info = info;
		i--;
	}
}

int	ft_init_sem(t_info *info)
{
	sem_unlink("/displayer");
	info->displayer = sem_open("/displayer", O_CREAT, S_IRWXU, 1);
	if (info->displayer <= 0)
		return (-1);
	sem_unlink("/is_mealed");
	info->is_mealed = sem_open("/is_mealed", O_CREAT, S_IRWXU, 1);
	if (info->is_mealed <= 0)
		return (-1);
	sem_unlink("/forks");
	info->forks = sem_open("/forks", O_CREAT, S_IRWXU, info->nb_philo);
	if (info->forks <= 0)
		return (-1);
	return (1);
}

int	ft_check_arg(t_info *info)
{
	if (info->nb_philo < 0 || info->nb_philo > 200)
	{
		ft_putstr_fd(2, "Error: nb_philo  must be a positive number");
		ft_putstr_fd(2, " not greater than 200, and composed of digits only\n");
		return (-1);
	}
	else if (info->sleep_t < 0 || info->eat_t < 0 || info->death_t < 0
		|| (info->n_meal < 0 && info->init != 0))
	{
		ft_putstr_fd(2, "Error: Args  must be apositive number,");
		ft_putstr_fd(2, " composed of digits  and fit in an integer\n");
		return (-1);
	}
	return (1);
}

int	ft_init(t_info *info, char **av)
{
	int	i;

	info->nb_philo = ft_atoi(av[1]);
	info->death_t = ft_atoi(av[2]);
	info->eat_t = ft_atoi(av[3]);
	info->sleep_t = ft_atoi(av[4]);
	info->n_meal = -667;
	info->full_mealed = 0;
	info->dead = 0;
	info->init = 0;
	if (av[5])
	{
		info->n_meal = ft_atoi(av[5]);
		info->init++;
	}
	if ((ft_check_arg(info)) < 0)
		return (-1);
	i = info->nb_philo - 1;
	if ((ft_init_sem(info)) < 0)
	{
		ft_putstr_fd(2, "Error: Unable to create mutexs\n");
		return (-1);
	}
	ft_init_philos(info, i);
	return (1);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (ac != 5 && ac != 6)
	{
		ft_putstr_fd(2, "Error: only 5 or 6 arguments accepted\n");
		return (0);
	}
	if ((ft_init(&info, av)) < 0)
		return (0);
	if ((ft_start(&info, 0)) < 0)
	{
		ft_putstr_fd(2, "Error: Unable to create the threads\n");
		return (0);
	}
	return (0);
}
