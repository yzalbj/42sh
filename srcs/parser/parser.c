/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 19:02:35 by claudioca         #+#    #+#             */
/*   Updated: 2018/03/19 14:59:11 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shellma.h>
#include <stdlib.h>
#include <array.h>
#include <tree.h>
#include <token.h>
#include <parser.h>
#include <ft_printf.h>

t_tree		*and_or(t_tree *tree, t_array *tokens, t_token **current)
{
	t_tree	*branch;

	ZERO_IF_FAIL(branch = pipeline(0, tokens, current));
	while (1)
	{
		if (match(current, AND_IF, OR_IF, SENTINEL))
		{
			branch = tree_add_child(
					tree_create_node(*current - 1, sizeof(t_token)), branch);
		}
		else if (!peek(current, SEMICOLON, TOKEN_END, SENTINEL))
			branch = pipeline(branch, tokens, current);
		else
			break ;
	}
	return (tree_add_child(tree, branch));
}

t_tree		*list(t_tree *tree, t_array *tokens, t_token **current)
{
	t_token token;
	t_tree	*child;

	token = emit_token(LIST, 0, 0, 0);
	ZERO_IF_FAIL(tree = tree_add_child(tree,
				tree_create_node(&token, sizeof(t_token))));
	while (1)
	{
		if (match(current, SEMICOLON, SENTINEL))
			continue ;
		else if (!peek(current, TOKEN_END, SENTINEL))
		{
			if (!(child = and_or(0, tokens, current)))
			{
				tree_free(tree, &noop);
				return (0);
			}
			if (!(tree = tree_add_child(tree, child)))
				break ;
		}
		else
			break ;
	}
	return (tree);
}

t_tree		*complete_command(t_tree *tree, t_array *tokens,
		t_token **current)
{
	tree = list(tree, tokens, current);
	return (tree);
}

t_tree		*parse(t_array *tokens)
{
	t_token	*current;
	t_tree	*tree;
	t_tree	*child;

	if (!tokens || peek((t_token**)&tokens->begin, TOKEN_END, SENTINEL))
	{
		array_free(tokens, &noop);
		return (0);
	}
	tree = 0;
	current = (t_token *)(tokens->begin);
	while (1)
	{
		if (peek(&current, TOKEN_END, SENTINEL))
			break;
		else if (!(child = complete_command(0, tokens, &current)))
			break ;
		if (!(tree = tree_add_child(tree, child)))
			break ;
	}
	array_free(tokens, &noop);
	if (!tree)
		ft_dprintf(2, "parse error\n");
	return (tree);
}
