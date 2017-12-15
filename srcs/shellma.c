/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellma.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 12:19:30 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/15 12:39:07 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shellma.h>

__attribute__((always_inline))
int	process_input(char const *str)
{
	return (execute(parse(lex(str))));
}
