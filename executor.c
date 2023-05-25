#include "main.h"
/**
 * get_cmd_path - gets full path of arg string if found
 * @str: arguement string
 * @env_list: list link of environments
 * Return: full path to string, or NULL
*/
char *get_cmd_path(char *str, var_list *env_list)
{
	char *path, **paths, *cmd_pt;
	struct stat statbuf;
	int i;

	if (stat(str, &statbuf) == 0)
		return (_strdup(str));
	if (_strncmp(str, "./", 2) == 0)
		return (NULL);
	path = _getenv(&env_list, "PATH");
	if (!path)
		return (NULL);
	paths = strsplt(path, ":");
	if (!paths)
	{
		free(path);
		return (NULL);
	}
	for (i = 0 ; paths[i] ; i++)
	{
		cmd_pt = malloc(sizeof(char) * (_strlen(paths[i]) + _strlen(str) + 2));
		if (!cmd_pt)
			return (NULL);
		cmd_pt = _strcpy(cmd_pt, paths[i]);
		cmd_pt = _strcat(cmd_pt, "/");
		cmd_pt = _strcat(cmd_pt, str);
		cmd_pt = _strcat(cmd_pt, "\0");
		if (access(cmd_pt, R_OK | X_OK) == 0)
		{
			v_free(paths);
			free(path);
			return (cmd_pt);
		}
		free(cmd_pt);
	}
	v_free(paths);
	free(path);
	return (NULL);
}
/**
 * get_status - gets exit status of exited process
 * @status: status integer
 * @p_stat: where to save the status
 * @e: address that holds return of execve
 * Return: 1, 0, a helper function, all is needed is to save the status
*/
int get_status(int status, size_t *p_stat, int *e)
{
	*p_stat = WEXITSTATUS(status);
	if ((*p_stat != 0) || *e != 0)
		return (1);
	return (0);
}
/**
 * execute - executes any passed arguement count
 * @av: arguement vector
 * @env_list: environment list
 * @cmd_cnt: command count
 * @p_stat: last exit status
 * @l: for exit free
 * Return: 0 if success, -1
*/
int execute(char **av, var_list *env_list, size_t *cmd_cnt, size_t *p_stat,
char *l)
{
	int (*f)(char **av, size_t cmd_count, var_list *head, char *l), i;
	char *path;
	int a, e = 0, status; /* e records return of execve, to check failure*/

	f = inb_functs(av[0]);
	if (f != NULL)
	{
		i = f(av, *cmd_cnt, env_list, l);
		*cmd_cnt = *cmd_cnt + 1;
		if (i == 1)
			return (1);
		return (0);
	}
	path = get_cmd_path(av[0], env_list);
	if (!path)
	{
		print_err_nf(_getenv(&env_list, "_"), *cmd_cnt, av[0], "not found");
		*cmd_cnt = *cmd_cnt + 1;
		return (1);
	}
	a = fork();
	if (a == 0)
	{
		av[0] = _strdup(path);
		e = execve(av[0], av, var_list2vector(&env_list));
		print_err(_getenv(&env_list, "_"), *cmd_cnt,
		"Error executing command");
	}
	else
	{
		wait(&status);
		free(path);
		*cmd_cnt = *cmd_cnt + 1;
	}
	if (WIFEXITED(status))
		return (get_status(status, p_stat, &e));
	return (0);
}
