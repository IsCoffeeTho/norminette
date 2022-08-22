/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadue <amenadue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 09:57:09 by amenadue          #+#    #+#             */
/*   Updated: 2022/08/22 15:24:09 by amenadue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "norminette.h"

#define NORM_tabsize 4

#define lexer_peek_char(lexerstruct) lexerstruct->__char

void	TokenError(Lexer *this)
{
	char *str = ft_strjoin("Error: Unrecognixed token line ", ft_itoa(this->__line));
	char *tmp = str;
	str = ft_strjoin(str, ", col ");
	free(tmp);
	tmp = str;
	str = ft_strjoin(str, ft_itoa(this->__line_pos));
	free(tmp);
	norm_err = Exception("TokenError", str);
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

void	lexer_string(Lexer *this)
{
	size_t	start;
	size_t	l;
	char	*tkn_value;
	
	if (lexer_peek_char(this) == 'L')
	{
		start = this->__pos;
		lexer_pop_char(this);
	}
	if (start)
		l++;
	else
		start = this->__pos;
	lexer_pop_char(this);
	while (lexer_peek_char(this))
	{
		l++;
		if (lexer_peek_char(this) == '"' && !this->__slashed)
			break;
		lexer_pop_char(this);
	}
	if (lexer_peek_char(this) == '\0')
	{
		TokenError(this);
		return ;
	}
	tkn_value = (char *) ft_calloc(l + 1, sizeof(char));
	lseek(this->fd, start, SEEK_SET);
	read(this->fd, tkn_value, l);
	lexer_tokens_append(this, token__init__("STRING", this->__line_pos, this->__line, tkn_value));
}


Token_lst *lexer_get_next_token(Lexer *lex)
{
	Token_lst *token = NULL;
	if (lex->__pos == 0)
		lexer_pop_char(lex);
	while (lexer_peek_char(lex))
	{
		if (lexer_peek_char(lex) == '"')
			lexer_string(lex);
		else if (lexer_isidentifier(lex))
			lexer_identifier(lex);
		else if (lexer_isconstant(lex))
			lexer_constant(lex);
		else if (lexer_peek_char(lex) == '\'')
			lexer_char_constant(lex);
		else if (lexer_peek_char(lex) == '#')
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
			return (NULL);
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

void	lexer_print_tokens(Lexer *lex)
{
	if (lex->tokens)
}