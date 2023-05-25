#include "main.h"
/**
 * getline_EOF_syn_err - print EOF syntax error
 * @head: headpointer of environ list
 * @count: cmd counter
 * Return: NULL
*/
char **getline_EOF_syn_err(var_list *head, size_t *count)
{
	print_err(_getenv(&head, "_"), *count,
	"Syntax error: end of file unexpected");
	return (NULL);
}
/**
 * v_free_NULL - helper function frees a vector and returns null
 * @av: vector
 * Return: NULL
*/
char **v_free_NULL(char **av)
{
	v_free(av);
	return (NULL);
}
/**
 * alloc_exec - gets arguements and executes them, helper function
 * @f: integer pointer for iteration
 * @g: integer pointer for iteration
 * @h: integer pointer for iteration
 * @d: integer pointer for return of execution
 * @sv: vector of tokens
 * @head: head of environ list
 * @count: command count
 * @p_stat: previous exit status
 * @l: line for exit free
 * Return: 0 on success -1 if failed
*/
int alloc_exec(int *f, int *g, int *h, int *d, char **sv,
var_list *head, size_t *count, size_t *p_stat, char *l)
{
	int i, a = *f, b = *g, c = *h;
	char **av;

	av = malloc(sizeof(char *) * (1 + a - b));
	if (!av)
		return (-1);
	av[a - b] = NULL;
	c = b;
	for (i = b ; i <  a ; i++)
	av[i - c] = _strdup(sv[b++]);
	*d = execute(av, head, count, p_stat, l);
	v_free(av);
	*f = a;
	*g = b;
	*h = c;
	return (0);
}
/**
 * an_exec - analyzes a vector for seperators and executes as needed
 * @sv: tokens vector
 * @head: head of environ list
 * @count: command count
 * @p_stat: previous exit status
 * @l: for exit free
 * Return: 0 success, -1 failure
*/
int an_exec(char **sv, var_list *head, size_t *count, size_t *p_stat, char *l)
{
	int a, b, c, d, e, sep = 0, sep1;

	for (a = 0, b = 0 ; sv[a] ; a++)
	{
		sep1 = sep;
		if (issep(sv[a], &e))
		{
			sep++;
			if (alloc_exec(&a, &b, &c, &d, sv, head, count, p_stat, l) == -1)
				return (-1);
			b = a + 1;
			if (e > 1)
			{
				if ((e == 2 && d == 0) || (e == 3 && d == 1))
					break;
			}
		}
	}
	if (!sep)
		d = execute(sv, head, count, p_stat, l);
	if (sep && sep == sep1)
		if (e == 1 || (e == 2 && d == 1) || (e == 3 && d == 0))
			if (alloc_exec(&a, &b, &c, &d, sv, head, count, p_stat, l) == -1)
				return (-1);
	return (d == 1 ? -1 : 0);
}
/**
 * pre_proc - processes input before execution
 * @line: inputed lie form getline
 * @delim: delimiters for splitting
 * @head: head of environ list
 * @count: command count
 * @p_stat: previous exit status
 * @fd: file descriptor
 * Return: arguement vectors
*/
char **pre_proc(char *line, const char *delim, var_list *head, size_t *count,
size_t *p_stat, FILE *fd)
{
	int i, d, l1, l2, m;
	char *line2 = NULL, **av, **av2;
	size_t n2 = 0;

	av = procs(strsplt(line, delim), p_stat, head);
	if (av)
		if (check_args(av, head, *count))
		{
			d = issep(av[v_count(av) - 1], &m);
			while (d && m > 1)
			{
				l1 = v_count(av);
				if (fd->_fileno == 0)
					_put("> ");
				*count = *count + 1;
				if (getline(&line2, &n2, fd) == -1)
				return (getline_EOF_syn_err(head, count));
				av2 = procs(strsplt(line2, delim), p_stat, head);
				l2 = v_count(av2);
				av = _realloc(av, sizeof(char *) * (l1 + 1),
				(l1 + l2 + 1) * sizeof(char *));
				for (i = 0 ; av2[i]; i++)
					av[l1++] = _strdup(av2[i]);
				av[l1] = NULL;
				v_free(av2);
				free(line2);
				line2 = NULL;
				if (check_args(av, head, *count))
					d = issep(av[v_count(av) - 1], &m);
				else
				return (v_free_NULL(av));
			}
			return (av);
		}
	return (NULL);
}
