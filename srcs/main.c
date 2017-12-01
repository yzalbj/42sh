/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 14:06:17 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/01 18:45:15 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sessions.h>

int	main(int argc, char **argv)
{
	if (argc == 1)
		return (interactive_session());
	return (script_session(argc, argv));
}
