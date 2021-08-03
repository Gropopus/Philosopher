/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 10:38:41 by thsembel          #+#    #+#             */
/*   Updated: 2021/07/01 15:32:52 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# define SLEEP	"is sleeping"
# define FORK	"has taken a fork"
# define EAT	"is eating"
# define THINK	"is thinking"
# define DEAD	"\033[0;31mdied\033[0m"
# define FULL	"\033[0;32mhas taken all of his meal\033[0m"
# define RED    "\033[0;31m"
# define GREEN  "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE   "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN   "\033[0;36m"
# define NC     "\033[0m"

struct	s_info;

typedef struct s_philo
{
	int					id;
	int					l_fork;
	int					r_fork;
	int					mealed;
	long long			mealed_t;
	struct s_info		*info;
	pthread_t			id_thread;
}				t_philo;

typedef struct s_info
{
	int					death_t;
	int					eat_t;
	int					sleep_t;
	int					dead;
	int					full_mealed;
	int					nb_philo;
	int					n_meal;
	int					init;
	long long			timestamp;
	pthread_mutex_t		displayer;
	pthread_mutex_t		is_mealed;
	pthread_mutex_t		forks[200];
	t_philo				philo[200];
}				t_info;
/*
**			utils.c
*/
void			ft_putstr_fd(int fd, char *str);
void			ft_display_action(t_info *info, int id, char *action);
long long		ft_get_time(void);
long long int	ft_atoi(const char *str);
void			ft_sleep(t_info *info, long long time);
/*
**			start.c
*/
int				ft_start(t_info *info, int i, int j);
#endif
