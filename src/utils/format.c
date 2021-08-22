/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenriq <pehenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:01:10 by pehenriq          #+#    #+#             */
/*   Updated: 2021/08/22 16:09:38 by pehenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/labs.h"
#include <json-c/json.h>

static void	insert_string(char *src, char *str)
{
	strcat(src, "'");
	strcat(src, str);
	strcat(src, "'");
}

char	*user_json_to_struct(t_user *user, char *user_json)
{
	char				*user_info;
	struct json_object	*json_project;
	struct json_object	*id;
	struct json_object	*email;
	struct json_object	*login;
	struct json_object	*first_name;
	struct json_object	*last_name;
    struct json_object	*url;
    struct json_object	*displayname;
    struct json_object	*image_url;
    struct json_object	*staff;
    struct json_object	*correction_point;
    struct json_object	*pool_month;
    struct json_object	*pool_year;

	user_info = calloc(sizeof(char), 2048 * 32);

	json_project = json_tokener_parse(user_json);

	json_object_object_get_ex(json_project, "id", &id);
	user->id = json_object_get_int(id);
	strcat(user_info, ft_itoa(user->id));
	strcat(user_info, ",");

	json_object_object_get_ex(json_project, "email", &email);
	user->email = strdup((char *) json_object_get_string(email));
	if (user->email != NULL)
		insert_string(user_info, user->email);
	strcat(user_info, ",");

	json_object_object_get_ex(json_project, "first_name", &first_name);
	user->first_name = strdup((char *) json_object_get_string(first_name));
	if (user->first_name != NULL)
		insert_string(user_info, user->first_name);
	strcat(user_info, ",");

	json_object_object_get_ex(json_project, "last_name", &last_name);
	user->last_name = strdup((char *) json_object_get_string(last_name));
	if (user->last_name != NULL)
		insert_string(user_info, user->last_name);
	strcat(user_info, ",");

	json_object_object_get_ex(json_project, "url", &url);
	user->url = strdup((char *) json_object_get_string(url));
	if (user->url != NULL)
		insert_string(user_info, user->url);
	strcat(user_info, ",");
	
	json_object_object_get_ex(json_project, "displayname", &displayname);
	user->displayname = strdup((char *) json_object_get_string(displayname));
	if (user->displayname != NULL)
		insert_string(user_info, user->displayname);
	strcat(user_info, ",");

	json_object_object_get_ex(json_project, "image_url", &image_url);
	user->image_url = strdup((char *) json_object_get_string(image_url));
	if (user->image_url != NULL)
		insert_string(user_info, user->image_url);
	strcat(user_info, ",");

	json_object_object_get_ex(json_project, "staff", &staff);
	user->staff = json_object_get_int(staff);
	strcat(user_info, ft_itoa(user->staff));
	strcat(user_info, ",");

	json_object_object_get_ex(json_project, "correction_point", &correction_point);
	user->correction_point = json_object_get_int(correction_point);
	strcat(user_info, ft_itoa(user->correction_point));
	strcat(user_info, ",");

	json_object_object_get_ex(json_project, "pool_month", &pool_month);
	user->pool_month = strdup((char *) json_object_get_string(pool_month));
	if (user->pool_month != NULL)
		insert_string(user_info, user->pool_month);
	strcat(user_info, ",");

	json_object_object_get_ex(json_project, "pool_year", &pool_year);
	user->pool_year = strdup((char *) json_object_get_string(pool_year));
	if (user->pool_year != NULL)
		insert_string(user_info, user->pool_year);
	strcat(user_info, ",");

	json_object_object_get_ex(json_project, "login", &login);
	user->login = strdup((char *) json_object_get_string(login));
	if (user->login != NULL)
		insert_string(user_info, user->login);

	return (user_info);
}

char	**user_projects_json_to_struct(t_user *user, char *user_json, int *n_projects)
{
	static char			*user_projects[128];
	char				*user_project;
	struct json_object	*user_obj;
	struct json_object	*projects_users_id;
	struct json_object	*occurrence;
	struct json_object	*final_mark;
	struct json_object	*status;
	struct json_object	*validated;
	struct json_object	*project_obj;
	struct json_object	*project_id;
	struct json_object	*name;
	struct json_object	*marked_at;
	struct json_object	*marked;
	struct json_object	*retriable_at;
	struct json_object	*created_at;
	struct json_object	*updated_at;
	struct json_object	*json_projects;
	struct json_object	*json_project;
	int					i;
	char				*tmp;


	user_obj = json_tokener_parse(user_json);


	json_object_object_get_ex(user_obj, "projects_users", &json_projects);
	*n_projects = json_object_array_length(json_projects);

	for(i = 0; i < *n_projects; i++)
	{
		user_project = calloc(sizeof(char), 512);
		json_project = json_object_array_get_idx(json_projects, i);
		json_object_object_get_ex(json_project, "id", &projects_users_id);
		json_object_object_get_ex(json_project, "occurrence", &occurrence);
		json_object_object_get_ex(json_project, "final_mark", &final_mark);
		json_object_object_get_ex(json_project, "status", &status);
		json_object_object_get_ex(json_project, "validated?", &validated);
		json_object_object_get_ex(json_project, "project", &project_obj);
		json_object_object_get_ex(json_project, "marked_at", &marked_at);
		json_object_object_get_ex(json_project, "marked", &marked);
		json_object_object_get_ex(json_project, "retriable_at", &retriable_at);
		json_object_object_get_ex(json_project, "created_at", &created_at);
		json_object_object_get_ex(json_project, "updated_at", &updated_at);
		
		user->projects[i].projects_users_id = json_object_get_int(projects_users_id);
		tmp = ft_ullitoa_base(user->projects[i].projects_users_id, "0123456789");
		strcat(user_project, tmp);
		strcat(user_project, ",");
		free(tmp);

		user->projects[i].occurrence = json_object_get_int(occurrence);
		tmp = ft_ullitoa_base(user->projects[i].occurrence, "0123456789");
		strcat(user_project, tmp);
		strcat(user_project, ",");
		free(tmp);
		
		user->projects[i].final_mark = json_object_get_int(final_mark);
		tmp = ft_ullitoa_base(
			user->projects[i].final_mark, "0123456789"
		);
		strcat(user_project, tmp);
		strcat(user_project, ",");
		free(tmp);

		user->projects[i].status = strdup((char *) json_object_get_string(status));
		if (user->projects[i].status != NULL)
			insert_string(user_project, user->projects[i].status);
		strcat(user_project, ",");

		user->projects[i].validated = json_object_get_int(validated);
		tmp = ft_itoa(user->projects[i].validated);
		strcat(user_project, tmp);
		strcat(user_project, ",");
		free(tmp);
		
		json_object_object_get_ex(project_obj, "id", &project_id);
		user->projects[i].project_id = json_object_get_int(project_id);
		tmp = ft_itoa(user->projects[i].project_id);
		strcat(user_project, tmp);
		strcat(user_project, ",");
		free(tmp);

		json_object_object_get_ex(project_obj, "name", &name);
		user->projects[i].name = strdup((char *) json_object_get_string(name));
		if (user->projects[i].name != NULL)
			insert_string(user_project, user->projects[i].name);
		strcat(user_project, ",");

		if (json_object_get_string(marked_at) == NULL)
		{
			user->projects[i].marked_at = "null";
			strcat(user_project, "null");
		}
		else
		{
			user->projects[i].marked_at = strdup((char *) json_object_get_string(marked_at));
			if (user->projects[i].marked_at != NULL)
			insert_string(user_project, user->projects[i].marked_at);
		}
		strcat(user_project, ",");
		
		user->projects[i].marked = json_object_get_int(marked);
		tmp = ft_itoa(user->projects[i].marked);
		strcat(user_project, tmp);
		strcat(user_project, ",");
		free(tmp);

		if (json_object_get_string(retriable_at) == NULL)
		{
			user->projects[i].retriable_at = "null";
			strcat(user_project, "null");
		}
		else
		{
			user->projects[i].retriable_at = strdup((char *) json_object_get_string(retriable_at));
			if (user->projects[i].retriable_at != NULL)
			insert_string(user_project, user->projects[i].retriable_at);
		}
		strcat(user_project, ",");

		user->projects[i].created_at = strdup((char *) json_object_get_string(created_at));
		if (user->projects[i].created_at != NULL)
			insert_string(user_project, user->projects[i].created_at);
		strcat(user_project, ",");

		user->projects[i].updated_at = strdup((char *) json_object_get_string(updated_at));
		if (user->projects[i].updated_at != NULL)
			insert_string(user_project, user->projects[i].updated_at);
		strcat(user_project, ",");

		tmp = ft_itoa(user->id);
		strcat(user_project, tmp);
		free(tmp);

		user_projects[i] = user_project;
	}
	return (user_projects);
}

