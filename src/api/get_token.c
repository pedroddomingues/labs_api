/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenriq <pehenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 23:03:29 by pehenriq          #+#    #+#             */
/*   Updated: 2021/08/22 15:46:57 by pehenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/labs.h"

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	str = malloc(sizeof(char) * (len + 1));
	if (start >= strlen(s))
		return ((char *)memset(str, 0, 1));
	if (!str)
		return (NULL);
	memset(str + len, 0, 1);
	return (memmove(str, &s[start], len));
}

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
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, save);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
		response = curl_easy_perform(curl);
		if (response != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
						curl_easy_strerror(response));
			return (NULL);
		}
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	return (ft_substr(response_data.memory, 17, 64));
}
