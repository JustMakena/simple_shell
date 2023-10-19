#include "main.h"

/**
 * choice_maker - to choice
 * @com: the command
 * @av: main args
 * @env: environment
 *
 * Return: Nothing
 */

void choice_maker(char *com, char **av, char **env)
{
	int a, o, out = 0;
	const char and[] = "&";
	const char or[] = "|";

	(void)out;
	com = comments_h(com);
	a = and_or_checker(com, and);
	switch (a)
	{
		case 1:
			and_or_h(com, av, env, and);
			break;
		case 2:
			final_and_or(com, av, env);
			break;
		default:
			o = and_or_checker(com, or);
			switch (o)
			{
				case 1:
					and_or_h(com, av, env, or);
					break;
				case 2:
					final_and_or(com, av, env);
					break;
				default:
					out = se_colh(com, av, env);
					break;

			}
	}

}


/**
 * se_colh - semicolon handler
 * @com: the commands
 * @av: main arguments
 * @env: environment
 *
 * Return: an integer
 */

int se_colh(char *com, char **av, char **env)
{
	char **l_com = NULL;
	const char d[] = ";";
	int i = 0, s, sp;
	char **args = NULL;
	const char d1[] = " ";

	delete_letter(com, d1);
	endSeCol(com);
	l_com = str_splt(com, d);
	while (l_com[i] != NULL)
	{
		delete_letter(l_com[i], d1);
		if (_strcmp(l_com[i], "env") == 0)
			_printenv(env);
		else
		{
			sp = sp_checker(l_com[i]);
			if (sp == -1)
			{
				args = str_splt(l_com[i], d1);
				s = h_fork(args, com, l_com);
				if (s == -1)
					error_h(av[0], args[0]);
				free_p(args);
			}
			else
				sp_handler(l_com[i]);
		}
		i++;
	}
	free_p(l_com);
	return (s);
}

/**
 * and_or_h - to handle && and ||
 * @com: the command
 * @av: main arguments
 * @env: environment
 * @d: delimiter
 *
 * Return: Nothing
 */

void and_or_h(char *com, char **av, char **env, const char d[])
{
	char **l_com = NULL;
	int i = 0, s;
	const char d1[] = " ";
	int end = 0;
	char *mycom = NULL;

	delete_letter(com, d);
	end = size(com, d) - 1;
	l_com = str_splt(com, d);
	while (l_com[i] != NULL)
	{
		delete_letter(l_com[i], d1);
		if (_strcmp(l_com[i], "env") == 0)
			_printenv(env);
		else
		{
			if (_strcmp(l_com[i], "exit") == 0)
			{
				free_c(com);
				mycom = _strdup(l_com[i]);
				free_p(l_com);
				s = se_colh(mycom, av, env);
			}
			s = se_colh(l_com[i], av, env);
			if (d[0] == '&')
			{
				if (s != 0)
					i = end - 1;
			}
			if (d[0] == '|')
			{
				if (s == 0)
					i = end - 1;
			}
		}
		i++;
	}
	free_p(l_com);
}

/**
 * and_or_checker - to check if there is && or || in  a str
 * @com: the command
 * @d: the letter to check
 *
 * Return: -1 or 1
 */

int and_or_checker(char *com, const char d[])
{
	int i;
	int and_or = 0;

	if (com[0] == d[0])
		return (-1);
	for (i = 0; com[i] != '\0'; i++)
	{
		if (com[i] == d[0])
		{
			and_or = 1;
			i++;
			if (com[i] != d[0])
				return (-1);
			if (com[i + 1] == d[0])
				return (-1);
		}
	}
	if (and_or == 1)
	{
		if (com[i - 1] == d[0])
			return (2);
		return (1);
	}
	return (0);
}

/**
 * final_and_or - if the command ends with && or ||
 * @com: the command
 * @av: arguments
 * @env: environment
 *
 * Return: Nothing
 */

void final_and_or(char *com, char **av, char **env)
{
	int i = 0, cmp_b = 0;
	char *end_line = NULL;

	while (i == 0)
	{
		write(STDOUT_FILENO, "> ", 2);
		end_line = _getline();
		if (end_line == NULL)
			perror("getline");
		cmp_b = _strcmp(end_line, "\n");
		if (cmp_b != 0)
		{
			i = 1;
			com = _strcat(com, end_line);
			free_c(end_line);
			choice_maker(com, av, env);
		}
	}
}
