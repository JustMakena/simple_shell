#include "main.h"

/**
 * _getenv - get a variable
 * @name: the variable
 *
 * Return: the value of the variable
 */

char *_getenv(const char *name)
{
	char **a = NULL;
	const char d[] = "=";
	unsigned int i = 0;
	char *p = NULL;

	while (environ[i] != NULL)
	{
		a = str_splt(environ[i], d);
		if (a == NULL)
			return (NULL);
		if (_strcmpc(a[0], name) == 0)
		{
			p = _strdup(a[1]);
			free_p(a);
			return (p);
		}
		free_p(a);
		i++;
	}
	return (NULL);
}

/**
 * len_P - numbers of directories in the path
 *
 * Return: an int
 */

int len_P(void)
{
	int i;
	int l = 0;
	char *p = NULL;

	p = _getenv("PATH");
	if (p == NULL)
		return (-1);
	for (i = 0; p[i] != '\0'; i++)
	{
		if (p[i] ==  ':')
			l++;
	}
	l++;
	free_c(p);
	return (l);
}

/**
 * _pathD - to get path directories
 *
 * Return: path directories char **
 */

char **_pathD(void)
{
	char *_path = NULL;
	char **D = NULL;
	const char d[] = ":";

	_path =  _getenv("PATH");
	if (_path == NULL)
		return (NULL);
	D = str_splt(_path, d);
	free_c(_path);
	return (D);
}

/**
 * existP - to check if a file exists in the path
 * @file: the filename
 *
 * Return: 0 or 1
 */

char *existP(char *file)
{
	char **P = NULL;
	struct stat st;
	int l = 0, i = 0, l_f = 0;
	char *tmp = NULL;

	P = _pathD();
	if (file == NULL || P == NULL)
		return (existH(P, file));
	l_f = _strlen(file) + 2;
	l =  len_P();
	if (l == -1)
		return (existH(P, file));
	while (i != l)
	{
		if (P[i] == NULL)
			return (existH(P, file));
		tmp = malloc(_strlen(P[i]) + l_f);
		if (tmp == NULL)
			return ((existH(P, file)));
		tmp = _strcath(tmp, P[i]);
		if (tmp == NULL)
			return ((existH(P, file)));
		tmp = _strcat(tmp, "/");
		tmp = _strcat(tmp, file);
		if (tmp == NULL)
		{
			return (existH(P, file));
		}
		if (stat(tmp, &st) == 0)
		{
			free_p(P);
			return (tmp);
		}
		free_c(tmp);
		i++;
	}
	return (existH(P, file));
}

/**
 * _printenv - print env
 * @s: a string
 *
 * Return:noting
 */

void _printenv(char **s)
{
	int i = 0;

	while (s[i] != NULL)
	{
		write(STDOUT_FILENO, s[i], _strlen(s[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
