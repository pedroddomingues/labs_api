/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenriq <pehenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 16:40:09 by pehenriq          #+#    #+#             */
/*   Updated: 2021/08/20 21:31:46 by pehenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/labs.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

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

char	*print_get_token()
{
	char	*uid;
	char	*secret;
	char	*token;

	uid = malloc(sizeof(char) * 128);
	secret = malloc(sizeof(char) * 128);
	printf("Type your 42 API UID\n\n");
	fgets(uid, 129, stdin);
	uid[strlen(uid) - 1] = '\0';
	printf("\nType your 42 API SECRET\n\n");
	fgets(secret, 129, stdin);
	secret[strlen(secret) - 1] = '\0';
	token = get_token(uid, secret);
	if (!token)
	{
		printf("Error getting the token, try again\n");
		return (NULL);
	}
	else if (!strcmp(token, "error"))
	{
		printf("Invalid credentials or unauthorized, please try again\n");
		return (NULL);
	}
	free(uid);
	free(secret);
	return(token);
}

void	exit_message(int *i)
{
	printf("\nWe have searched %d user(s)!!\n", *i - 1);
	printf("Bye bye\n");
	*i = -1;
}

int main(int argc, char *argv[])
{
	// db_return = db_pull_user(argv[1], conn);

	int		i;
	char	input[21];
	char	*token;
	// PGconn	*conn;
	// int		db_return;
	t_user *user;
	char	*response;
	char	*user_info;

	i = 1;
	token = print_get_token();
	if (!token)
		return (-1);
	// conn = db_connect(NULL);
	user = malloc(sizeof(*user)*100);
	response = malloc(sizeof(char)*4096);
	while (i)
	{
		if (i == 1)
			printf("INSTRUCTIONS\n");
		printf("\nType the login to search or exit to stop\n\n");
		fgets(input, 20, stdin);
		input[strlen(input) - 1] = '\0';
		if (!strcmp(input, "exit"))
			exit_message(&i);
		else
		{
			//fetch data and store in the db
			response = get_user(user, input, token);
			if (!strcmp(response, "{}"))
			{
				printf("User not found, please try again.");
			}
			else
			{
				// user_info = user_json_to_struct(user, response);
				// db_return = db_push_user(user_info, conn);
				//if (db_return < 0)
				//	printf("Failed to insert data into the database.");
				printf("\nUser info: %s", response);
			}
		}
		i++;
	}
	// if (db_return >= 0)
	// 	db_disconnect(conn);
	free(token);
	free(response);
	free(user_info);
	kill_user(user);
	return (0);
}
