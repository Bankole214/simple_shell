#include "main.h"
/**
 * num_len - gets the length of string for an integer print with any base
 * @n: number
 * Return: length
 */

int num_len(unsigned long n)
{
	unsigned int l = 1;

	for (; n > 9 ; n /= 10)
		l++;
	return (l);
}
/**
 * num2str - converts any signed number to string
 * @n: number in base 10
 * Return: pointer to string
 */

char *num2str(unsigned long n)
{
	int l = 0, j;
	char *str;

	l += num_len(n);
	str = malloc(sizeof(char) * (l + 1));
	if (str == NULL)
		return (NULL);
	str[l] = '\0';
	for (j = l - 1 ; j >= 0; j--)
	{

		str[j] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}
