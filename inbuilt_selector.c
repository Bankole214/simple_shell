#include "main.h"
/**
 * inb_functs - checks for an inbuilt function
 * @name: name of function to check for
 * Return: function if found else NULL
*/
int (*inb_functs(char *name))(char **, size_t, var_list *, char *)
{
	int i = 0;
	inbuilt inbuilt_fcs[] = {
		{"env", env},
		{"exit", __exit},
		{"setenv", __setenv},
		{"unsetenv", __unsetenv},
		{"cd", cd},
		{NULL, NULL}
	};

	for (i = 0 ; inbuilt_fcs[i].name; i++)
	{
		if (_strcmp(name, inbuilt_fcs[i].name) == 0)
		{
			return (inbuilt_fcs[i].f);
		}
	}
	return (NULL);
}
