/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadue <amenadue@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 00:14:03 by amenadue          #+#    #+#             */
/*   Updated: 2022/07/24 17:25:37 by amenadue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "norminette.h"

typedef struct s_args
{
	lst		*files;
	int		debug;
	int		o;
	char 	*cfile;
	char 	*hfile;
	char 	*filename;
} norm_argc;

norm_argc *parse_args(int c, char **v)
{
	norm_argc *args = (norm_argc *) ft_calloc(1, sizeof(norm_argc));
	int	i = 1;
	int	j;

	args->files = NULL;
	while (i < c)
	{
		if (!ft_strncmp(v[i], "-", 1))
		{
			if (ft_strncmp(v[i], "--", 2))
			{
				j = 1;
				while (v[i][j])
				{
					if (v[i][j] == 'v')
					{
						print_version();
						exit(0);
					}
					else if (v[i][j] == 'h')
					{
						print_help();
						exit(0);
					}
					else if (v[i][j] == 'd')
						args->debug++;
					else if (v[i][j] == 'o')
						args->o = 1;
					else
					{
						print_usage();
						ft_printf("norminette: error: unrecognized arguments: %s\n", v[i]);
						exit(2);
					}
					
					j++;
				}
			}
			else
			{
				if (!ft_strncmp(v[i], "--version", 10))
				{
					print_version();
					exit(0);
				}
				else if (!ft_strncmp(v[i], "--help", 10))
				{
					print_help();
					exit(0);
				}
				else if (!ft_strncmp(v[i], "--only-filename", 16))
					args->o = 1;
				else if (!ft_strncmp(v[i], "--cfile", 8))
				{
					if (++i >= c)
					{
						print_usage();
						ft_printf("norminette: error: argument --cfile: expected one argument\n");
						exit(2);
					}
					args->cfile = v[i];
				}
				else if (!ft_strncmp(v[i], "--hfile", 8))
				{
					if (++i >= c)
					{
						print_usage();
						ft_printf("norminette: error: argument --hfile: expected one argument\n");
						exit(2);
					}
					args->hfile = v[i];
				}
				else if (!ft_strncmp(v[i], "--filename", 11))
				{
					if (++i >= c)
					{
						print_usage();
						ft_printf("norminette: error: argument --filename: expected one argument\n");
						exit(2);
					}
					args->filename = v[i];
				}
				else
				{
					print_usage();
					ft_printf("norminette: error: unrecognized arguments: %s\n", v[i]);
					exit(2);
				}
			}
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
	
	lst *targets = NULL;
	int	has_err = 0;
	int content = -1;

	debug = args->debug;
	if (args->cfile || args->hfile)
	{
		if (args->filename)
			targets = new_lstitem(args->filename);
		else if (args->cfile)
		{
			targets = new_lstitem("file.c");
			if (!ft_strncmp(args->cfile+ft_strlen(args->cfile)-2, ".c", 3))
				content = open(args->cfile, O_RDONLY);
			else
				content = store_tmpfile(args->cfile);
		}
		else
		{
			targets = new_lstitem("file.h");
			if (!ft_strncmp(args->hfile+ft_strlen(args->hfile)-2, ".h", 3))
				content = open(args->hfile, O_RDONLY);
			else
				content = store_tmpfile(args->hfile);
		}
	}
	else
	{
		if (!args->files) //No specified files
		{
			targets = getfiles_recursive(".");
		}
		else
		{
			while (args->files) // foreach arg in arg.file
			{
				lst			*item = lst_shift(&(args->files));
				char		*arg = item->value;
				struct stat	fs;
				
				int file_noexist = stat(arg,&fs);
				if (file_noexist)
					ft_printf("'%s' no such file or directory\n", arg);
				else if ((fs.st_mode & S_IFMT) == S_IFDIR)
					lst_push(&targets, getfiles_recursive(arg));
				else if ((fs.st_mode & S_IFMT) == S_IFREG)
					lst_push(&targets, new_lstitem(ft_strdup(arg)));
			}
		}
	}

	while (targets) // foreach target in targets
	{
		lst *targetitem = lst_shift(&targets);
		char *target = targetitem->value;
		char *file_end = target + (ft_strlen(target) - 2);

		if (ft_strncmp(file_end, ".c", 3) && ft_strncmp(file_end, ".h", 3))
			ft_printf("Error: %s is not valid C or C header file\n", target);
		else
		{
			int source = content;
			if (source < 0)
			{
				source = open(target, O_RDONLY);
				if (source < 0)
				{
					ft_printf("Error: File could not be read: \"source = %d\" errno(%d)\n", source, errno);
					exit(0);
				}
			}
			Lexer *lexer = lexer__init__(source);
			Token_lst *tokens = lexer_get_tokens(lexer);
			close(source);
		}
	}
	return (has_err > 0);
}