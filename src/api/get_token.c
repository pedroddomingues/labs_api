/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenriq <pehenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 23:03:29 by pehenriq          #+#    #+#             */
/*   Updated: 2021/08/18 17:47:48 by pehenriq         ###   ########.fr       */
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

char *get_token(char *uid, char *secret)
{
	CURL *curl;
	CURLcode response;
	char  url[] = "https://api.intra.42.fr/oauth/token";
	char  data[1024] = "grant_type=client_credentials&client_id=";
	t_memory_struct response_data;
 
	response_data.memory = malloc(1);
	response_data.size = 0;

	curl_global_init(CURL_GLOBAL_ALL);
	strcat(data, uid);
	strcat(data, "&client_secret=");
	strcat(data, secret);
 
	curl = curl_easy_init();
	if(curl) {

		curl_easy_setopt(curl, CURLOPT_URL, url);

		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, save_in_memory);

		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
		
		response = curl_easy_perform(curl);

		if(response != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
						curl_easy_strerror(response));
			return (NULL);
		}



		// // function to parse the response_data into the structs like:
		// user = json_to_struct(response_data);


		printf("%s", response_data.memory);
		
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	return (response_data.memory);
}
