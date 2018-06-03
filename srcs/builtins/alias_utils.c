/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfloure <>                                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 22:15:38 by gfloure           #+#    #+#             */
/*   Updated: 2018/06/03 22:21:08 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <stdlib.h>

int				get_next(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ';')
			return (i + 1);
		i++;
	}
	return (i);
}

int				ft_strchral(char *s)
{
	int			i;

	i = -1;
	while (s[++i])
		if (s[i] == ' ' || s[i] == ';')
			return (i);
	return (i > 1 ? i  : -1);
}

int				get_alias_to_replace(t_string *str, int *i)
{
	char		*tmp;
	char		*tmp1;
	int			ret;

	while ((ret = ft_strchral(&str->buffer[*i])) != -1)
	{
		tmp = ft_strsub(str->buffer, *i, ret);
		tmp1 = alias_replace_process(tmp);
		string_delete_n(str, *i, ret);
		string_insert_string(str, tmp1, *i);
		tmp ? free(tmp) : 0;
		*i += get_next(&str->buffer[*i]);
	}
	return (1);
}

int			is_valid_alias(char *alias)
{
	(void)alias;
	int		i;

	i = 0;
	return (1);
}
