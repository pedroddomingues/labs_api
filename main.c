/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenriq <pehenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 16:40:09 by pehenriq          #+#    #+#             */
/*   Updated: 2021/08/20 04:11:26 by pehenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/labs.h"

static void	kill_user(t_user *user)
{
	free(user->email);
	free(user->login);
	free(user->first_name);
	free(user->last_name);
	free(user->url);
	free(user->displayname);
	free(user->image_url);
	free(user->pool_month);
	free(user->pool_year);
	free(user);
}

int main(int argc, char *argv[])
{
	t_user *user;
	char *token;
	PGconn	*conn;
	char	*response;
	char	*user_info;
	int		push;


	user = malloc(sizeof(*user)*100);
	// token = get_token("93ae758ab8266f7c4c419e58a605ea217aef2dd5c0776ac38521328dd9f0391f", "13c0e6d41d35465e40dbe6a1c67165c59940dc141c3443ddd9484b562187a7a9");
	// printf("token: %s\n\n", token);
	// if (!token)
	// {
	// 	printf("error getting the token");
	// 	return (-1);
	// }
	token = "e0e0718ba401f939cbba88f59b7d11016fac359677217284e0fb10fa68015a06";
	// free(token);
	// response = get_user(user, argv[1], token);
	// user_info = user_json_to_struct(user, response);
	conn = db_connect(NULL);
	// push = db_push_user(user_info, conn);
	push = db_pull_user(argv[1], conn);
	if (push < 0)
		db_disconnect(conn);
	// free(response);
	// free(user_info);
	kill_user(user);
	return (0);
}
