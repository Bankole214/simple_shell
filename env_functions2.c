#include "main.h"
/**
 * _setenv - adds a new key value pair to environments, or update if existing
 * @name: key
 * @value: value
 * @overwrite: integer to determin if to overwrite if found
 * @env_list: head pointer of environment
 * Return: 0 success, -1 error
*/
int _setenv(const char *name, const char *value, int overwrite,
var_list *env_list)
{
	int index, name_len, value_len;
	char *variable;

	name_len = _strlen(name);
	value_len = _strlen(value);
	index = get_var__index(&env_list, name);
	variable = malloc(sizeof(char) * (name_len + value_len + 2));
	/*allowance of ' '*/
	if (!variable)
		return (-1);
	variable = _strcpy(variable, name);
	variable = _strcat(variable, "=");
	variable = _strcat(variable, value);
	if (index < 0)
		add_var_end(&env_list, variable);
	else
		if (overwrite != 0)
			if (overwrite_env_index(&env_list, index, variable) == 0)
			{
				free(variable);
				return (-1);
			}
	free(variable);
	return (0);
}

/**
 * _unsetenv - deletes key value pair to environments
 * @name: key
 * @env_list: head pointer of environment
 * Return: 0 success, -1 error
*/
int _unsetenv(const char *name, var_list *env_list)
{
	int index = get_var__index(&env_list, name);

	if (index >= 0)
		if (del_var_at_index(&env_list, index) == -1)
			return (-1);
	return (0);
}
