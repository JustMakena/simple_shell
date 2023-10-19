#include "main.h"

/**
 * env_size - size of environ
 *
 * Return: an integer
 */

int env_size(void)
{
	int i = 0;

	while (environ[i] != NULL)
		i++;
	return (i + 1);
}

/**
 * whereToSet - to get where to the new value
 * @name: the variable
 * @value: the value
 *
 * Return: the value of the variable
 */

int whereToSet(char *name, char *value)
{
	char **a = NULL;
	const char d[] = "=";
	unsigned int i = 0;

	while (environ[i] != NULL)
	{
		a = str_splt(environ[i], d);
		if (a == NULL)
			return (-1);
		if (_strcmpc(a[0], name) == 0)
		{
			if (_strcmp(a[1], value) == 0)
			{
				free_p(a);
				return (-2);
			}
			free_p(a);
			return (i);
		}
		free_p(a);
		i++;
	}
	return (-1);
}

/**
 * change_value - to change an environment variable
 * @name: the name
 * @value: the new value
 *
 * Return: an int
 */

int change_value(char *name, char *value)
{
	char **myenv = NULL;
	int l = 0, j = 0, i = 0, k = 0, s = 0;
	char *new = NULL;

	j = whereToSet(name, value);
	if (j == -2)
		return (0);
	l = env_size();
	myenv = malloc(l * sizeof(*myenv));
	if (myenv == NULL)
	{
		perror("Malloc failed");
		return (-1);
	}
	for (i = 0; i < l; i++)
		myenv[i] = NULL;
	s = _strlen(name) + _strlen(value) + 2;
	new = malloc(s);
	if (new == NULL)
	{
		perror("Malloc failed");
		return (1);
	}
	new = _strcath(new, name);
	new = _strcat(new, "=");
	new = _strcat(new, value);
	i = 0;
	k = 0;
	while (environ[i] != NULL)
	{
		if (i == j)
			myenv[k] = _strdup(new);
		else
			myenv[k] = _strdup(environ[i]);
		i++;
		k++;
	}
	free_c(new);
	environ = myenv;
	return (0);
}

/**
 * add_env - to add environment variable
 * @name: new variable
 * @value: its value
 *
 * Return: 0 or -1
 */

int add_env(char *name, char *value)
{
	char **myenv = NULL;
	int l = 0, i = 0;
	char *new = NULL;
	int s = 0;

	l = env_size();
	l += 1;

	myenv = malloc(l * sizeof(*myenv));
	if (myenv == NULL)
	{
		perror("Malloc failed");
		return (1);
	}
	for (i = 0; i < l; i++)
		myenv[i] = NULL;
	i = 0;
	while (environ[i] != NULL)
	{
		myenv[i] = _strdup(environ[i]);
		i++;
	}
	s = _strlen(name) + _strlen(value) + 2;
	new = malloc(s);
	if (new == NULL)
	{
		perror("Malloc failed");
		return (1);
	}
	new = _strcath(new, name);
	new = _strcat(new, "=");
	new = _strcat(new, value);
	myenv[i] = _strdup(new);
	free_c(new);
	environ = myenv;
	return (0);
}


/**
 * _setenv - to add a variable
 * @name: variable name
 * @value: the value
 * @overwrite: 0 to do nothing
 *
 * Return: an integer
 */


int _setenv(char *name, char *value, int overwrite)
{
	char *s = NULL;

	if (name == NULL)
	{
		write(STDERR_FILENO, "./hsh: 1: setenv: name is null\n",
				_strlen("./hsh: 1: setenv: name is null\n"));
		return (1);
	}
	if (value == NULL)
	{
		write(STDERR_FILENO, "./hsh: 1: setenv: value is null\n",
				_strlen("./hsh: 1: setenv: value is null\n"));
		return (1);
	}
	s = _getenv(name);
	if (s == NULL)
		return (add_env(name, value));

	if (overwrite != 0)
	{
		free_c(s);
		return (change_value(name, value));
	}
	free_c(s);
	return (0);
}
