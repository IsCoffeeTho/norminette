/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenadue <amenadue@student.42adel.org.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 01:18:55 by amenadue          #+#    #+#             */
/*   Updated: 2022/07/23 02:08:10 by amenadue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "norminette.h"
#include <dirent.h>

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