#include "main.h"

/**
 * _getlineHelper - to reduce _getline
 * @s: the command
 *
 * Return: NULL
 */

char *_getlineHelper(char *s)
{
	free_c(s);
	perror("read");
	return (NULL);
}

/**
 * non_isattyHelper - to handle non isatty
 * @r: size
 * @command: command
 * @bufferSize: buff size
 *
 * Return: char *
 */

char *non_isattyHelper(ssize_t r, char *command, size_t bufferSize)
{
	r = 0;
	r = read(STDIN_FILENO, command, bufferSize);
	if (r <= 0)
		return (_getlineHelper(command));
	command[r - 1] = '\0';
	return (command);

}
/**
 * _getline - getline
 *
 * Return: the line
 */

char *_getline(void)
{
	ssize_t r = 0;
	size_t bufferSize = 1024;
	char *command = NULL;
	char c;
	int i = 0, w = 1;

	command = (char *)malloc(bufferSize * sizeof(char));
	if (command == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	if (isatty(STDIN_FILENO))
	{
		while (w == 1)
		{
			r = read(STDIN_FILENO, &c, 1);
			if (r == -1)
				return (_getlineHelper(command));
			if (r == 0 || c == '\n')
			{
				if (r == 0 && i == 0)
				{
					free_c(command);
					return (NULL);
				}
				command[i] = '\0';
				w = 0;
			}
			else
				command[i] = c;
			i++;
		}
	}
	else
		return (non_isattyHelper(r, command, bufferSize));
	return (command);
}

/**
 * sp_checker - to check $ or ?
 * @com: the command
 *
 * Return: 1, -1 or 2
 */

int sp_checker(char *com)
{
	if (_strcmp(com, "echo $?") == 0)
		return (1);
	if (_strcmp(com, "echo \"$?\"") == 0)
		return (1);
	if (_strcmp(com, "echo $$") == 0)
		return (2);
	if (_strcmp(com, "echo \"$$\"") == 0)
		return (2);
	return (-1);
}

/**
 * myprintf - to print number
 * @n: the number
 *
 * Return: Nothing
 */

void myprintf(int n)
{
	int i;
	int cpt = 0;
	int mul = 10;

	if (n < 0)
	{
		_putchar('-');
		n = -n;
	}

	while (n % mul != n)
	{
		mul = mul * 10;
		cpt++;
	}
	mul = mul / 10;

	for (i = 1; i <= cpt; i++)
	{
		_putchar(48 + ((n - (n % mul)) / mul));
		n = n % mul;
		mul = mul / 10;
	}
	_putchar(48 + n);
}
