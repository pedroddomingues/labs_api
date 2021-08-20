/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenriq <pehenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 00:54:29 by pehenriq          #+#    #+#             */
/*   Updated: 2021/08/19 17:28:21 by pehenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/labs.h"

PGconn	*db_connect(char *connection_information)
{
	const char	*conninfo;
	PGconn		*conn;

	if (connection_information)
		conninfo = connection_information;
	else
		conninfo = "dbname = 42sp_labs host = database-1.c3h9jk6hltop.sa-east-1.rds.amazonaws.com user = postgres password = labs42sp";

	conn = PQconnectdb(conninfo);

	if (PQstatus(conn) != CONNECTION_OK)
	{
		fprintf(stderr, "Connection to database failed: %s",
				PQerrorMessage(conn));
		db_disconnect(conn);
	}
	return (conn);
}

void	db_disconnect(PGconn *conn)
{
	PQfinish(conn);
}
