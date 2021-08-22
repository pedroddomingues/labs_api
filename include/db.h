#ifndef DB_H
# define DB_H

# include <libpq-fe.h>

PGconn	*db_connect(char *connection_information);

void	db_disconnect(PGconn *conn);

int		db_push_user(char *user_info, PGconn *conn);

int		db_pull_user(char *login, PGconn *conn);

int		db_push_project(char *user_project, PGconn *conn);

#endif
