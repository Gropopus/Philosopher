/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:27:11 by thsembel          #+#    #+#             */
/*   Updated: 2021/07/01 15:46:52 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_exit(t_info *info, int i, int ret)
{
	while (i < info->nb_philo)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = 0;
			while (i < info->nb_philo)
			{
				kill(info->philo[i].id_pid, 15);
				i++;
			}
			break ;
		}
		i++;
	}
	sem_close(info->displayer);
	sem_unlink("/displayer");
	sem_close(info->is_mealed);
	sem_unlink("/is_mealed");
	sem_close(info->forks);
	sem_unlink("/forks");
}
