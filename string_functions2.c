#include "main.h"

/**
 * _strdup - to duplicate a string
 * @s: the string
 *
 * Return: the string
 */

char *_strdup(char *s)
{
	char *d = NULL;

	d = malloc(_strlen(s) + 1);
	if (d != NULL)
	{
		d = _strcpy(d, s);
		return (d);
	}
	return (NULL);
}
/**
 * _strcat - copying
 * @src: source
 * @dest: destination
 *
 * Return: char *
 */

char *_strcat(char *dest, char *src)
{
	int i = 0;
	int j = 0;

	if (dest == NULL || src == NULL)
		return (NULL);

	for (i = 0; dest[i] != '\0'; i++)
		;
	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}
	dest[i] = '\0';

	return (dest);
}

/**
 * _strcath - concatening other way
 * @src: source
 * @dest: destination
 *
 * Return: char *
 */

char *_strcath(char *dest, char *src)
{
	int j = 0;

	if (dest == NULL || src == NULL)
		return (NULL);

	for (j = 0; src[j] != '\0'; j++)
		dest[j] = src[j];
	dest[j] = '\0';

	return (dest);
}


/**
 * _atoi - string numbers
 * @s: The string
 *
 * Return: an integer
 */

int _atoi(char *s)
{
	int i;
	int nb = 0;

	if (s != NULL)
	{
		for (i = 0; s[i] != '\0'; i++)
		{
			if (s[i] < 48 || s[i] > 57)
				return (-1);
			nb = nb * 10;
			nb = nb + (s[i] - 48);
		}
	}
	return (nb);
}

/**
 * delete_letter - delete letter that is not useful
 * @s: in this string
 * @d: the letter to delete
 *
 * Return: Nothing
 */

void delete_letter(char *s, const char d[])
{
	int l = 0, i = 0, j = 0;

	if (s != NULL)
	{
		if (s[0] != '\0')
		{
			l = _strlen(s);
			for (i = 0; i < l - 1; i++)
			{
				if (s[i] == d[0] && s[i + 1] == d[0])
				{
					for (j = i + 1; j < l; j++)
						s[j] = s[j + 1];
					i--;
				}
			}

			l = _strlen(s);
			if (s[l - 1] == d[0])
				s[l - 1] = '\0';

			l = _strlen(s);
			if (s[0] == d[0])
			{
				for (i = 0; i < l - 1; i++)
					s[i] = s[i + 1];
				s[l - 1] = '\0';
			}
		}
	}
}
