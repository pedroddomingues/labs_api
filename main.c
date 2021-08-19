/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenriq <pehenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 16:40:09 by pehenriq          #+#    #+#             */
/*   Updated: 2021/08/19 00:08:43 by pehenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/labs.h"

int main(int argc, char *argv[])
{
	static t_user user;
	char *token;


	// token = get_token("93ae758ab8266f7c4c419e58a605ea217aef2dd5c0776ac38521328dd9f0391f", "13c0e6d41d35465e40dbe6a1c67165c59940dc141c3443ddd9484b562187a7a9");
	// printf("%s", token);
	// if (!token)
	// {
	// 	printf("error getting the token");
	// 	return (-1);
	// }
	token = "df0b33bbbd5521467196c1a8f2be6c71259df84ef7bb93a29e5ae55a8afb8ef4";
	get_user(&user, argv[1], token);
	// free(token);
	return (0);
}
