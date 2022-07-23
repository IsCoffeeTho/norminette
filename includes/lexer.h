#ifndef LEXER_H
# define LEXER_H


#include "libft.h"

typedef struct s_token_lst
{
	char *type;
	unsigned int pos[2];
	char *value;
	unsigned int length;
	struct s_token_lst	*next;
} Token_lst;

typedef struct s_lexer
{
	int			fd;
	long		size;
	char		__char;
	long		__pos;
	int			__line_pos;
	long		__line;
	Token_lst	*tokens;
	Token_lst	*last_tok;
}	Lexer;

Token_lst *token__init__(char *type, int *pos, char* value);
Lexer *lexer__init__(int fd);


#endif