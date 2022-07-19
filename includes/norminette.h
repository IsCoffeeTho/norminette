#ifndef NORMINETTE_H
# define NORMINETTE_H

# define __version__ "3.3.51"
# define __name__ "norminette"
# define __og_author__ "42"
# define __og_author__email__ "pedago@42.fr"
# define __new_author__ "amenadue"
# define __new_author__email__ "amenadue@student.42adel.org.au"

# include "lexer.h"
# include "exceptions.h"
# include "context.h"

typedef struct s_lst
{
	char *value;
	struct s_lst *next;
} lst;

lst	*new_lstitem(char *value);
void lst_push(lst **list, lst *item);
lst	*lst_pop(lst **list);
void lst_unshift(lst **list, lst *item);
lst	*lst_shift(lst **list);

#endif