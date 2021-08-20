#ifndef LABS_H
# define LABS_H
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <curl/curl.h>
# include <libpq-fe.h>
# include <json-c/json.h>

typedef struct s_user_cursus
{
	char	*grade;
	int		level;
	long	cursus_users_id;
	char	*begin_at;
	char	*end_at;
	int		cursus_id;
	char	*name;
	char	*slug;
}	t_user_cursus;

typedef struct s_user_projects
{
	long			projects_users_id;
	int				occurrence;
	int				final_mark;
	char			*status;
	int				validated;
	unsigned long	current_team_id;
	unsigned int	project_id;
	char			*name;
	char			*slug;
	unsigned int	parent_id;
	char			*marked_at;
	int				marked;
	char			*retriable_at;
	char			*created_at;
	char			*updated_at;
}					t_user_projects;

typedef struct s_user
{
	int				id;
	char			*email;
    char			*login;
    char			*first_name;
    char			*last_name;
    char			*url;
    char			*displayname;
    char			*image_url;
    int				staff;
    int				correction_point;
    char			*pool_month;
    char			*pool_year;
	t_user_cursus	cursus[64];
	t_user_projects	projects[];
}					t_user;

typedef struct s_memory_struct
{
	char *memory;
	size_t size;
}				t_memory_struct;

char	*get_user(t_user *user, char *login, char *token);

char	*get_token(char *uid, char *secret);

char	*user_json_to_struct(t_user *user, char *user_json);

PGconn	*db_connect(char *connection_information);

void	db_disconnect(PGconn *conn);

int		db_push_user(char *user_info, PGconn *conn);

int		db_pull_user(char *login, PGconn *conn);

char	*ft_ullitoa_base(unsigned long long int n, char *base);

char	*ft_itoa(int n);

#endif
