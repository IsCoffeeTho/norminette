/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadue <amenadue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 19:47:05 by amenadue          #+#    #+#             */
/*   Updated: 2022/08/23 14:53:27 by amenadue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

typedef struct s_token_lst
{
	char *type;
	size_t linepos;
	size_t line;
	char *value;
	unsigned int length;
	struct s_token_lst	*next;
}	Token_lst;

typedef struct s_lexer
{
	int			fd;
	size_t		size;
	char		__char;
	size_t		__pos;
	size_t		__line_pos;
	size_t		__line;
	Token_lst	*tokens;
	Token_lst	*last_tok;
	int			__slashed : 1;
}	Lexer;

Token_lst	*token__init__(char *type, size_t linepos, size_t line, char* value);
char		*token_tostr(Token_lst *token);

Lexer		*lexer__init__(int fd);
char		lexer_pop_char(Lexer *this);
void		lexer_tokens_append(Lexer *lex, Token_lst *tok);

Token_lst	*lexer_get_next_token(Lexer *lex);
Token_lst	*lexer_get_tokens(Lexer *lex);
void		lexer_print_tokens(Lexer *lex);


#endif