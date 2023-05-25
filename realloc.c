#include "main.h"

/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr: is a pointer to the memory previously allocated with a call to malloc
 * @old_size: is the size, in bytes, of the allocated space for ptr
 * @new_size: is the new size, in bytes of the new memory block
 * Return: pointer to new allocated space of NULL if failed or memory freed
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new;
	char *dest, *src;
	unsigned int size, i;

	if (ptr == NULL)
	{
		new = malloc(new_size);
		return (new);
	}
	if (old_size == new_size)
		return (ptr);
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	new = malloc(new_size);
	if (new == NULL)
		return (NULL);
	dest = new;
	src = ptr;

	size = old_size < new_size ? old_size : new_size;

	for (i = 0; i < size; i++)
		dest[i] = src[i];

	free(ptr);
	return (new);
}
