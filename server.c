
#ifndef _WIN32
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#include <ulfius.h>
#include "include/labs.h"

#define PORT 80
#define PREFIX "/user"
#define PREFIXJSON "/testjson"

/**
 * callback functions declaration
 */
int callback_user (const struct _u_request * request, struct _u_response * response, void * user_data);

int callback_default (const struct _u_request * request, struct _u_response * response, void * user_data);

/**
 * decode a u_map into a string
 */
char * print_map(const struct _u_map * map)
{
	char * line, * to_return = NULL;
	const char **keys, * value;
	int len, i;
	if (map != NULL)
	{
		keys = u_map_enum_keys(map);
		for (i=0; keys[i] != NULL; i++)
		{
			value = u_map_get(map, keys[i]);
			len = snprintf(NULL, 0, "key is %s, value is %s", keys[i], value);
			line = o_malloc((len+1)*sizeof(char));
			snprintf(line, (len+1), "key is %s, value is %s", keys[i], value);
			if (to_return != NULL) {
			len = o_strlen(to_return) + o_strlen(line) + 1;
			to_return = o_realloc(to_return, (len+1)*sizeof(char));
			if (o_strlen(to_return) > 0)
				strcat(to_return, "\n");
		}
		else
		{
			to_return = o_malloc((o_strlen(line) + 1)*sizeof(char));
			to_return[0] = 0;
		}
		strcat(to_return, line);
		o_free(line);
		}
	return (to_return);
	}
	else
		return (NULL);
}

int main (int argc, char **argv)
{
	int ret;

	// Set the framework port number
	struct _u_instance instance;

	y_init_logs("42labs_api", Y_LOG_MODE_CONSOLE, Y_LOG_LEVEL_DEBUG, NULL, "Starting 42labs_api");

	if (ulfius_init_instance(&instance, PORT, NULL, NULL) != U_OK)
	{
		y_log_message(Y_LOG_LEVEL_ERROR, "Error ulfius_init_instance, abort");
		return(1);
	}

	u_map_put(instance.default_headers, "Access-Control-Allow-Origin", "*");

	// Maximum body size sent by the client is 1 Kb
	instance.max_post_body_size = 1024;

	// Endpoint list declaration
	ulfius_add_endpoint_by_val(&instance, "GET", PREFIX, "/:login", 0, &callback_user, NULL);

	// default_endpoint declaration
	ulfius_set_default_endpoint(&instance, &callback_default, NULL);

	// Start the framework
	// if (argc == 4 && o_strcmp("-secure", argv[1]) == 0) {
	// // If command-line options are -secure <key_file> <cert_file>, then open an https connection
	// char * key_pem = read_file(argv[2]), * cert_pem = read_file(argv[3]);
	// ret = ulfius_start_secure_framework(&instance, key_pem, cert_pem);
	// o_free(key_pem);
	// o_free(cert_pem);
	// } else {
	// Open an http connection
	ret = ulfius_start_framework(&instance);
	// }

	if (ret == U_OK)
	{
		y_log_message(Y_LOG_LEVEL_DEBUG, "Start %sframework on port %d", ((argc == 4 && o_strcmp("-secure", argv[1]) == 0)?"secure ":""), instance.port);

		// Wait for the user to press <enter> on the console to quit the application
		getchar();
	}
	else
		y_log_message(Y_LOG_LEVEL_DEBUG, "Error starting framework");
	y_log_message(Y_LOG_LEVEL_DEBUG, "End framework");

	y_close_logs();

	ulfius_stop_framework(&instance);
	ulfius_clean_instance(&instance);

	return 0;
}

/**
 * Callback function that put "Hello World!" and all the data sent by the client in the response as string (http method, url, params, cookies, headers, post, json, and user specific data in the response
 */
int callback_user (const struct _u_request * request, struct _u_response * response, void * user_data)
{
	char *url_params = print_map(request->map_url);
	char *headers = print_map(request->map_header);
	char *cookies = print_map(request->map_cookie);
	char *post_params = print_map(request->map_post_body);
	char *response_body;
	char *api_response;
	char	*user_info;
	char	**user_projects;
	int		n_projects;
	int		db_return;
	PGconn	*conn;
	t_user	*user;

	n_projects = 0;
	conn = db_connect(NULL);
	user = o_malloc(sizeof(*user)*100);
	if (request->map_url->nb_values > 2)
		response_body = o_strdup("You should provide only the token as query param. The correct request is /user/:login?token=YOURTOKEN");
	else if (strcmp(request->map_url->keys[0], "token"))
		response_body = o_strdup("You should provide a token. The correct request is /user/:login?token=YOURTOKEN");
	else
	{
		#ifndef _WIN32
		response_body = msprintf("Hello World!\n\nmethod is %s\nurl is %s\n\nparameters from the url are \n%s\n\ncookies are \n%s\n\nheaders are \n%s\n\npost parameters are \n%s\n\nuser data is %s\n\nclient address is %s\n\n",
										request->http_verb, request->http_url, url_params, cookies, headers, post_params, (char *)user_data, inet_ntoa(((struct sockaddr_in *)request->client_address)->sin_addr));
		#else
		response_body = msprintf("Hello World!\n\nmethod is %s\nurl is %s\n\nparameters from the url are \n%s\n\ncookies are \n%s\n\nheaders are \n%s\n\npost parameters are \n%s\n\nuser data is %s\n\n",
										request->http_verb, request->http_url, url_params, cookies, headers, post_params, (char *)user_data);
		#endif
	}
	api_response = get_user(request->map_url->values[1], request->map_url->values[0]);
	if (!strcmp(api_response, "{}"))
			{
				o_free(response_body);
				response_body = o_strdup("Error with the API request, probably invalid intra login.");
			}
			else if (!strcmp(api_response, "{\"error\":\"Not authorized\",\"message\":\"The access token expired\"}"))
			{
				o_free(response_body);
				response_body = o_strdup("\nToken expired, please get another one.\n");
			}
			else
			{
				o_free(response_body);
				response_body = o_strdup(api_response);
				user_info = user_json_to_struct(user, api_response);
				db_return = db_push_user(user_info, conn);
				if (db_return < 0)
					printf("\n\n\n\nFailed to insert data into the database.\n\n\n\n");
				user_projects = user_projects_json_to_struct(user, api_response, &n_projects);
				while (*user_projects)
				{
					db_return = db_push_project(*user_projects, conn);
					if (db_return < 0)
						printf("\n\n\n\nFailed to insert data into the database.\n\n\n\n");
					user_projects++;
				}
		}
	ulfius_set_string_body_response(response, 200, response_body);
	if (db_return >= 0)
		db_disconnect(conn);
	o_free(user);
	o_free(response_body);
	o_free(url_params);
	o_free(headers);
	o_free(cookies);
	o_free(post_params);
	return U_CALLBACK_CONTINUE;
}

/**
 * Default callback function called if no endpoint has a match
 */
int callback_default (const struct _u_request * request, struct _u_response * response, void * user_data)
{
	ulfius_set_string_body_response(response, 404, "Page not found. The correct request is /user/:login?token=YOURTOKEN");
	return U_CALLBACK_CONTINUE;
}
