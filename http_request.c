/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_request.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenriq <pehenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 23:03:29 by pehenriq          #+#    #+#             */
/*   Updated: 2021/08/18 02:39:26 by pehenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "labs.h"

size_t save_in_memory(char *contents, size_t size, size_t nmemb, void *userdata)
{
	size_t realsize = size * nmemb;
	t_memory_struct *mem = (struct MemoryStruct *)userdata;

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

int main(int argc, char *argv[])
{
	CURL *curl;
	CURLcode response;
	char  url[1024] = "https://api.intra.42.fr/v2/users/";
	t_memory_struct chunk;
	t_user	user;
 
	chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */
	chunk.size = 0;    /* no data at this point */

	curl_global_init(CURL_GLOBAL_ALL);
	strcat(url, argv[1]);
 
	curl = curl_easy_init();
	if(curl) {
		struct curl_slist *header = NULL;
		header = curl_slist_append(header, "Authorization: Bearer 2a20ebca2f2856645b01f9e8b84c24fda5950a14860a1f9e9aa51faf1e44525c");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);

		curl_easy_setopt(curl, CURLOPT_URL, url);

		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, save_in_memory);

		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);
		
		response = curl_easy_perform(curl);

		if(response != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
							curl_easy_strerror(response));



		// function to parse the chunk into the structs like:
		user = json_to_struct(chunk);

		// function to store the user data in the database:
		int store_user(user);



		
		curl_easy_cleanup(curl);
		curl_slist_free_all(header);
	}
	curl_global_cleanup();
	return 0;
}
