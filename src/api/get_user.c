/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_user.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenriq <pehenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 23:03:29 by pehenriq          #+#    #+#             */
/*   Updated: 2021/08/18 16:50:19 by pehenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/labs.h"

static size_t save_in_memory(char *contents, size_t size, size_t nmemb, void *userdata)
{
	size_t realsize = size * nmemb;
	t_memory_struct *mem = (t_memory_struct *)userdata;

	char *ptr = realloc(mem->memory, mem->size + realsize + 1);
	if(!ptr)
	{
		printf("not enough memory (realloc returned NULL)\n");
		return 0;
	}

	mem->memory = ptr;
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}

//returns 1 if ok, -1 if error, 0 if response is empty
int get_user(t_user *user, char *login, char *token)
{
	CURL *curl;
	CURLcode response;
	char  url[1024] = "https://api.intra.42.fr/v2/users/";
	char  auth_header[512] = "Authorization: Bearer ";
	t_memory_struct response_data;
 
	response_data.memory = malloc(1);
	response_data.size = 0;

	curl_global_init(CURL_GLOBAL_ALL);
	strcat(url, login);
	strcat(auth_header, token);
 
	curl = curl_easy_init();
	if(curl) {
		struct curl_slist *header = NULL;
		header = curl_slist_append(header, auth_header);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);

		curl_easy_setopt(curl, CURLOPT_URL, url);

		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, save_in_memory);

		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
		
		response = curl_easy_perform(curl);

		if(response != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
						curl_easy_strerror(response));
			return (-1);
		}



		// // function to parse the response_data into the structs like:
		// user = json_to_struct(response_data);


		printf("%s", response_data.memory);
		
		curl_easy_cleanup(curl);
		curl_slist_free_all(header);
	}
	curl_global_cleanup();
	return (1);
}
