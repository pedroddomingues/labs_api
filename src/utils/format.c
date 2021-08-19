/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenriq <pehenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:01:10 by pehenriq          #+#    #+#             */
/*   Updated: 2021/08/18 23:24:14 by pehenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/labs.h"

void	user_json_to_struct(t_user *user, char *user_json)
{
	struct json_object	*parsed_json;
	struct json_object	*id;
	struct json_object	*email;
	struct json_object	*login;
	struct json_object	*first_name;
	struct json_object	*last_name;
    struct json_object	*usual_first_name;
    struct json_object	*url;
    struct json_object	*displayname;
    struct json_object	*image_url;
    struct json_object	*staff;
    struct json_object	*correction_point;
    struct json_object	*pool_month;
    struct json_object	*pool_year;
    struct json_object	*location;

	parsed_json = json_tokener_parse(user_json);

	json_object_object_get_ex(parsed_json, "id", &id);
	user->id = json_object_get_int(id);
	printf("id: %d\n", user->id);

	json_object_object_get_ex(parsed_json, "email", &email);
	user->email = (char *) json_object_get_string(email);
	printf("email: %s\n", user->email);

	json_object_object_get_ex(parsed_json, "login", &login);
	user->login = (char *) json_object_get_string(login);
	printf("login: %s\n", user->login);

	json_object_object_get_ex(parsed_json, "first_name", &first_name);
	user->first_name = (char *) json_object_get_string(first_name);
	printf("first_name: %s\n", user->first_name);

	json_object_object_get_ex(parsed_json, "last_name", &last_name);
	user->last_name = (char *) json_object_get_string(last_name);
	printf("last_name: %s\n", user->last_name);

	json_object_object_get_ex(parsed_json, "usual_first_name", &usual_first_name);
	user->usual_first_name = (char *) json_object_get_string(usual_first_name);
	printf("usual_first_name: %s\n", user->usual_first_name);

	json_object_object_get_ex(parsed_json, "url", &url);
	user->url = (char *) json_object_get_string(url);
	printf("url: %s\n", user->url);

	json_object_object_get_ex(parsed_json, "displayname", &displayname);
	user->displayname = (char *) json_object_get_string(displayname);
	printf("displayname: %s\n", user->displayname);

	json_object_object_get_ex(parsed_json, "image_url", &image_url);
	user->image_url = (char *) json_object_get_string(image_url);
	printf("image_url: %s\n", user->image_url);

	json_object_object_get_ex(parsed_json, "pool_month", &pool_month);
	user->pool_month = (char *) json_object_get_string(pool_month);
	printf("pool_month: %s\n", user->pool_month);

	json_object_object_get_ex(parsed_json, "pool_year", &pool_year);
	user->pool_year = (char *) json_object_get_string(pool_year);
	printf("pool_year: %s\n", user->pool_year);

	json_object_object_get_ex(parsed_json, "location", &location);
	user->location = (char *) json_object_get_string(location);
	printf("location: %s\n", user->location);

	json_object_object_get_ex(parsed_json, "staff", &staff);
	user->staff = json_object_get_int(staff);
	printf("staff: %d\n", user->staff);

	json_object_object_get_ex(parsed_json, "correction_point", &correction_point);
	user->correction_point = json_object_get_int(correction_point);
	printf("correction_point: %d\n", user->correction_point);



















	
	return ;
}
