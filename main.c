/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenriq <pehenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 16:40:09 by pehenriq          #+#    #+#             */
/*   Updated: 2021/08/18 17:49:12 by pehenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/labs.h"

int main(int argc, char *argv[])
{
	static t_user user;
	char *token;

	
	token = get_token("93ae758ab8266f7c4c419e58a605ea217aef2dd5c0776ac38521328dd9f0391f", "13c0e6d41d35465e40dbe6a1c67165c59940dc141c3443ddd9484b562187a7a9");
	get_user(&user, argv[1], token);
	return (0);
}
