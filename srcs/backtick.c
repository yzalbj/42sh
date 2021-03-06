/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtick.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <ccabral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 15:07:25 by ccabral           #+#    #+#             */
/*   Updated: 2018/06/12 22:43:14 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <backtick.h>
#include <fcntl.h>
#include <stdlib.h>
#include <libft.h>
#include <ft_string.h>
#include <ft_printf.h>
#include <execute.h>

char	*ft_strchr_skipbs(char const *s, int c)
{
	while (1)
	{
		if (*s == '\\')
		{
			if (!*s++)
				break ;
		}
		else if (*s == (char)c)
			return ((char *)s);
		if (!*s++)
			break ;
	}
	return (NULL);
}

char	*get_back_tick_content(char *str, size_t pos, char **start, char **stop)
{
	if (!(*start = ft_strchr_skipbs(str + pos, '`')))
		return (0);
	if (!(*stop = ft_strchr_skipbs(*start + 1, '`')))
		return (0);
	return (ft_memdup(*start + 1, *stop - *start - 1));
}

int		collect_command_output(char *str, int read_write[2])
{
	int	save_stdout;

	if ((save_stdout = dup(STDOUT_FILENO)) == -1)
		return (0);
	if (pipe(read_write) == -1)
	{
		close(save_stdout);
		return (0);
	}
	dup2(read_write[1], 1);
	close(read_write[1]);
	remove_backslash(str);
	process_input_after_backtick(str);
	close(1);
	read_write[1] = save_stdout;
	return (1);
}

char	*escapeshell(char *origin)
{
	t_string	*str1;

	str1 = ft_memalloc(sizeof(t_string));
	str1->buffer = ft_strdup(origin);
	str1->size = ft_strlen(origin);
	str1->capacity = ft_strlen(origin);
	string_replace(str1, "$", "\\$");
	string_replace(str1, "\"", "\\\"");
	string_replace(str1, "`", "\\`");
	origin = str1->buffer;
	free(str1);
	return (origin);
}

char	*command_output_to_string(int read_write[2])
{
	char	buffer[1024];
	char	*str;
	char	*tmp;
	char	*tmp2;
	int		size;

	str = ft_strdup("");
	while (str && (size = read(read_write[0], buffer, 1023)))
	{
		buffer[size] = '\0';
		tmp = str;
		tmp2 = escapeshell(buffer);
		str = ft_vjoin(4, str, "`", tmp2, "`");
		free(tmp);
		free(tmp2);
	}
	dup2(read_write[1], 1);
	close(read_write[0]);
	close(read_write[1]);
	if (size == -1)
	{
		free(str);
		str = 0;
	}
	return (str);
}

char	*replace_backtick(char *str, char *new_str, char *begin, char *end)
{
	char	*result;

	result = ft_strreplace(str, new_str, begin - str, end - str);
	free(str);
	result = backticks_replace(result, (begin - str) + ft_strlen(new_str));
	free(new_str);
	return (result);
}
