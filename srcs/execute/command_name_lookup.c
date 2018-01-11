/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_name_lookup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 11:48:51 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/11 15:24:42 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <array.h>
#include <hash_table.h>
#include <builtins.h>
#include <execute.h>

static	t_hash_table	*g_builtins;
static	t_array			*g_paths;

uint64_t				builtin_hash(t_builtin *builtin)
{
	return (hash_string(&builtin->name));
}

int						builtin_compare(t_builtin *a, t_builtin *b)
{
	return (ft_strcmp(a->name, b->name));
}

void					add_builtin(char *name, t_exec func)
{
	t_builtin	builtin;

	builtin.name = name;
	builtin.func = func;
	hash_table_insert(g_builtins, &builtin);
}

void					free_paths(t_array	*paths)
{
	t_binary_path	**it;

	if (!paths)
		return ;
	it = (t_binary_path **)paths->begin;
	while (it != paths->end)
	{
		hash_table_free((*it)->table, (t_freef)&free_wrapper);
		string_free((*it)->buffer);
		free(*it);
		++it;
	}
	free(paths->begin);
	free(paths);
}

int						init_builtins(void)
{
	ZERO_IF_FAIL(g_builtins = hash_table_create(sizeof(t_builtin), 16,
					(t_hashf)&builtin_hash, (t_cmpf)&builtin_compare));
	add_builtin("cd", &cd);
	add_builtin("echo", &echo);
	add_builtin("pwd", &pwd);
	add_builtin("env", &env);
	add_builtin("setenv", &builtin_setenv);
	add_builtin("unsetenv", &builtin_unsetenv);
	return (1);
}

int						generate_paths(void)
{
	free_paths(g_paths);
	g_paths = 0;
	return (init_paths(&g_paths));
}

int						init_path_table(void)
{
	ZERO_IF_FAIL(init_builtins());
	return (generate_paths());
}

__attribute__((always_inline))
t_builtin				*get_builtin_command(char const *name)
{
	t_builtin	dummy;

	dummy.name = name;
	return (hash_table_find(g_builtins, &dummy));
}

__attribute__((always_inline))
char const				*command_name_lookup(char const *name)
{
	t_binary_path	**path;
	char const		**entry;

	path = g_paths->begin;
	while (path != g_paths->end)
	{
		if ((entry = hash_table_find((*path)->table, &name)))
		{
			binary_path_set_buffer(*path, *entry);
			return ((*path)->buffer->buffer);
		}
		++path;
	}
	return(0);
}
