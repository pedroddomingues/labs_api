/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenriq <pehenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 16:40:09 by pehenriq          #+#    #+#             */
/*   Updated: 2021/08/22 16:33:27 by pehenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/labs.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

static void	kill_mallocs(t_user *user, char *response, char *user_info, char **user_projects)
{
	free(response);
	free(user_info);
	while (*user_projects)
	{
		free(*user_projects);
		user_projects++;
	}
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
	int		i;
	char	input[21];
	char	*token;
	PGconn	*conn;
	int		db_return;
	t_user	*user;
	char	*response;
	char	*instructions = "-----INSTRUCTIONS-----\nUse this program to search for data about a student of 42 network.\nYou can provide the API token when calling the executing file or follow the steps with you UID and SECRET.";
	char	*user_info;
	char	**user_projects;
	int		n_projects;

	i = 1;
	n_projects = 0;
	if (argc == 2)
		token = argv[1];
	else if (argc > 2)
		printf("You should only insert the token");
	if (argc != 2)
	{
		token = print_get_token();
		if (!token)
			return (-1);
		printf("%s", token);
	}
	conn = db_connect(NULL);
	user = malloc(sizeof(*user)*100);
	response = malloc(sizeof(char)*4096);
	while (i)
	{
		if (i == 1)
			printf("%s", instructions);
		printf("\nType the login to search or exit to stop the program.\n\n");
		fgets(input, 20, stdin);
		input[strlen(input) - 1] = '\0';
		if (!strcmp(input, "exit"))
			exit_message(&i);
		else
		{
			response = get_user(input, token);
			if (!strcmp(response, "{}"))
			{
				printf("Error with the API request, check token if provided in execution or invalid intra login.");
			}
			else if (!strcmp(response, "{\"error\":\"Not authorized\",\"message\":\"The access token expired\"}"))
			{
				printf("\nToken expired, please get another one.\n");
				return (-1);
			}
			else
			{
				user_info = user_json_to_struct(user, response);
				db_return = db_push_user(user_info, conn);
				if (db_return < 0)
					printf("\n\n\n\nFailed to insert data into the database.\n\n\n\n");
				user_projects = user_projects_json_to_struct(user, response, &n_projects);
				while (*user_projects)
				{
					db_return = db_push_project(*user_projects, conn);
					if (db_return < 0)
						printf("\n\n\n\nFailed to insert data into the database.\n\n\n\n");
					user_projects++;
				}
				print_user(user);
				print_projects(user, n_projects);
				print_analysis(user, n_projects);
			}
		}
		i++;
	}
	if (db_return >= 0)
		db_disconnect(conn);
	if (argc != 2)
		free(token);
	kill_mallocs(user, response, user_info, user_projects);
	return (0);
}
