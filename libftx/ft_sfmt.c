/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sfmt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadue <amenadue@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 17:55:40 by amenadue          #+#    #+#             */
/*   Updated: 2022/07/29 07:09:28 by amenadue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libftx.h"

int	count_added(char *fmt)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!fmt)
		return (0);
	while (fmt[i])
	{
		if (fmt[i++] == '%')
			if (fmt[i++] != '%')
				j++;
	}
	return (j);
}

char *_appendto_lbuf(char *buf, char* app)
{	
	size_t	buf_len;
	size_t	app_len;
	size_t	i;

	if (!buf || !app)
		return (NULL);
	buf_len = ft_strlen(buf);
	app_len = ft_strlen(app);
	buf = (char *) realloc(buf, buf_len + app_len + 1);
	if (!buf)
		return (NULL);
	i = 0;
	while (app[i])
	{
		buf[buf_len + i] = app[i];
	}
	buf[buf_len + i] = '\0';
	return (buf);
}

char	*ft_sfmt(char const *_fmt, ...)
{
	va_list	varg;
	char	*buffer;
	int		i;
	int		j;

	if (!_fmt)
		return (NULL);
	buffer = ft_calloc(ft_strlen(_fmt+1), sizeof(char));
	va_start(varg, _fmt);
	i = 0;
	j = 0;
	while (_fmt[i])
	{
		if (_fmt[i] == '%')
			i++;
		else
			buffer[j] = _fmt[i];
		i++;
	}
	return (buffer);
}