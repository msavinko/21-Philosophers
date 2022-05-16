/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlean <marlean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:37:24 by marlean           #+#    #+#             */
/*   Updated: 2022/05/16 19:29:28 by marlean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_error(int num)
{
	if (num == 1)
		write(1, "Wrong arguments\n", 16);
	else if (num == 2)
		write(1, "Malloc error\n", 13);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data *data;

	if (argc != 5 && argc != 6)
		return (ft_error(1));
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_error(2));
	init_data(data, &argv);


	return (0);
}