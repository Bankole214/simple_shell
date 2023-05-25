#include "main.h"
/**
 * _strncmp - compares n bytes of a string
 * @s1: string 1
 * @s2: string 2
 * @n: bites to compare
 * Return: 0 if equal, > 0 if s1 > s2 <0 if s1 < s2
*/
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i = 0;

	for (; i < n ; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		if (s1[i] == 0)
			return (0);
	}
	return (0);
}

/**
 * _strlen - count length of string
 * @s: string to be counted address of string
 * Return: returns the length
 */
int _strlen(const char *s)
{
	int i = 0;

	while (*(s + i))
	{
		i++;
	}
	return (i);
}


/**
 * _strcat - appends src to dest
 * @dest: destination string
 * @src: source string
 * Return: pointer to destination
 */

char *_strcat(char *dest, const char *src)
{
	int i = 0;
	int j = 0;

	if (!dest || !src)
		return (NULL);
	while (dest[i])
	{
		i++;
	}

	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	dest[i] = '\0';
	return (dest);
}
/**
 * _strdup - duplicates a string
 * @str: string to be duplicated
 * Return: pointer to a newly allocated space in memory, which contains a copy
 * of the string given as a parameter.
 */

char *_strdup(const char *str)
{
	char *dup;
	int len, i;

	if (str == NULL)
		return (NULL);
	len = _strlen(str);
	dup = malloc(sizeof(char) * (len + 1));

	if (dup == NULL)
		return (NULL);
	for (i = 0; i < len; i++)
		*(dup + i) = *(str + i);
	*(dup + i) =  '\0';

	return (dup);
}
