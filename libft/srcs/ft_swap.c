/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 09:47:19 by ccabral           #+#    #+#             */
/*   Updated: 2018/01/05 10:38:04 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_swap(void *a, void *b, void *buffer, size_t size)
{
	ft_memcpy(buffer, a, size);
	ft_memcpy(a, b, size);
	ft_memcpy(b, buffer, size);
	ft_bzero(buffer, size);
}
