/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadue <amenadue@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 00:14:03 by amenadue          #+#    #+#             */
/*   Updated: 2022/07/20 01:00:54 by amenadue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "norminette.h"

#define V_STR "%s %s\nAuthor: %s (%s)\nRemade: %s (%s)\n"

typedef struct s_args
{
	lst *files;
} norm_argc;

norm_argc *parse_args(int c, char **v)
{
	norm_argc *args = (norm_argc *) ft_calloc(1, sizeof(norm_argc));
	int	i = 1;

	args->files = NULL;
	while (i < c)
	{
		if (!ft_strncmp(v[i], "-v", 3) || !ft_strncmp(v[i], "-v", 3))
		{
			ft_printf(V_STR, __name__, __version__,
				__og_author__, __og_author__email__,
				__new_author__, __new_author__email__);
			exit(0);
		}
		else if (!ft_strncmp(v[i], "--cfile", 8))
		{
			ft_printf("cfile flag\n");
		}
		else
			lst_push(&(args->files), new_lstitem(v[i]));
		i++;
	}
	return (args);
}

int	main(int c, char **v)
{
	norm_argc *args = parse_args(c, v);
	lst *file = args->files;
	while (file)
	{
		ft_printf("%s\n", file->value);
		if (!file->next)
			break;
		file = file->next;
	}
	return (0);
}