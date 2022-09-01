/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadue <amenadue@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 09:57:09 by amenadue          #+#    #+#             */
/*   Updated: 2022/09/01 15:16:16 by amenadue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../norminette.h"

#define NORM_tabsize 4

/**
 * Stores an error in a globally accessed global variable
 */
void	TokenError(Lexer *this)
{
	char *str = ft_strjoin("Error: Unrecognized token line ", ft_itoa(this->__line));
	char *tmp = str;
	str = ft_strjoin(str, ", col ");
	free(tmp);
	tmp = str;
	str = ft_strjoin(str, ft_itoa(this->__line_pos));
	free(tmp);
	norm_err = Exception("TokenError", str);
}

/** Creates a Lexer struct, acts as a constructor for the Lexer object
 * 	in the original repo in python.
 * @param fd File descriptor of file being looked for parsing
*/
Lexer	*lexer__init__(int fd)
{
	Lexer *this = (Lexer *) ft_calloc(1, sizeof(Lexer));
	this->fd = fd;
	this->size = lseek(fd, 0, SEEK_END);
	this->__char = '\0';
	this->__pos = 0;
	this->__line_pos = 1;
	this->__line = 1;
	this->tokens = NULL;
	lseek(fd, 0, SEEK_SET);
	return (this);
}

/** Returns at an amount of character in Lexer struct from at the point of position
 * 
 *	WARNING:
 *	This function is prone to messing with the execution of parsing
 * 	please pop each token by hand and handle each token one by one.
*/
char	*lexer_peek_char_substring(Lexer *this, int size)
{
	size_t	curr_pos = this->__pos;
	size_t	curr_line_pos = this->__line_pos;
	size_t	curr_line = this->__line;
	char 	*str = (char *) ft_calloc(size+1, sizeof(char));
	int		i = 0;

	while (i < size)
		str[i] = lexer_pop_char(this);
	lseek(this->fd, curr_pos-1, SEEK_SET);
	lexer_pop_char(this);
	this->__pos = curr_pos;
	this->__line_pos = curr_line_pos;
	this->__line = curr_line;
	return (str);
}

/** Returns the character being looked at from a Lexer struct */
#define	lexer_peek_char(lex) lex->__char

/** Moves a Lexer struct along its file descriptor and returns the char found */
char	lexer_pop_char(Lexer *this)
{
	char _c;
	this->__char = '\0';
	this->__pos += read(this->fd, &_c, 1);
	if (this->__pos < this->size)
	{
		this->__char = _c;
	}

	if (this->__char == '\n')
	{
		this->__line_pos = 1;
		this->__line++;
	}
	else if (this->__char == '\t')
		this->__line_pos += NORM_tabsize - (this->__line_pos % NORM_tabsize);
	else
		this->__line_pos++;
	return (this->__char);
}

/** Returns the last token parsed in a Lexer struct */
#define	lexer_peek_token(this) this->last_tok

/** Returns if the Lexer struct is looking at a string definition */
#define lexer_is_string(this) lexer_peek_char(this) == '"'

/** Returns if the Lexer struct is looking at a number constant */
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

/** Returns if the Lexer struct is looking at a char constant */
#define lexer_is_char_constant(this) lexer_peek_char(this) == '\''

/** Returns if the Lexer struct is looking at a comment
 *	Either:
 *	- Multiline; or
 *	- Singleline
*/
int	lexer_is_comment(Lexer *this)
{
	size_t	curr_pos = this->__pos;
	size_t	curr_line_pos = this->__line_pos;
	size_t	curr_line = this->__line;

	if (lexer_peek_char(this) == '/')
	{
		char nxt = lexer_pop_char(this);
		
		lseek(this->fd, curr_pos-1, SEEK_SET);
		lexer_pop_char(this);
		this->__pos = curr_pos;
		this->__line_pos = curr_line_pos;
		this->__line = curr_line;
		
		if (nxt == '/' || nxt == '*')
			return (1);
	}
	return (0);
}

/** Returns if the Lexer struct is looking at an identifier */
int	lexer_is_identifier(Lexer *this)
{
	if ((lexer_peek_char(this) >= 'A' && lexer_peek_char(this) <= 'Z')
	 || (lexer_peek_char(this) >= 'a' && lexer_peek_char(this) <= 'z')
	 || lexer_peek_char(this) == '_')
		return (1);
	return (0);
}

/** Parse a String Definition in a Lexer struct */
void	lexer_string(Lexer *this)
{
	size_t	start;
	size_t	l = 0;
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
		if (lexer_peek_char(this) == '\\' && lexer_pop_char(this) == '"')
			break;
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

/** Parse a Char Constant in a Lexer struct
 * Example:
 * 's' = ascii s or 0x37 or (int)115
*/
void	lexer_char_constant(Lexer *this)
{
	char	*tkn_value = ft_strdup("''''");
	
	lexer_pop_char(this);
	if (lexer_peek_char(this) == '\\')
	{
		tkn_value[1] = '\\';
		tkn_value[2] = lexer_pop_char(this);
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

/** Parse a Number Constant in a Lexer struct
 * 
 * Different Execution style from original python repo
 * due to efficiency in C.
*/
void	lexer_constant(Lexer *this)
{
	char	*tkn_value;
	size_t	start = this->__pos;
	size_t	l = 0;
	char	negative_flag = 0;

	if (lexer_peek_char(this) == '-')
		negative_flag = 1;

	if (lexer_peek_char(this) == '+' || lexer_peek_char(this) == '-')
	{
		l++;
		lexer_pop_char(this);
	}

	if (lexer_peek_char(this) == '0')
	{
		l++;
		if (lexer_pop_char(this) == 'b' || lexer_peek_char(this) == 'B')
		{
			l++;
			while (lexer_pop_char(this) == '0' || lexer_peek_char(this) == '1')
				l++;
		}
		else if (lexer_peek_char(this) == 'x' || lexer_peek_char(this) == 'X')
		{
			l++;
			while ((lexer_pop_char(this) >= '0' && lexer_peek_char(this) <= '9')
				|| (lexer_peek_char(this) >= 'a' && lexer_peek_char(this) <= 'a')
				|| (lexer_peek_char(this) >= 'A' && lexer_peek_char(this) <= 'F'))
				l++;
		}
		else if (lexer_peek_char(this) >= '0' && lexer_peek_char(this) <= '7')
		{
			l++;
			while (lexer_pop_char(this) >= '0' && lexer_peek_char(this) <= '7')
				l++;
		}
		else
		{
			TokenError(this);
			return ;
		}
	}
	else if ((lexer_peek_char(this) >= '0' && lexer_peek_char(this) <= '9') || lexer_peek_char(this) == '.')
	{
		l++;
		if (lexer_peek_char(this) != '.')
		{
			while (lexer_pop_char(this) >= '0' && lexer_peek_char(this) <= '9')
				l++;
		}
		if (lexer_peek_char(this) == '.')
		{
			if (lexer_pop_char(this) >= '0' && lexer_peek_char(this) <= '9')
			{
				l++;
				while (lexer_pop_char(this) >= '0' && lexer_peek_char(this) <= '9')
					l++;
			}
			else
			{
				TokenError(this);
				return ;
			}
		}
		if (lexer_peek_char(this) == 'e' || lexer_peek_char(this) == 'E')
		{
			l++;
			if (lexer_pop_char(this) == '+' || lexer_peek_char(this) == '-')
				l++;
			while (lexer_peek_char(this) >= '0' && lexer_peek_char(this) <= '9')
			{
				l++;
				lexer_pop_char(this);
			}
		}
		else
		{
			TokenError(this);
			return ;
		}
	}

	if (lexer_peek_char(this) == 'u' || lexer_peek_char(this) == 'U')
	{
		if (negative_flag)
		{
			TokenError(this);
			return ;
		}
		l++;
		lexer_pop_char(this);
	}
	if (lexer_peek_char(this) == 'l' || lexer_peek_char(this) == 'L')
	{
		l++;
		if (lexer_pop_char(this) == 'l' || lexer_peek_char(this) == 'L')
		{
			l++;
			lexer_pop_char(this);
		}
	}

	tkn_value = (char *) ft_calloc(l + 1, sizeof(char));
	lseek(this->fd, start, SEEK_SET);
	read(this->fd, tkn_value, l);
	lexer_tokens_append(this, token__init__("CONSTANT", this->__line_pos, this->__line, tkn_value));
}
#undef usedNeg

/** Parse a Number Constant in a Lexer struct */
void	lexer_comment(Lexer *this)
{
	char	*tkn_value;
	size_t	start = this->__pos;
	size_t	l = 0;
	
	if (lexer_peek_char(this) == '/')
	{
		l++;
		if (lexer_pop_char(this) == '/')
		{
			l++;
			while (lexer_pop_char(this))
			{
				if (lexer_peek_char(this) == '\n')
				{
					tkn_value = (char *) ft_calloc(l + 1, sizeof(char));
					lseek(this->fd, start, SEEK_SET);
					read(this->fd, tkn_value, l);
					lexer_tokens_append(this, token__init__("COMMENT", this->__line_pos, this->__line, tkn_value));
					return ;
				}
				l++;
			}
		}
		else if (lexer_peek_char(this) == '*')
		{
			l++;
			while (lexer_pop_char(this))
			{
				l++;
				if (lexer_peek_char(this) == '*')
				{
					l++;
					if (lexer_pop_char(this) == '/')
					{
						tkn_value = (char *) ft_calloc(l + 1, sizeof(char));
						lseek(this->fd, start, SEEK_SET);
						read(this->fd, tkn_value, l);
						lexer_tokens_append(this, token__init__("MULT_COMMENT", this->__line_pos, this->__line, tkn_value));
						return ;
					}
				}
			}
		}
		else
		{
			TokenError(this);
			return ;
		}
	}
	else
		TokenError(this);
}

/** Parse an Identifier in a Lexer struct 
 * 
 * MY NEED A REWORK
*/
void	lexer_identifier(Lexer *this)
{
	char	*tkn_value;
	size_t	start = this->__pos;
	size_t	l = 0;

	while (lexer_is_identifier(this) || (lexer_peek_char(this) >= '0' && lexer_peek_char(this) <= '9'))
	{
		if (lexer_pop_char(this) == '\\')
		{
			if (lexer_pop_char(this) == '\n')
				lexer_pop_char(this);
			l++;
		}
		l++;
		lexer_pop_char(this);
	}
	
	tkn_value = (char *) ft_calloc(l + 1, sizeof(char));
	lseek(this->fd, start, SEEK_SET);
	read(this->fd, tkn_value, l);
	if (dict_is_in_keywords(tkn_value))
		lexer_tokens_append(this, token__init__(dict_keyword(tkn_value), this->__line_pos, this->__line, NULL));
	else
		lexer_tokens_append(this, token__init__("IDENTIFIER", this->__line_pos, this->__line, tkn_value));
}

/** Parse an Operator in a Lexer struct */
void	lexer_operator(Lexer *this)
{
	char	*tkn_value;
	size_t	start = this->__pos;
	size_t	l = 0;
	
	tkn_value = (char *) ft_calloc(l + 1, sizeof(char));
	lseek(this->fd, start, SEEK_SET);
	read(this->fd, tkn_value, l);
	lexer_tokens_append(this, token__init__(dict_operator(tkn_value), this->__line_pos, this->__line, NULL));
	
}

/** Parse the next token in a Lexer struct */
Token_lst	*lexer_get_next_token(Lexer *this)
{
	Token_lst	*token = NULL;

	if (this->__pos == 0)
		lexer_pop_char(this);
	while (lexer_peek_char(this))
	{
		if (norm_err)
			return (NULL);

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
		else if (lexer_is_comment(this))
			lexer_comment(this);
		else if (lexer_is_op(this))
			lexer_operator(this);
		else if (lexer_is_ws(this))
			lexer_ws(this);
		else if (lexer_is_brackets(this))
			lexer_bracket(this);
		else
		{
			TokenError(this);
			return (NULL);
		}
	}
	return (token);
}

/** Parses the file supplied in a Lexer struct and provides
 *  a linked list of tokens in the file. */
Token_lst	*lexer_get_tokens(Lexer *this)
{
	while (lexer_get_next_token(this))
		continue;
	return (this->tokens);
}

/**	Prints the list of Parsed Tokens inside a Lexer struct
 *	
 *	@returns <'TYPE'='value'>; or
 *	<'TYPE'>
 */
void	lexer_print_tokens(Lexer *this)
{
	Token_lst	*last = this->tokens;

	while (last)
	{
		ft_printf("%s\n", token_tostr(last));
		if (last->next)
			last = last->next;
		else
			break;
	}
}