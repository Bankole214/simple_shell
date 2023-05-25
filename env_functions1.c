#include "main.h"
/**
 * var_list2vector - makes a vector from an environment linled list
 * @head: pointer to head
 * Return: pointer to array or null
*/
char **var_list2vector(var_list **head)
{
	char **env;
	var_list *h = *head;
	size_t l = var_list_len(head);
	int i = 0;

	if (!h)
		return (NULL);
	if (!l)
		return (NULL);
	env = malloc(sizeof(char *) * (l + 1));
	if (!env)
		return (NULL);
	env[l] = NULL;
	while (h)
	{
		env[i] = _strdup(h->var);
		if (!env[i])
		{
			i--;
			while (i >= 0)
				free(env[i--]);
			free(env);
			return (NULL);
		}
		i++;
		h = h->next;
	}
	return (env);
}
/**
 * get_var__index - returns the index of a variable in a linked list.
 * @h: address of head pointer
 * @name: name of variable
 * Return: index or -1 if failure
*/

int get_var__index(var_list **h, const char *name)
{
	unsigned int i = 0, l = _strlen(name), pref_len;
	char *name_w_eq;
	var_list *head = *h;

	if (!head)
		return (-1);
	name_w_eq = malloc(sizeof(char) * (l + 2));
	if (!name_w_eq)
		return (-1);
	name_w_eq = _strcpy(name_w_eq, name);
	name_w_eq = _strcat(name_w_eq, "=");
	pref_len = _strlen(name_w_eq);
	for (; head ; i++)
	{
		if (_strncmp(head->var, name_w_eq, pref_len) == 0)
		{
			free(name_w_eq);
			return (i);
		}
		head = head->next;
	}
	free(name_w_eq);
	return (-1);
}
/**
 * overwrite_env_index - overwrites a variable using index
 * @head: address of head pointer of variable
 * @index: index of variable
 * @variable: new variable key
 * Return: 1 success, 0 fail
*/
int overwrite_env_index(var_list **head, int index, char *variable)
{
	int i = 0;
	var_list *h = *head;

	while (h)
	{
		if (i == index)
		{
			free(h->var);
			h->var = _strdup(variable);
			if (!h->var)
				return (0);
			return (1);
		}
		i++;
		h = h->next;
	}
	return (0);
}
/**
 * del_var_at_index - deletes the variable at
 * index of var_list linked list.
 * @head: pointer to head pointer
 * @index: index
 * Return: 1 if it succeeded, -1 if it failed
*/

int del_var_at_index(var_list **head, unsigned int index)
{
	var_list *prior, *h, *next;
	unsigned int i;

	if (!head || !*head)
		return (-1);
	h = *head;
	if (index == 0)
	{
		next = h->next;
		free(h->var);
		free(h);
		*head = next;
		return (1);
	}
	for (i = 0; i < index && h; i++)
	{
		prior = h;
		h = h->next;
	}
	if (i < index)
		return (-1);
	if (!h)
		return (-1);
	prior->next = h->next;
	free(h->var);
	free(h);
	return (1);
}
