#ifndef PY_LAYER_H
# define PY_LAYER_H

typedef struct py_exception
{
	char *name;
	char *msg;
	char *toString;
} exception;

#endif