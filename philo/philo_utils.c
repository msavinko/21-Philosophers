/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:47:58 by marlean           #+#    #+#             */
/*   Updated: 2022/04/11 16:04:09 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(int num)
{
	if (num == 1)
		write(1, "Wrong input\n", 12);
	else if (num == 2)
		write (1, "Mutex error\n", 12);
	else if (num == 3)
		write (1, "Malloc error\n", 13);
	exit(1);
}

int	ph_atoi(const char *str)
{
	int			i;
	long int	res;

	i = 0;
	res = 0;
	if (str[i] != '\0' && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			ft_error(1);
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i++] - '0');
		if ((res) > 2147483647)
			ft_error(1);
	}
	if (res == 0)
		ft_error(1);
	return (res);
}
