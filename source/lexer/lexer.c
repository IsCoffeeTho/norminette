/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadue <amenadue@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 09:57:09 by amenadue          #+#    #+#             */
/*   Updated: 2022/07/24 20:12:59 by amenadue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "norminette.h"

#define NORM_tabsize 4

void	TokenError(Lexer *this)
{
	norm_err = normError("TokenError", );
}

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
	if (lex->__pos == 0)
		lexer_pop_char(lex);
	while (lex->__char)
	{
		if (lex->__char == '"')
			lexer_string(lex);
		else if (lexer_isidentifier(lex))
			lexer_identifier(lex);
		else if (lexer_isconstant(lex))
			lexer_constant(lex);
		else if (lex->__char == '\'')
			lexer_char_constant(lex);
		else if (lex->__char == '#')
			lexer_preprocessor(lex);
		else if (lexer_iscomment(lex)) // this will be for both single and multi line
			lexer_comment(lex);
		else if (lexer_isop(lex))
			lexer_operator(lex);
		else if (lexer_isws(lex))
			lexer_ws(lex);
		else if (lexer_isbrackets(lex))
			lexer_bracket(lex);
		else
		{
			TokenError(lex);
			return;
		}
	}
	return (token);
}

Token_lst *lexer_get_tokens(Lexer *lex)
{
	while (lexer_get_next_token(lex))
		continue;
	return (lex->tokens);
}