#include "main.h"


/**
 * _strstr - searching a substring
 * @haystack: the string
 * @needle: the substring
 *
 * Return: int
 */

int _strstr(char *haystack, char *needle)
{
	char *p;
	char *q = needle;
	char *tmp;

	if (needle[0] == '\0')
		return (-1);
	for (p = haystack; *p != '\0'; p++)
	{
		if (*p == *q)
		{
			tmp = p;
			while (*q == *tmp && *q != '\0')
			{
				q++;
				tmp++;
			}
			if (*q == '\0')
				return (0);
			q = needle;
		}
	}
	return (-1);
}

/**
 * exit_checker - to check if there is exit in a string
 * @com: the command
 *
 * Return: 0 0r -1
 */

int exit_checker(char *com)
{
	if (_strstr(com, "exit ") == 0)
		return (0);
	if (_strstr(com, "exit\n") == 0)
		return (0);
	if (_strstr(com, "exit&") == 0)
		return (0);
	if (_strstr(com, "exit|") == 0)
		return (0);
	if (_strstr(com, "exit;") == 0)
		return (0);
	if (_strstr(com, "exit") == 0)
		return (0);
	return (-1);
}

/**
 * f_h - to handle non interactive mode
 * @com: the commands
 * @av: main arguments
 * @env: environment
 *
 * Return: Nothing
 */

void f_h(char *com, char **av, char **env)
{
	char **l_com = NULL;
	const char d[] = "\n";
	int i = 0;
	char *mycom = NULL;

	l_com = str_splt(com, d);
	free_c(com);
	while (l_com[i] != NULL)
	{
		if (l_com[i][0] != '\0')
			delete_letter(l_com[i], " ");
		if (l_com[i][0] != '\0')
			delete_letter(l_com[i], "\t");
		if (l_com[i][0] != '\0')
			delete_letter(l_com[i], "\n");
		if (l_com[i][0] != '\0')
		{
			if (exit_checker(l_com[i]) == 0)
			{
				mycom = _strdup(l_com[i]);
				free_p(l_com);
				choice_maker(mycom, av, env);
			}
			else
				choice_maker(l_com[i], av, env);
		}
		i++;
	}
	free_p(l_com);
}

/**
 * letters_f - number of bytes of a file
 * @file: the file
 *
 * Return: the number of bytes
 */

size_t letters_f(const char *file)
{
	size_t i = 0;
	struct stat st;

	if (stat(file, &st) == 0)
		i = st.st_size;
	else
		i = -1;
	return (i);
}

/**
 * file_mode - handling file mode
 * @av: main arguments
 * @env: environment
 *
 * Return: Nothing
 */

void file_mode(char **av, char **env)
{
	int fd, nb = 0, status = 0;
	char *com = NULL;
	ssize_t r;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		write(STDERR_FILENO, "./hsh: 0: Can't open ",
				_strlen("./hsh: 0: Can't open "));
		write(STDERR_FILENO, av[1], _strlen(av[1]));
		write(STDERR_FILENO, "\n", 1);
		exit(127);
	}
	nb = letters_f(av[1]);
	if (nb == -1)
	{
		write(STDERR_FILENO, "./hsh: 0: ",
				_strlen("./hsh: 0: "));
		perror(av[1]);
		exit(status);
	}

	com = malloc(nb);
	if (com != NULL)
	{
		r = read(fd, com, nb);
		if (r > 0)
		{
			com[r - 1] = '\0';
			f_h(com, av, env);
			close(fd);
			exit(0);
		}
		close(fd);
		free_c(com);
		exit(0);
	}
	close(fd);
	perror(av[1]);
	exit(EXIT_FAILURE);
}
