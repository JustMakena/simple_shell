#include "main.h"

/**
 * cd_home - cd home
 *
 * Return: 0 on success
 */

int cd_home(void)
{
	char *home = NULL;
	int s;
	char buf[1024];

	(void)s;
	if (getcwd(buf, sizeof(buf)) == NULL)
	{
		free_c(home);
		perror("./hsh");
		return (1);
	}

	home = _getenv("HOME");
	if (chdir(home) != 0)
	{
		free_c(home);
		perror("./hsh");
		return (1);
	}
	s = _setenv("PWD", home, 1);
	s = _setenv("OLDPWD", buf, 1);
	free_c(home);
	return (0);
}

/**
 * cd_previous - cd old directory
 *
 * Return: 0 on success
 */

int cd_previous(void)
{
	char *old = NULL;
	int s;
	char buf[1024];

	(void)s;
	if (getcwd(buf, sizeof(buf)) == NULL)
	{
		free_c(old);
		perror("./hsh");
		return (1);
	}

	old = _getenv("OLDPWD");
	if (chdir(old) != 0)
	{
		free_c(old);
		perror("./hsh");
		return (1);
	}
	s = _setenv("PWD", old, 1);
	s = _setenv("OLDPWD", buf, 1);
	write(STDOUT_FILENO, old, _strlen(old));
	write(STDOUT_FILENO, "\n", 1);
	free_c(old);
	return (0);
}

/**
 * cd_dir - cd dir_name
 * @args: the command
 *
 * Return: 0 on success
 */

int cd_dir(char **args)
{
	int s;
	char buf[1024];

	(void)s;
	if (getcwd(buf, sizeof(buf)) == NULL)
	{
		perror("./hsh");
		return (1);
	}

	if (chdir(args[1]) != 0)
	{
		perror("./hsh");
		return (1);
	}
	s = _setenv("PWD", args[1], 1);
	s = _setenv("OLDPWD", buf, 1);
	return (0);

}

/**
 * cd_handler - to handle cd
 * @args: cd command
 *
 * Return: 0 on success
 */

int cd_handler(char **args)
{
	if (args[1] == NULL)
		return (cd_home());
	if (args[2] != NULL)
	{
		write(STDERR_FILENO, "./hsh: 1: cd: Too many arguments!\n",
				_strlen("./hsh: 1: cd: Too many arguments!\n"));
		return (1);
	}
	if (args[1][0] == '-')
		return (cd_previous());
	return (cd_dir(args));
}
