#include "main.h"

/**
 * handle_sigint - to handle ctr + C
 * @sig: the signal number
 *
 * Return: Nothing
 */

void handle_sigint(int sig)
{
	(void)sig;
	write(STDIN_FILENO, "\n", 1);
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
}


/**
 * comments_h - to handle comments
 * @com: the command
 *
 * Return: com
 */

char *comments_h(char *com)
{
	int i;

	if (com == NULL)
		return (NULL);
	for (i = 0; com[i] != '\0'; i++)
	{
		if (com[i] == '#')
		{
			com[i] = '\0';
			return (com);
		}
	}
	return (com);
}


/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * endSeCol - handling ; ending
 * @s: the command
 *
 * Return: Nothing
 */

void endSeCol(char *s)
{
	int i = 0;
	int c = 0;

	if (s[0] != '\0')
	{
		for (i = 0; s[i] != '\0'; i++)
			;
		while (c == 0)
		{
			if (s[i - 1] == ';')
				s[i - 1] = '\0';
			if (s[i - 2] != ';')
			{
				c = 1;
			}
			i--;
		}
	}
}

/**
 * existH - existP helper
 * @P: the path
 * @file: to display error
 *
 * Return: NULL
 */

char *existH(char **P, char *file)
{
	if (P != NULL)
		free_p(P);

	write(STDERR_FILENO, "./hsh: 1: ", _strlen("./hsh: 1: "));
	write(STDERR_FILENO, file, _strlen(file));
	write(STDERR_FILENO, ": not found\n ", _strlen(": not found\n"));
	return (NULL);
}
