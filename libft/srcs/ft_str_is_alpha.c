/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 11:39:18 by ccabral           #+#    #+#             */
/*   Updated: 2017/12/17 16:39:57 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_str_is_alnum(const char *str)
{
	while (*str)
	{
		if (!ft_isalnum(*str))
			return (0);
		++str;
	}
	return (1);
}
