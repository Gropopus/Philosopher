/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 10:41:09 by thsembel          #+#    #+#             */
/*   Updated: 2021/08/03 14:55:02 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_putstr_fd(int fd, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

void	ft_sleep(t_info *info, long long time)
{
	long long	i;

	i = ft_get_time();
	while (info->dead == 0)
	{
		if (ft_get_time() - i >= time)
			break ;
		usleep(50);
	}
}

void	ft_display_action(t_info *info, int id, char *action)
{
	pthread_mutex_lock(&(info->displayer));
	if (info->dead == 0)
	{
		printf("%s%lli%s ", BLUE, ft_get_time() - info->timestamp, NC);
		printf("%s%i%s ", YELLOW, id, NC);
		printf("%s\n", action);
	}
	else if (info->dead && action[0] == 'd')
	{
		printf("%s%lli%s ", BLUE, ft_get_time() - info->timestamp, NC);
		printf("%s%i%s ", YELLOW, id, NC);
		printf("%s\n", action);
	}
	pthread_mutex_unlock(&(info->displayer));
}

long long int	ft_atoi(const char *str)
{
	long long int		nb;
	int					i;
	int					n;

	i = 0;
	nb = 0;
	n = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - 48;
		i++;
	}
	if ((nb * n) > 2147463647)
		return (-1);
	return (nb * n);
}

long long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
