/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadue <amenadue@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 03:07:41 by amenadue          #+#    #+#             */
/*   Updated: 2022/08/30 13:06:13 by amenadue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../norminette.h"

#define V_STR "%s %s\nAuthor: %s (%s)\nRemade: %s (%s)\n"

void	print_usage(void)
{
	ft_printf("usage: %s [-h] [-d] [-o] [-v] [--cfile CFILE] [--hfile HFILE] [--filename FILENAME] [-R R] [file [file ...]]\n", __name__);
}

void	print_help(void)
{
	print_usage();
	ft_printf("\npositional arguments:\n");
	ft_printf("  file                 File(s) or folder(s) you wanna run the parser on. If no file provided, runs on current folder.\n\n");
	ft_printf("optional arguments:\n");
	ft_printf("  -h, --help           Show this help message and exit\n");
	ft_printf("  -d, --debug          Debug output (multiple values available)\n");
	ft_printf("  -o, --only-filename  By default norminette displays the full path to the file, this allows to show only filename\n");
	ft_printf("  -v, --version        Show program's version number and exit\n");
	ft_printf("  --cfile CFILE        Store C file content directly instead of filename\n");
	ft_printf("  --hfile HFILE        Store header file content directly instead of filename\n");
	ft_printf("  --filename FILENAME  Stores filename if --cfile or --hfile is passed\n");
	ft_printf("  -R R                 Compatibility for norminette 2\n");
}

void	print_version(void)
{
	ft_printf(V_STR, __name__, __version__,
		__og_author__, __og_author__email__,
		__new_author__, __new_author__email__);
}