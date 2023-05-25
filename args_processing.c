#include "main.h"
/**
 * prc_cmnts - checks for comment and removes it from execution
 * @av: arguement vector
 * Return: processed vector
*/
char **prc_cmnts(char **av)
{
	int i, j = 0;
	char **av2;

	if (!av)
		return (NULL);
	for (i = 0 ; av[i]; i++)
	{
		if (_strncmp(av[i], "#", 1) == 0)
		{
			j = i;
			break;
		}
	}
	if (j)
	{
		av2 = malloc(sizeof(char *) * (j + 1));
		if (!av2)
			return (NULL);
		av2[j] = NULL;
		for (i = 0 ; i < j ; i++)
			av2[i] = _strdup(av[i]);
		v_free(av);
		return (av2);
	}
	return (av);
}
/**
 * reset_vec - rearranges a vector if it constains null inbetween
 * @av: vector to reset
 * @old_c: old length
 * @new_c: new length
 * Return: new vector, or null if it fails
*/
char **reset_vec(char **av, int old_c, int new_c)
{
	char **new = malloc(sizeof(char *) * (new_c + 1));
	int i, j;

	if (!new)
	{
		for (i = 0 ; i < old_c ; i++)
		{
			if (av[i])
			free(av[i]);
		}
		free(av);
		return (NULL);
	}
	new[new_c] = NULL;
	for (i = 0, j = 0 ; i < old_c;)
	{
		if (av[i] == NULL)
		{
			i++;
			continue;
		}
		new[j] = _strdup(av[i]);
		free(av[i]);
		i++;
		j++;
	}
	free(av);
	return (new);
}
/**
 * sh_rep - does variable replacements
 * @av: vector;
 * @p_st: last exit status
 * @head: head of environment list
 * Return: processed vector or NULL on failure
*/
char **sh_rep(char **av, size_t *p_st, var_list *head)
{
	int i, c = v_count(av), fail = 0;
	char **sv, *var, *res;

	if (!av)
		return (NULL);
	for (i = 0 ; av[i] ; i++)
	if (_strcmp(av[i], "$$") == 0)
	{
		free(av[i]);
		av[i] = num2str(getpid());
	}
	else
		if (_strcmp(av[i], "$?") == 0)
		{
			free(av[i]);
			av[i] = num2str(*p_st);
		}
		else
			if (_strncmp(av[i], "$", 1) == 0)
			{
				sv = strsplt(av[i], "$");
				free(av[i]);
				var = _strdup(sv[0]);
				v_free(sv);
				res = _getenv(&head, var);
				free(var);
				if (!res)
				{
					av[i] = NULL;
					fail++;
					continue;
				}
				av[i] = res;
			}
	if (fail)
		return (reset_vec(av, c, c - fail));
	return (av);
}
/**
 * procs - process arguements before execution
 * @av: vector;
 * @p_st: last exit status
 * @head: head of environment list
 * Return: processed vector or NULL on failure
*/
char **procs(char **av, size_t *p_st, var_list *head)
{
	if (!av)
		return (NULL);
	return (sh_rep(prc_cmnts(av), p_st, head));
}
