#ifndef LABS_H
# define LABS_H
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <curl/curl.h>
# include "db.h"
# include "api42.h"

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
	unsigned int	project_id;
	char			*name;
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
	t_user_projects	projects[128];
}					t_user;

typedef struct s_memory_struct
{
	char *memory;
	size_t size;
}				t_memory_struct;

char	*user_json_to_struct(t_user *user, char *user_json);

char	**user_projects_json_to_struct(t_user *user, char *user_json, int *n_projects);

char	*ft_ullitoa_base(unsigned long long int n, char *base);

char	*ft_itoa(int n);

void	print_user(t_user *user);

void	print_projects(t_user *user, int n_projects);

void	print_analysis(t_user *user, int n_projects);

int		get_average_grade_finished(t_user *user, int n_projects);

int		get_average_grade_all(t_user *user, int n_projects);

#endif
