/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadue <amenadue@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:03:42 by amenadue          #+#    #+#             */
/*   Updated: 2022/09/02 17:19:07 by amenadue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "dictionary.h"

const char	*keywords[36] = {
	"auto",
	"break",
	"case",
	"char",
	"const",
	"continue",
	"default",
	"do",
	"double",
	"else",
	"enum",
	"extern",
	"float",
	"for",
	"goto",
	"if",
	"int",
	"long",
	"register",
	"return",
	"short",
	"signed",
	"sizeof",
	"static",
	"struct",
	"switch",
	"typedef",
	"union",
	"unsigned",
	"void",
	"volatile",
	"while",
	"inline",
	"NULL",
	"restrict",
	NULL
};

const char	*preproc_keywords[14] = {
	"define",
	"error",
	"endif",
	"elif",
	"ifdef",
	"ifndef",
	"if",
	"else",
	"include",
	"pragma",
	"undef",
	"warning",
	"import",
	NULL
};

const char	*op_match[41] = {
	">>=",
	"<<=",
	"+=",
	"-=",
	"*=",
	"/=",
	"%=",
	"&=",
	"^=",
	"|=",
	"<=",
	">=",
	"==",
	"!=",
	"=",
	";",
	":",
	",",
	".",
	"!",
	"-",
	"+",
	"*",
	"/",
	"%",
	"<",
	">",
	"...",
	"++",
	"--",
	"->",
	"&&",
	"||",
	"^",
	"|",
	"~",
	"&",
	">>",
	"<<",
	"?",
	NULL
};

const char	*op_name[41] = {
	"RIGHT_ASSIGN",
	"LEFT_ASSIGN",
	"ADD_ASSIGN",
	"SUB_ASSIGN",
	"MUL_ASSIGN",
	"DIV_ASSIGN",
	"MOD_ASSIGN",
	"AND_ASSIGN",
	"XOR_ASSIGN",
	"OR_ASSIGN",
	"LESS_OR_EQUAL",
	"GREATER_OR_EQUAL",
	"EQUALS",
	"NOT_EQUALS",
	"ASSIGN",
	"SEMI_COLON",
	"COLON",
	"COMMA",
	"DOT",
	"NOT",
	"MINUS",
	"PLUS",
	"MULT",
	"DIV",
	"MODULO",
	"LESS_THAN",
	"MORE_THAN",
	"ELLIPSIS",
	"INC",
	"DEC",
	"PTR",
	"AND",
	"OR",
	"BWISE_XOR",
	"BWISE_OR",
	"BWISE_NOT",
	"BWISE_AND",
	"RIGHT_SHIFT",
	"LEFT_SHIFT",
	"TERN_CONDITION",
	NULL
};

char	*toUppercase(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] += ' ';
	}
	return (str);
}

int		dict_is_in_keywords(char *tkn_value)
{
	int 	i;
	size_t	len;

	i = 0;
	len = ft_strlen(tkn_value) + 1;
	while (keywords[i])
	{
		if (!ft_strncmp(keywords[i], tkn_value, len))
			return (i);
		i++;
	}
	return (-1);
}

/**  */
char	*dict_keyword(char *tkn_value)
{
	int	index;

	index = dict_is_in_keywords(tkn_value);
	if (index >= 0)
		return (toUppercase(ft_strdup(keywords[index])));
	else
		return (toUppercase(tkn_value));
}

char	*dict_operator(char *tkn_value)
{
	int 	i;
	size_t	len;

	i = 0;
	len = ft_strlen(tkn_value) + 1;
	while (op_match[i])
	{
		if (!ft_strncmp(op_match[i], tkn_value, len))
			return (ft_strdup(op_name[i]));
		i++;
	}
	return (NULL);
}