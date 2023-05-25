#include "main.h"
/**
 * sigint_handler - handles ctrl + C signal
 * @n: unused int
*/
void sigint_handler(int n)
{
	(void)n;
	_put("\n$ ");
}
/**
 * get_file - gets file descriptor
 * @av: arguement vector
 * @ac: arguement count
 * Return: file descriptor or -1 if error
*/
FILE *get_file(int ac, char **av)
{
	FILE *fd;

	if (ac > 2)
	{
		perror("Usage: simple_shell [filename]");
		exit(98);
	}
	if (ac == 1)
		fd = stdin;
	else
		fd = fopen(av[1], "r");
	if (fd == NULL)
	{
		_put_e(av[0]);
		_put_e(": 0: cannot open ");
		_put_e(av[1]);
		_puts_e(": No such file");
		exit(98);

	}
	return (fd);
}
/**
 * main - simple shell project
 * @ac: arguement count
 * @av: arguement vector
 * @env: environment
 * Return: 0 if success
*/
int main(int ac, char **av, char **env)
{
	var_list *env_list = NULL;
	char **sv, *line = NULL, *delim = "\t\r\f\v\b \n", p = 0, ret = 0;
	size_t n = 0, cmd_cnt = 1, exstat = 0;
	ssize_t r = 1;
	FILE *fd = get_file(ac, av);

	signal(SIGINT, sigint_handler);
	env_list = build_env_list(&env_list, env);
	while (1 && (!p || r != 0))
	{
		p = !isatty(STDIN_FILENO);
		if (ac == 1 && !p)
		_put("$ ");
		r = getline(&line, &n, fd);
		if (r == -1)
			break;
		sv = pre_proc(line, delim, env_list, &cmd_cnt, &exstat, fd);
		if (!sv)
			continue;
		 ret = an_exec(sv, env_list, &cmd_cnt, &exstat, line);
		v_free(sv);
	}
	free(line);
	if (fd->_fileno > STDIN_FILENO)
		fclose(fd);
	if (!p && ac == 1)
		_put("\n");
	if (env_list)
		free_envlist(env_list);
	if (p && ret == -1)
		exit(127);
	return (0);
}
