/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadue <amenadue@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 01:02:05 by amenadue          #+#    #+#             */
/*   Updated: 2022/07/24 20:18:47 by amenadue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTIONS_H
# define EXCEPTIONS_H

typedef struct py_exception
{
	char *name;
	char *message;
} exception;

exception *Exception(char *name, char* message);

#endif