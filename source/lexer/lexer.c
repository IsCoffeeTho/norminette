/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadue <amenadue@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 09:57:09 by amenadue          #+#    #+#             */
/*   Updated: 2022/07/24 17:23:43 by amenadue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

#define NORM_tabsize 4

Lexer *lexer__init__(int fd)
{
	Lexer *this = (Lexer *) ft_calloc(1, sizeof(Lexer));
	this->fd = fd;
	this->size = lseek(fd, 0, SEEK_END);
	this->__char = '\0';
	this->__slashed = 0;
	this->__pos = 0;
	this->__line_pos = 1;
	this->__line = 1;
	this->tokens = NULL;
	lseek(fd, 0, SEEK_SET);
	return (this);
}

char lexer_pop_char(Lexer *this)
{
	char _c;
	this->__char = '\0';
	this->__slashed = 0;
	this->__pos += read(this->fd, &_c, 1);
	if (this->__pos < this->size)
	{
		if (_c == '\\')
		{
			this->__pos += read(this->fd, &_c, 1);
			this->__char = _c;
			this->__slashed = 1;
		}
		else
			this->__char = _c;
	}
	
	if (this->__char == '\n')
	{
		this->__line_pos = 1;
		this->__line++;
	}
	else if (this->__char == '\t')
		this->__line_pos += NORM_tabsize - (this->__line_pos % NORM_tabsize);
	else if (this->__slashed)
		this->__line_pos += 2;
	else
		this->__line_pos++;
	return (this->__char);
}

Token_lst *lexer_get_next_token(Lexer *lex)
{
	Token_lst *token = NULL;
	while (lex->__char != '\0')
		;
	return (token);
}

Token_lst *lexer_get_tokens(Lexer *lex)
{
	while (lexer_get_next_token(lex))
		continue;
	return (lex->tokens);
}