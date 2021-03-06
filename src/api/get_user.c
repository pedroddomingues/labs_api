/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_user.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenriq <pehenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 23:03:29 by pehenriq          #+#    #+#             */
/*   Updated: 2021/08/22 15:46:57 by pehenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/labs.h"

static size_t	save(char *buff, size_t size, size_t nmemb, void *data)
{
	t_memory_struct	*mem;
	size_t			realsize;
	char			*ptr;

	mem = (t_memory_struct *)data;
	realsize = size * nmemb;
	ptr = realloc(mem->memory, mem->size + realsize + 1);
	if (!ptr)
	{
		printf("not enough memory (realloc returned NULL)\n");
		return (0);
	}
	mem->memory = ptr;
	memcpy(&(mem->memory[mem->size]), buff, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;
	return (realsize);
}

//returns 1 if ok, -1 if error, 0 if response is empty
char	*get_user(char *login, char *token)
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
	if (curl) {
		struct curl_slist *header = NULL;
		header = curl_slist_append(header, auth_header);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, save);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
		response = curl_easy_perform(curl);
		if (response != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
						curl_easy_strerror(response));
			free(response_data.memory);
			return (NULL);
		}
		curl_easy_cleanup(curl);
		curl_slist_free_all(header);
	}
	curl_global_cleanup();
	return (response_data.memory);
}
