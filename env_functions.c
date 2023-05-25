#include "main.h"
/**
 * _getenv - returns the value of an environment variable
 * @env_list: environment linked list
 * @name: environment variable name
 * Return: value of environment variable. it should be freed
*/
char *_getenv(var_list **env_list, const char *name)
{
	int l = _strlen(name), pref_len;
	/* name with equal sign*/
	char **splitted = NULL, *variable, *found = NULL, *name_w_eq;
	var_list *h = *env_list;

	name_w_eq = malloc(sizeof(char) * (l + 2));
	if (!name_w_eq)
		return (NULL);
	/*copy strings over with _strcat function*/
	name_w_eq = _strcpy(name_w_eq, name);
	name_w_eq = _strcat(name_w_eq, "=");
	pref_len = _strlen(name_w_eq);
	for (; h ; h = h->next)
	{
		if (_strncmp(h->var, name_w_eq, pref_len) == 0)
			found = _strdup(h->var);
	}
	free(name_w_eq);
	splitted = strsplt(found, "=");
	if (!splitted)
	{
		if (found)
			free(found);
		return (NULL);
	}
	variable = _strdup(splitted[1]);
	if (!variable)
	{
		v_free(splitted);
		free(found);
		return (NULL);
	}
	v_free(splitted);
	free(found);
	return (variable);
}
/**
 * add_var_end - adds a new node at the end of a list_t list.
 * @head: address of head of node
 * @str: string part of element
 * Return: pointer to new head
*/
var_list *add_var_end(var_list **head, const char *str)
{
	var_list *new, *end, *h;

	if (!head)
		return (NULL);
	new = malloc(sizeof(var_list));
	if (!new)
		return (NULL);
	new->var = _strdup(str);
	new->next = NULL;
	if (!new->var)
	{
		free(new);
		return (NULL);
	}
	if (!(*head))
	{
		*head = new;
		return (new);
	}
	h = *head;
	while (h)
	{
		if (h->next == NULL)
			end = h;
		h = h->next;
	}
	end->next = new;
	return (new);
}
/**
 * build_env_list - builds environment variable linkedlist
 * @head: address of pointer to head
 * @env: environment vector
 * Return: pointer to head or NULL;
*/
var_list *build_env_list(var_list **head, char **env)
{
	int i;

	if (!env)
		return (NULL);
	if (!head)
		return (NULL);
	for (i = 0 ; env[i] ; i++)
	{
		add_var_end(head, env[i]);
	}
	return (*head);
}
/**
 * free_envlist - frees a list_t list.
 * @head: list head
*/

void free_envlist(var_list *head)
{
	var_list *next;

	while (head)
	{
		next = head->next;
		free(head->var);
		free(head);
		head = next;
	}
}
/**
 * var_list_len - returns the number of elements in a linked listint_t list.
 * @h: list head
 * Return: size of list
*/
size_t var_list_len(var_list **h)
{
	size_t n = 0;
	var_list *head = *h;

	while (head)
	{
		n++;
		head = head->next;
	}
	return (n);
}
