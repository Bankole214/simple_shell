#include "main.h"
/**
 * isdelim - checks isf a charter is a delimeter byte
 * @c: character
 * @delim: delimeter bytes
 * Return: 1 if yes or 0 if not
*/
int isdelim(char c, const char *delim)
{
	while (*delim)
	{
		if (*delim == c) /* if char is a delimeter byte*/
		return (1); /* retutn true*/
	delim++;
	}
	return (0); /* if not return false */
}
/**
 * strcount - counts the number of tokens in a string
 * @str: string
 * @delim: delimeter
 * Return: Number of tokens
*/
unsigned int strcount(char *str, const char *delim)
{
	unsigned int c = 0, i;

	for (i = 0 ; str[i] ; i++)
	{
		if (isdelim(str[i], delim) == 0)
		{/* if a character is not a delimeter, increment count */
			c++;
		/* move through the string till the last non delimeter char*/
		while (str[i + 1] && isdelim(str[i + 1], delim) == 0)
			i++;
		}
	}
	return (c);
}
/**
 * strsplt - gets a string input and returns an string vector
 * @input: string to split
 * @delim: delimeter bytes
 * Return: a vector of strings
*/
char **strsplt(char *input, const char *delim)
{
	char **sv = NULL; /* for our vector */
	unsigned int sc; /*string count*/
	unsigned int j = 0;

	if (!input)
		return (NULL);
	sc = strcount(input, delim);
	if (sc)
		sv = malloc(sizeof(char *) * (sc + 1));
	if (!sv)
		return (NULL);
	sv[sc] = NULL;
	for (j = 0; *input ; input++)
	{
		if (isdelim(*input, delim) == 1)
		{/* if character is a delimeter byte, relace with null byte */
			*input = '\0';
			continue;
		}
		if (isdelim(*input, delim) == 0)
		{	/*if the first non delim is encountered let it be the start of a token*/
			sv[j] = input;
			while (*(input + 1) && !isdelim(*(input + 1), delim))
				input++;
		}
		j++;
	}
	for (j = 0 ; sv[j] ; j++)
		sv[j] = _strdup(sv[j]);
	return (sv);/* Return the generated null terminated vector*/
}
/**
 * v_count - count how many arrays in a vector
 * @vector: vector to count
 * Return: number of strings in vector
*/
int v_count(char **vector)
{
	int c = 0;

	while (*vector)
	{
		c++;
		vector++;
	}
	return (c);
}
/**
 * v_free - frees a vector
 * @vector: vector to free
*/
void v_free(char **vector)
{
	int i = 0, c;

	if (vector)
	{
		c = v_count(vector);
		while (i < c)
		{
			if (vector[i])
				free(vector[i]);
			i++;
		}
		free(vector);
	}
}
