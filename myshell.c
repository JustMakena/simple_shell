#include "main.h"

static int EXIT_CODE;

/**
 * h_fork - handler of fork
 * @args: the command
 * @s: tline
 * @l_com: command
 *
 * Return: -1 or 1 or 0
 */

int h_fork(char **args, char *s, char **l_com)
{
	int choice;
	char *tp = NULL;

	if (args == NULL || args[0] == NULL)
	{
		EXIT_CODE = 127;
		return (0);
	}
	choice = cd_envh(args[0]);
	switch (choice)
	{
		case 0:
			exit_handler(args, s, l_com, EXIT_CODE);
			break;
		case 1:
			EXIT_CODE = cd_handler(args);
			return (EXIT_CODE);
		case 2:
			EXIT_CODE = _setenv(args[1], args[2], 1);
			return (EXIT_CODE);
		case 3:
			EXIT_CODE  = _unsetenv(args[1]);
			return (EXIT_CODE);
		default:
			if (args[0][0] != '/' && args[0][0] != '.')
			{
				tp = existP(args[0]);
				if (tp == NULL)
				{
					EXIT_CODE = 127;
					return (8);
				}
				free_c(args[0]);
				args[0] = _strdup(tp);
				free_c(tp);
			}
			return (h_forkEnd(args));
	}
	return (0);
}
/**
 * h_forkEnd - next of h_fork
 * @args: the command for execve
 *
 * Return: -1 or 1 or 0
 */

int h_forkEnd(char **args)
{
	pid_t p;
	int exit_s, status;
	char **envp = environ;

	p = fork();
	if (p == -1)
	{
		EXIT_CODE = -1;
		return (-1);
	}
	if (p == 0)
	{
		if ((execve(args[0], args, envp) == -1))
		{       EXIT_CODE = -1;
			return (-1);
		}
	}
	else
	{
		waitpid(p, &status, 0);
		fflush(stdin);
		if (WIFEXITED(status))
		{
			exit_s = WEXITSTATUS(status);
			if (exit_s != 0)
			{
				EXIT_CODE = exit_s;
				return (1);
			}
		}
		EXIT_CODE = 0;
		return (0);
	}
	return (1);
}

/**
 * sp_handler - to handle special $? or $$
 * @com: the command
 *
 * Return: Nothing
 */

void sp_handler(char *com)
{
	int sp = 0;
	int p;

	sp = sp_checker(com);
	if (sp == 1)
	{
		myprintf(EXIT_CODE);
		_putchar('\n');
	}
	else
	{
		p = getpid();
		myprintf(p);
		_putchar('\n');
	}
	EXIT_CODE = 0;
}


/**
 * non_ith - to choice
 * @com: the command
 * @av: main args
 * @env: environment
 *
 * Return: Nothing
 */

void non_ith(char *com, char **av, char **env)
{
	char **l_com = NULL;
	const char d[] = "\n";
	int i = 0;

	if (isatty(STDIN_FILENO))
	{
		if (com[0] != '\n')
			choice_maker(com, av, env);
	}
	else
	{
		l_com = str_splt(com, d);
		while (l_com[i] != NULL)
		{
			choice_maker(l_com[i], av, env);
			i++;
		}
		free_p(l_com);
	}
}

/**
 * main - main function
 * @ac: number of args
 * @av: args
 * @env: environment
 *
 * Return: Always 0
 */

int main(int ac, char **av, char **env)
{
	char *t_line = NULL;

	EXIT_CODE = 0;
	(void)ac;
	while (1)
	{
		signal(SIGINT, handle_sigint);
		if (av[1] != NULL)
			file_mode(av, environ);
		else
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "$ ", 2);
			t_line = _getline();
			if (t_line == NULL)
			{
				write(STDOUT_FILENO, "\n", 1);
				exit(EXIT_CODE);
			}
			else
			{
				if (_strcmp(t_line, "env") == 0)
					_printenv(env);
				else
				{
					non_ith(t_line, av, env);
				}
				if (!isatty(STDIN_FILENO))
				{
					free_c(t_line);
					exit(EXIT_CODE);
				}
				free_c(t_line);
			}
		}
	}
	return (0);
}
