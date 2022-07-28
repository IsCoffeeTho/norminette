/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadue <amenadue@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 09:57:09 by amenadue          #+#    #+#             */
/*   Updated: 2022/07/29 07:30:54 by amenadue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

Token_lst *token__init__(char *type, size_t linepos, size_t line, char* value)
{
	Token_lst *this = (Token_lst *) ft_calloc(1, sizeof(Token_lst));
	this->type = type;
	this->linepos = linepos;
	this->line = line;
	if (value != NULL)
	{
		this->value = value;
		this->length = ft_strlen(value);
	}
	else
	{
		this->value = NULL;
		this->length = 0;
	}
	return (this);
}

char *token_tostr(Token_lst *token)
{
	char *rep;
	if (token->length)
	{
		rep = ft_strjoin("<", token->type);
		rep = ft_strjoin(rep, "=");
		rep = ft_strjoin(rep, token->value);
		rep = ft_strjoin(rep, ">");
	}
	else
	{
		rep = ft_strjoin("<", token->type);
		rep = ft_strjoin(rep, ">");
	}
	return (rep);
}