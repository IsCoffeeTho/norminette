/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadue <amenadue@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 20:15:21 by amenadue          #+#    #+#             */
/*   Updated: 2022/07/29 07:32:30 by amenadue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "norminette.h"

exception *Exception(char *name, char* message)
{
	exception *ex = (exception *) ft_calloc(1, sizeof(exception));
	if (!ex)
		return (NULL);
	ex->name = name;
	ex->message = message;
	return (ex);
}