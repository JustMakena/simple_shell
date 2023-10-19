#include "main.h"

/**
 * free_c - to free t_line
 * @s: the ptr to free
 *
 * Return: Nothing
 */

void free_c(char *s)
{
	if (s != NULL)
	{
		free(s);
		s = NULL;
	}
}


/**
 * free_p - to free an array of array
 * @a: the array
 *
 * Return: Nothing
 */

void free_p(char **a)
{
	int i = 0;

	if (a != NULL)
	{
		while (a[i] != NULL)
		{
			free(a[i]);
			a[i] = NULL;
			i++;
		}
		if (a[i] != NULL)
		{
			free(a[i]);
			a[i] = NULL;
		}
		if (a != NULL)
		{
			free(a);
			a = NULL;
		}
	}
}

/**
 * error_h - handling errors
 * @av: 1
 * @args: 2
 *
 * Return: Nothing
 */

void error_h(char *av, char *args)
{
	char *error = NULL;

	error = malloc(6 + _strlen(av) + _strlen(args));
	if (error != NULL)
	{
		if (av != NULL)
			error = _strcath(error, av);
		error = _strcat(error, ": 1: ");
		if (args != NULL)
			error = _strcat(error, args);
		perror(error);
		free_c(error);
	}
}
