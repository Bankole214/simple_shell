#include "main.h"

/**
 * _strcpy - copies a string to the other
 * @dest: destination
 * @src: source
 * Return: address to 1st element of dest
 */

char *_strcpy(char *dest, const char *src)
{
	int l = _strlen(src);
	int i = 0;

	while (i <= l)
	{
		*(dest + i) = i < l ? *(src + i) : '\0';
		i++;
	}

	return (dest);
}
/**
 * _atoi - convert a string to an integer
 * @s: string to be converted
 * Return: result
 */
int _atoi(char *s)
{
	unsigned int n = 0;
	int i = 0;
	int minus = 0;

	while (!(*(s + i) >= '0' && *(s + i) <= '9') && *(s + i))
	{
		if (*(s + i) == '-')
			minus++;
		i++;
	}

	while (*(s + i) && (*(s + i) <= '9' && *(s + i) >= '0'))
	{
		n = (n * 10) + (*(s + i) - '0');
		i++;
	}

	n = minus % 2 != 0 ? 0 - n : n;
	return (n);
}
/**
 * _strcmp - compares 2 strings
 * @s1: string 1
 * @s2: string 2
 * Return: 0 if same, more than 0 if s1 greater and lesser if else
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
			return (0);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
/**
 * is_number - checks if inputed string is a number
 * @str: string
 * Return: 1 if it is, 0 if not
*/
int is_number(const char *str)
{
	int i;

	for (i = 0 ; str[i] ; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}
	return (1);
}
