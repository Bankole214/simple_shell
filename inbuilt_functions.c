#include "main.h"
/**
* env - prints environment
* @av: arguement vector
* @cmd_count: command count for error printing
* @head: head pointer of environments linked list
* @l: unused
* Return: 0 sunccess, 1 failure
*/
int env(char **av, size_t cmd_count, var_list *head, char *l)

{
int ac = v_count(av), i;

char *error = "Usage: env", **_env;

(void)l;
if (ac > 1)
{
print_err(_getenv(&head, "_"), cmd_count, error);
return (-1);
}
_env = var_list2vector(&head);
for (i = 0 ; _env[i] ; i++)
_puts(_env[i]);
v_free(_env);
return (0);
}
/**
* __exit - exits the shell
* @av: arguement vector
* @cmd_count: command count for error printing
* @head: head pointer of environments linked list
* @l: pointer to line to be freed
* Return: 0 sunccess, 1 failure
*/
int __exit(char **av, size_t cmd_count, var_list *head, char *l)
{
int ac = v_count(av);
int stat;

if (ac > 1)
{
if (is_number(av[1]))
{
stat = _atoi(av[1]);
free_envlist(head);
v_free(av);
free(l);
exit(stat);
}
print_exit_err(_getenv(&head, "_"), cmd_count, av[1]);
}
else
{
free_envlist(head);
v_free(av);
free(l);
exit(EXIT_SUCCESS);
}
return (0);
}
/**
* __setenv - innitialive a new environment variable or modify an existing one.
* @av: arguement vector
* @cmd_count: command count for error printing
* @head: head pointer of environments linked list
* @l: unused
* Return: 0 sunccess, 1 failure
*/
int __setenv(char **av, size_t cmd_count, var_list *head, char *l)
{
int ac = v_count(av);
char *error = "Usage: setenv VARIABLE VALUE";

(void)l;
if (ac != 3)
{
print_err(_getenv(&head, "_"), cmd_count, error);
return (1);
}

if (_setenv(av[1], av[2], 1, head) == -1)
{
print_err(_getenv(&head, "_"), cmd_count, "error setting variable");
return (1);
};
return (0);
}
/**
* __unsetenv - deletes a variable from the environment list
* @av: arguement vector
* @cmd_count: command count for error printing
* @head: head pointer of environments linked list
* @l: unused
* Return: 0 sunccess, 1 failure
*/
int __unsetenv(char **av, size_t cmd_count, var_list *head, char *l)
{
int ac = v_count(av);
char *error = "Usage: setenv VARIABLE";

(void)l;
if (ac != 2)
{
print_err(_getenv(&head, "_"), cmd_count, error);
return (1);
}
_unsetenv(av[1], head);
return (0);
}
/**
* cd - change working directory
* @av: arguement vector
* @cmd_count: command count for error printing
* @head: head pointer of environments linked list
* @l: unused
* Return: 0 sunccess, 1 failure
*/
int cd(char **av, size_t cmd_count, var_list *head, char *l)
{
int ac = v_count(av);
char *dir, *home, *oldpwd;

(void)l;
home =  _getenv(&head, "HOME");
oldpwd = _getenv(&head, "OLDPWD");
if (ac > 1)
{
if (_strcmp(av[1], "-") == 0)
dir = oldpwd;
else
dir = av[1];
}
else
dir = home;
if (_cd(head, dir) == 0)
{
print_cd_err(_getenv(&head, "_"), cmd_count, dir);
frees(2, home, oldpwd);
return (-1);
}
frees(2, home, oldpwd);
return (0);
}
