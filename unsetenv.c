#include "main.h"

/**
 * exit_handler - to exit
 * @args: command
 * @s: to free
 * @l_com: to free
 * @n: exit code
 *
 * Return: Nothing
 */

void exit_handler(char **args, char *s, char **l_com, int n)
{
	int status;

	if (args[1] == NULL)
		exit(n);
	status = _atoi(args[1]);
	if (status < 0)
	{
		write(STDERR_FILENO, "./hsh: 1: exit: Illegal number: ",
				_strlen("./hsh: 1: exit: Illegal number: "));
		write(STDERR_FILENO, args[1], _strlen(args[1]));
		write(STDERR_FILENO, "\n", 1);
		exit(2);
	}
	free_p(args);
	free_p(l_com);
	free_c(s);
	exit(status);

}


/**
 * cd_envh - to handle cd and env com
 * @args: the commande
 *
 * Return: 0, 1, 2, 3
 */

int cd_envh(char *args)
{
	if (args == NULL)
		return (-1);
	if (_strcmp(args, "exit") == 0)
		return (0);
	if (_strcmp(args, "cd") == 0)
		return (1);
	if (_strcmp(args, "setenv") == 0)
		return (2);
	if (_strcmp(args, "unsetenv") == 0)
		return (3);
	return (-1);
}

/**
 * whereToUnset - to get where to the new value
 * @name: the variable
 *
 * Return: the value of the variable
 */

int whereToUnset(char *name)
{
	char **a = NULL;
	const char d[] = "=";
	unsigned int i = 0;

	if (name == NULL)
	{
		write(STDERR_FILENO, "./hsh: 1: unsetenv: name is null\n",
				_strlen("./hsh: 1: unsetenv: name is null\n"));
		return (-1);
	}
	while (environ[i] != NULL)
	{
		a = str_splt(environ[i], d);
		if (a == NULL)
			return (-1);
		if (_strcmpc(a[0], name) == 0)
		{
			free_p(a);
			return (i);
		}
		free_p(a);
		i++;
	}
	return (-1);
}


/**
 * _unsetenv - to delete variable
 * @name: the name
 *
 * Return: an int
 */

int _unsetenv(char *name)
{
	int l = 0, j = 0, i = 0, k = 0;
	char **myenv = NULL;

	j = whereToUnset(name);
	if (j == -1)
		return (1);
	l = env_size() - 1;
	myenv = malloc(l * sizeof(*myenv));
	if (myenv == NULL)
	{
		perror("Malloc failed");
		return (1);
	}
	for (i = 0; i < l; i++)
		myenv[i] = NULL;
	i = 0;
	k = 0;
	while (environ[i] != NULL)
	{
		if (i == j)
			k--;
		else
			myenv[k] = _strdup(environ[i]);
		i++;
		k++;
	}
	environ = myenv;
	return (0);
}
