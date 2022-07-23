/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadue <amenadue@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 09:57:09 by amenadue          #+#    #+#             */
/*   Updated: 2022/07/23 11:32:28 by amenadue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

Lexer *lexer__init__(int fd)
{
	Lexer *this = (Lexer *) ft_calloc(1, sizeof(Lexer));
	this->fd = fd;
	this->size = lseek(fd, 0, SEEK_END);
	this->__char = '\0';
	this->__pos = 0;
	this->__line_pos = 0;
	this->__line = 0;
	this->tokens = NULL;
	lseek(fd, 0, SEEK_SET);
	return (this);
}

char lexer_peek_char(Lexer *this)
{
	if (this->__pos < this->size)
	{
		if (this->)
	}
}

Token_lst *lexer_get_next_token(Lexer *lex)
{
	Token_lst *token = NULL;
	while (lexer_peek_char(lex) != '\0')
		;
	return (token);
}

Token_lst *lexer_get_tokens(Lexer *lex)
{
	while (lexer_get_next_token(lex))
		continue;
	return (lex->tokens);
}