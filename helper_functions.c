#include "main.h"
/**
 * frees - helperfree oldpwd and pwd
 * @n: number of argeuments
*/
void frees(int n, ...)
{
	va_list args;

	va_start(args, n);
	while (n > 0)
	{
		free(va_arg(args, char *));
		n--;
	}
}
/**
 * resetdir - helper function
 * @pwd: present working directory;
 * @oldpwd: str old pwd
 * @buffer: buffer
 * @n: number of arguements for free
 * Return: 0
*/
int resetdir(int n, char *pwd, char *oldpwd, char *buffer)
{
	chdir(pwd);
	if (buffer)
		frees(n, oldpwd, pwd);
	else
		frees(n, oldpwd, pwd, buffer);
	return (0);
}
/**
 * _cd - change directory
 * @env_list: environment linked list head pointer
 * @dir: directory to change to;
 * Return: 1 if success, 0 on failure
*/
int _cd(var_list *env_list, char *dir)
{
	char *pwd, *oldpwd, *cwd, *buffer, *new_buff;
	size_t bufsize = 1024, oldsize;

	oldpwd = _getenv(&env_list, "OLDPWD");
	pwd = _getenv(&env_list, "PWD");
	if (chdir(dir) == -1)
	{
		frees(2, oldpwd, pwd);
		return (0);
	}
	buffer = malloc(sizeof(char) * bufsize);
	if (!buffer)
		return (resetdir(2, pwd, oldpwd, NULL));
	while ((cwd = getcwd(buffer, bufsize)) == NULL && errno == ERANGE)
	{
		oldsize = bufsize;
		bufsize *= 2;
		new_buff = _realloc(buffer, oldsize, bufsize);
		if (!new_buff)
			return (resetdir(3, pwd, oldpwd, buffer));
	}
	if (!cwd)
	return (resetdir(3, pwd, oldpwd, buffer));
	if (_setenv("OLDPWD", pwd, 1, env_list) == -1)
		return (resetdir(3, pwd, oldpwd, buffer));
	if (_setenv("PWD", cwd, 1, env_list) == -1)
	{
		_setenv("OLDPWD", oldpwd, 1, env_list);
		return (resetdir(3, pwd, oldpwd, buffer));
	}
	frees(3, oldpwd, pwd, cwd);
	return (1);
}
/**
 * issep - checks if a token is a sperator
 * @str: token
 * @n: sets integer according to the token found
 * Return: 1 if true 0 if false
*/
int issep(char *str, int *n)
{
	char *sep[] = {";", "&&", "||", NULL};
	int i;

	if (!str)
		return (0);
	for (i = 0 ; sep[i] ; i++)
		if (_strcmp(sep[i], str) == 0)
		{
			if (n != NULL)
			{
				if (_strcmp(str, ";") == 0)
					*n = 1;
				if (_strcmp(str, "||") == 0)
					*n = 2;
				if (_strcmp(str, "&&") == 0)
					*n = 3;
			}
			return (1);
		}
	return (0);
}
/**
 * check_args - checks an argement vector to see if no syntax error
 * @av: srguement vector
 * @head: head of environment linked list
 * @count: number of commands so far
 * Return: 1 if no error: 0 if error
*/
int check_args(char **av, var_list *head, size_t count)
{
	int i;

	for (i = 0 ; av[i] ; i++)
	{
		if (issep(av[i], NULL) && issep(av[i + 1], NULL))
		{
			print_err_sep(_getenv(&head, "_"), count, av[i + 1]);
			return (0);
		}
	}
	return (1);
}
