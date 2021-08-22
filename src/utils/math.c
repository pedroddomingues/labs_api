/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenriq <pehenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 02:08:58 by pehenriq          #+#    #+#             */
/*   Updated: 2021/08/22 15:46:57 by pehenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/labs.h"

int	get_average_grade_all(t_user *user, int n_projects)
{
	int	sum;
	int	i;

	i = 0;
	sum = 0;
	while (i < n_projects)
	{
		sum += user->projects[i].final_mark;
		i++;
	}
	return (sum/n_projects);
}

int	get_average_grade_finished(t_user *user, int n_projects)
{
	int	sum;
	int	i;
	int	j;

	i = 0;
	j = 0;
	sum = 0;
	while (i < n_projects)
	{
		if (strcmp(user->projects[i].status, "finished"))
			j++;
		else
			sum += user->projects[i].final_mark;
		i++;
	}
	return (sum/(n_projects - j));
}
