/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projects.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenriq <pehenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 17:18:27 by pehenriq          #+#    #+#             */
/*   Updated: 2021/08/22 15:46:57 by pehenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/labs.h"

int	db_push_project(char *user_project, PGconn *conn)
{
	PGresult	*res;
	char		*query;

	query = malloc(sizeof(char) * 512 * 128);
	strcpy(query, "INSERT INTO public.users_projects VALUES (");
	strcat(query, user_project);
	strcat(query, ") ON CONFLICT (projects_users_id) DO UPDATE SET occurrence = EXCLUDED.occurrence, final_mark = EXCLUDED.final_mark, status = EXCLUDED.status, validated = EXCLUDED.validated, marked_at = EXCLUDED.marked_at, marked = EXCLUDED.marked, retriable_at = EXCLUDED.retriable_at, updated_at = EXCLUDED.updated_at;");
	// printf("query: %s\n\n", query);
	res = PQexec(conn, query);

	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		printf("%s", (char *)res);
		free(query);
		return (-1);
	}
	PQclear(res);
	free(query);
	return (0);
}
