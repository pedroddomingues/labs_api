/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenriq <pehenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:01:10 by pehenriq          #+#    #+#             */
/*   Updated: 2021/08/20 03:57:37 by pehenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/labs.h"

static void	insert_string(char *src, char *str)
{
	strcat(src, "'");
	strcat(src, str);
	strcat(src, "'");
}

char	*user_json_to_struct(t_user *user, char *user_json)
{
	char				*user_info;
	char				*tmp;
	struct json_object	*parsed_json;
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

	user_info = malloc(sizeof(char) * 2048 * 32);

	parsed_json = json_tokener_parse(user_json);

	json_object_object_get_ex(parsed_json, "id", &id);
	user->id = json_object_get_int(id);
	//printf("id: %d\n", user->id);
	strcpy(user_info, ft_itoa(user->id));
	strcat(user_info, ",");

	json_object_object_get_ex(parsed_json, "email", &email);
	user->email = strdup((char *) json_object_get_string(email));
	// printf("email: %s\n", user->email);
	if (user->email != NULL)
		insert_string(user_info, user->email);
	strcat(user_info, ",");

	json_object_object_get_ex(parsed_json, "first_name", &first_name);
	user->first_name = strdup((char *) json_object_get_string(first_name));
	//printf("first_name: %s\n", user->first_name);
	if (user->first_name != NULL)
		insert_string(user_info, user->first_name);
	strcat(user_info, ",");

	json_object_object_get_ex(parsed_json, "last_name", &last_name);
	user->last_name = strdup((char *) json_object_get_string(last_name));
	//printf("last_name: %s\n", user->last_name);
	if (user->last_name != NULL)
		insert_string(user_info, user->last_name);
	strcat(user_info, ",");

	json_object_object_get_ex(parsed_json, "url", &url);
	user->url = strdup((char *) json_object_get_string(url));
	//printf("url: %s\n", user->url);
	if (user->url != NULL)
		insert_string(user_info, user->url);
	strcat(user_info, ",");
	
	json_object_object_get_ex(parsed_json, "displayname", &displayname);
	user->displayname = strdup((char *) json_object_get_string(displayname));
	//printf("displayname: %s\n", user->displayname);
	if (user->displayname != NULL)
		insert_string(user_info, user->displayname);
	strcat(user_info, ",");

	json_object_object_get_ex(parsed_json, "image_url", &image_url);
	user->image_url = strdup((char *) json_object_get_string(image_url));
	//printf("image_url: %s\n", user->image_url);
	if (user->image_url != NULL)
		insert_string(user_info, user->image_url);
	strcat(user_info, ",");

	json_object_object_get_ex(parsed_json, "staff", &staff);
	user->staff = json_object_get_int(staff);
	//printf("staff: %d\n", user->staff);
	strcat(user_info, ft_itoa(user->staff));
	strcat(user_info, ",");

	json_object_object_get_ex(parsed_json, "correction_point", &correction_point);
	user->correction_point = json_object_get_int(correction_point);
	//printf("correction_point: %d\n", user->correction_point);
	strcat(user_info, ft_itoa(user->correction_point));
	strcat(user_info, ",");

	json_object_object_get_ex(parsed_json, "pool_month", &pool_month);
	user->pool_month = strdup((char *) json_object_get_string(pool_month));
	//printf("pool_month: %s\n", user->pool_month);
	if (user->pool_month != NULL)
		insert_string(user_info, user->pool_month);
	strcat(user_info, ",");

	json_object_object_get_ex(parsed_json, "pool_year", &pool_year);
	user->pool_year = strdup((char *) json_object_get_string(pool_year));
	//printf("pool_year: %s\n", user->pool_year);
	if (user->pool_year != NULL)
		insert_string(user_info, user->pool_year);
	strcat(user_info, ",");

	json_object_object_get_ex(parsed_json, "login", &login);
	user->login = strdup((char *) json_object_get_string(login));
	if (user->login != NULL)
		insert_string(user_info, user->login);
	//printf("login: %s\n", user->login);

	return (user_info);
}
