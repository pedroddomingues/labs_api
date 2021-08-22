/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenriq <pehenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 17:25:46 by pehenriq          #+#    #+#             */
/*   Updated: 2021/08/22 15:46:57 by pehenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/labs.h"

int	db_push_user(char *user_info, PGconn *conn)
{
	PGresult	*res;
	char		*query;

	query = malloc(sizeof(char) * 512 * 128);
	strcpy(query, "INSERT INTO public.user VALUES (");
	strcat(query, user_info);
	strcat(query, ") ON CONFLICT (id) DO UPDATE SET correction_point = EXCLUDED.correction_point;");
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

int	db_pull_user(char *login, PGconn *conn)
{
	PGresult	*res;
	char		*query;

	query = malloc(sizeof(char) * 1024);
	strcpy(query, "SELECT * FROM public.user WHERE login='");
	strcat(query, login);
	strcat(query, "';");
	printf("%s", query);
	res = PQexec(conn, query);

	if (PQresultStatus(res) != PGRES_TUPLES_OK) 
	{
		printf("nothing recieved, are you sure this is a correct login?");
		free(query);
		db_disconnect(conn);
		return (-1);
	}
 	int ncols = PQnfields(res);
	for (int i=0; i<ncols; i++) {
		char *name = PQfname(res, i);
		char *value = PQgetvalue(res, 0, i);
		printf("%s: %s\n", name, value);
	}
	PQclear(res);
	free(query);
	return (0);
}
