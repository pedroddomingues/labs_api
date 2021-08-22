/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   report.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenriq <pehenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 04:39:38 by pehenriq          #+#    #+#             */
/*   Updated: 2021/08/22 15:46:57 by pehenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/labs.h"

void	print_user(t_user *user)
{
	printf("\n============================================================================================================================\n");
	printf("     ID     |    login    |                Display Name               |               email               | correction_point\n");
	printf("============================================================================================================================\n");
	printf("%8d %14s %40s %38s %12d\n", user->id, user->login, user->displayname, user->email, user->correction_point);
	printf("----------------------------------------------------------------------------------------------------------------------------\n\n");
}

void	print_projects(t_user *user, int n_projects)
{
	int	i;

	i = 0;
	printf("\n============================================================================================================================\n");
	printf("                                                       Projects Stats                                                       \n");
	printf("----------------------------------------------------------------------------------------------------------------------------\n");
	printf("                                Status           |             Name            |          Grade                              \n");
	printf("============================================================================================================================\n");
	while (i < n_projects)
	{
		printf("           %27s %30s %20d                   \n", user->projects[i].status, user->projects[i].name, user->projects[i].final_mark);
		i++;
	}
	printf("============================================================================================================================\n\n");
}

void	print_analysis(t_user *user, int n_projects)
{
	printf("%s has %d projects with an average of %d points.\n", user->login, n_projects, get_average_grade_all(user, n_projects));
	printf("Counting only the finished ones, the average goes to %d points.\n\n", get_average_grade_finished(user, n_projects));
	// printf("leozinho tem 75 medalhas e está nível 6 no 42cursus.\n\n");
	printf("----------------------------------------------------------------------------------------------------------------------------\n\n");
}
