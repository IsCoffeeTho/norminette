/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadue <amenadue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 09:57:09 by amenadue          #+#    #+#             */
/*   Updated: 2022/08/23 14:57:17 by amenadue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "norminette.h"

#define NORM_tabsize 4

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

Lexer	*lexer__init__(int fd)
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

char	*lexer_peek_char_substring(Lexer *this, int size)
{
	size_t	curr_pos = this->__pos;
	size_t	curr_line_pos = this->__line_pos;
	size_t	curr_line = this->__line;
	char 	*str = (char *) ft_calloc(size+1, sizeof(char));
	int		i = 0;

	while (i < size)
		str[i] = lexer_pop_char(this);
	this->__pos = curr_pos;
	this->__line_pos = curr_line_pos;
	this->__line = curr_line;
	return (str);
}

#define	lexer_peek_char(lex) lex->__char

char	lexer_pop_char(Lexer *this)
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

#define	lexer_peek_token(this) this->last_tok

#define lexer_is_string(this) lexer_peek_char(this) == '"'

int	lexer_is_constant(Lexer *this)
{
	if (lexer_peek_char(this) >= '0' && lexer_peek_char(this) <= '9')
		return (1);
	else if (lexer_peek_char(this) == '.')
	{
		if (lexer_peek_char(this) >= '0' && lexer_peek_char(this) <= '9')
			return (1);
		else
			return (0);
	}
	return (0);
}

#define lexer_is_char_constant(this) lexer_peek_char(this) == '\''

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

void	lexer_char_constant(Lexer *this)
{
	char	*tkn_value = ft_strdup("''''");
	
	lexer_pop_char(this);
	if (this->__slashed)
	{
		tkn_value[1] = '\\';
		tkn_value[2] = lexer_peek_char(this);
	}
	else
	{
		tkn_value[1] = lexer_peek_char(this);
		tkn_value[3] = '\0';
	}
	lexer_pop_char(this);
	if (lexer_peek_char(this) != '\'')
	{
		TokenError(this);
		return ;
	}
	lexer_tokens_append(this, token__init__("CHAR_CONST", this->__line_pos, this->__line, tkn_value));
}

void	lexer_constant(Lexer *this)
{
	char	*tkn_value;
	char	*bucket = ft_strdup(".0123456789aAbBcCdDeEfFlLuUxX-+");
	while (0);
}

Token_lst	*lexer_get_next_token(Lexer *this)
{
	Token_lst	*token = NULL;

	if (this->__pos == 0)
		lexer_pop_char(this);
	while (lexer_peek_char(this))
	{
		if (lexer_is_string(this))
			lexer_string(this);
		else if (lexer_is_identifier(this))
			lexer_identifier(this);
		else if (lexer_is_constant(this))
			lexer_constant(this);
		else if (lexer_is_char_constant(this))
			lexer_char_constant(this);
		else if (lexer_peek_char(this) == '#')
			lexer_preprocessor(this);
		else if (lexer_iscomment(this)) // this will be for both single and multi line
			lexer_comment(this);
		else if (lexer_isop(this))
			lexer_operator(this);
		else if (lexer_isws(this))
			lexer_ws(this);
		else if (lexer_isbrackets(this))
			lexer_bracket(this);
		else
		{
			TokenError(this);
			return (NULL);
		}
	}
	return (token);
}

Token_lst	*lexer_get_tokens(Lexer *this)
{
	while (lexer_get_next_token(this))
		continue;
	return (this->tokens);
}

void	lexer_print_tokens(Lexer *this)
{
	//if (this->tokens)
}