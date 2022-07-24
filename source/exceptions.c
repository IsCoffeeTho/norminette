/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadue <amenadue@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 20:15:21 by amenadue          #+#    #+#             */
/*   Updated: 2022/07/24 20:16:51 by amenadue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "norminette.h"

exception *Exception(char *name, char* message)
{
	exception *ex = (exception *) ft_calloc(1, sizeof(exception));
	ex->name = name;
	ex->message = message;
}