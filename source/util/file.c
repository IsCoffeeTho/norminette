/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadue <amenadue@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 01:18:55 by amenadue          #+#    #+#             */
/*   Updated: 2022/08/30 13:06:14 by amenadue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../norminette.h"
#include <stdio.h>
#include <unistd.h>

# define TMPFILE_NAME__ "/tmp/norminette"

int store_tmpfile(char *content)
{
	remove(TMPFILE_NAME__);
	int fd = open(TMPFILE_NAME__, O_RDWR | O_CREAT);
	chmod(TMPFILE_NAME__, S_IRWXU|S_IRWXO|S_IRWXG);
	if (fd >= 0)
		write(fd, content, ft_strlen(content));
	else
	{
		ft_printf("Error: there was a problem writing to temporary file.\n");
		exit(1);
	}
	return (fd);
}

lst *getfiles_recursive(char *path)
{
	lst *root = NULL;
	DIR *directory;
	struct dirent *dir;
	
	if (!path)
		return (NULL);
	path = ft_strdup(path);
	if (path[ft_strlen(path)-1] == '/')
		path[ft_strlen(path)-1] = '\0';
	directory = opendir(path);
	if (!directory)
	{
		free(path);
		return (NULL);
	}
	while ((dir = readdir(directory)) != NULL)
	{
		char *file = dir->d_name;
		char *file_end = file + ft_strlen(file) - 2;
		if (ft_strncmp(file, ".", 1))
		{
			if (ft_strncmp(path, ".", 1))
			{
				file = ft_strjoin("/", file);
				file = ft_strjoin(path, file);
			}
			if (dir->d_type == DT_DIR)
				lst_push(&root, getfiles_recursive(file));
			else if (dir->d_type == DT_REG)
				if (!(ft_strncmp(file_end, ".c", 3) && ft_strncmp(file_end, ".h", 3)))
					lst_push(&root, new_lstitem(file));
		}
    }
    closedir(directory);
	return (root);
}