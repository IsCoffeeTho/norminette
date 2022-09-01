/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadue <amenadue@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 00:30:52 by amenadue          #+#    #+#             */
/*   Updated: 2022/09/01 15:28:21 by amenadue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICTIONARY_H
# define DICTIONARY_H

# include "../norminette.h"

int		dict_is_in_keywords(char *tkn_value);
char	*dict_keyword(char *tkn_value);

char	*dict_operator(char *tkn_value);

#endif