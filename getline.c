#include "main.h"
/**
 * gl_rfl -memory allocation for getline
 * @lineptr: line pointer
 * @buffer: buffer for getline
 * @n: address of lineptr size
 * @bufsize: buffer size for creating innitial buffer
 * @buf: size control for lineptr
 * @old: initial size for reallocation
 * Return: 0 if error, 1 if success
*/
int gl_rf1(char **lineptr, char **buffer, size_t *n, size_t bufsize,
size_t *buf, size_t *old)
{
	if (!lineptr || !n)
		return (-1);
	*old = *lineptr ? *n : 0;
	*buf = *n && *lineptr ? *n : 120;
	*buffer = malloc(bufsize);
	if (!buffer)
		return (-1);
	return (0);
}
/**
 * buff_inc - increase buffer size if needed
 * @buffer: buffer address
 * @BUFF: address of static buffer size
 * Return: 1 if success, 0 if failure
*/
int buff_inc(char **buffer, size_t *BUFF)
{
	*BUFF *= 2;
	*buffer = _realloc(*buffer, (*BUFF / 2), *BUFF);
	if (!*buffer)
	{
		free(*buffer);
		return (-1);
	}
	return (0);
}
int end_getline(char **lineptr, size_t total, char *buffer, size_t *n,
size_t buf, FILE * stream, ssize_t r, size_t *start);
/**
 * _getline - gets inputed line and saves to lineptr
 * @lineptr: pointer to memory space to save string
 * @n: initial size of lineptr
 * @stream: pointer to file stream
 * Return: -1 on failure, else number of read charcters
*/
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static size_t buf, BUFF, start;
	ssize_t r;
	size_t j, total = 0, buff_pos = 0, alocd = 0, old;
	char *buffer;

	BUFF = 2048;
	if (stream->_fileno == 0)
		start = 0;
	if (gl_rf1(lineptr, &buffer, n, BUFF, &buf, &old) == -1)
		return (-1);
	while ((r = read(stream->_fileno, buffer + buff_pos, BUFF)) > 0)
	{
		for (j = 0; j < (size_t)r; j++)
		{
			if (total >= buf - 1 || !*lineptr)
			{
				old = alocd ? buf : old;
				buf = *lineptr ? buf * 2 : buf;
				*lineptr = _realloc(*lineptr, old, buf);
				if (!buffer)
					return (-1);
			}
			(*lineptr)[total++] = buffer[buff_pos + j];
			if (buffer[buff_pos + j] == '\n')
			{
				break;
			}
		}

		if (buffer[r - 1] == '\n')
			break;
		buff_pos += j;
		if (j == BUFF)
			if (buff_inc(&buffer, &BUFF) == -1)
				return (-1);
	}
	return (end_getline(lineptr, total, buffer, n, buf, stream, r, &start));
}
/**
 * end_getline - helper function for refactoring
 * @lineptr: line pointer
 * @total: total read
 * @buffer: buffer
 * @buf: size of lineptr
 * @r: read value
 * @n: lineptr size address
 * @stream: file stream
 * @start: pointer to restart string
 * Return: number of bytes read
*/
int end_getline(char **lineptr, size_t total, char *buffer, size_t *n,
size_t buf, FILE *stream, ssize_t r, size_t *start)
{
	if (*lineptr)
	(*lineptr)[total] = 0;
	*n = buf;
	free(buffer);
	*start = *start + total;
	fseek(stream, *start, SEEK_SET);
	return (r == (ssize_t)-1 ? -1 : (ssize_t)total ? (ssize_t)total :
	(ssize_t)-1);
}
