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
# include "json.h"

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
	int				cursus_ids[];
}					t_user_projects;

typedef struct s_user
{
	int				id;
	char			*email;
    char			*login;
    char			*first_name;
    char			*last_name;
    char			*usual_first_name;
    char			*url;
    char			*displayname;
    char			*image_url;
    int				staff;
    int				correction_point;
    char			*pool_month;
    char			*pool_year;
    char			*location;
	t_user_cursus	cursus[32];
	t_user_projects	projects[];
}					t_user;

typedef struct s_memory_struct
{
	char *memory;
	size_t size;
}				t_memory_struct;

#endif
