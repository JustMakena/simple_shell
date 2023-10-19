#include "main.h"

/**
 * _strlen - lenght
 * @s: lenght of s
 *
 * Return: an int
 */

int _strlen(char *s)
{
	int i = 0;

	if (s != NULL)
		for (i = 0; s[i] != '\0'; i++)
			;
	return (i);
}

/**
 * _strcpy - copying
 * @src: source
 * @dest: destination
 *
 * Return: char *
 */

char *_strcpy(char *dest, char *src)
{
	int i;

	if (dest == NULL || src == NULL)
		return (NULL);
	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcmpc - concatenation
 * @s1: first string
 * @s2: 2nd string
 *
 * Return: an integer
 */

int _strcmpc(char *s1, const char *s2)
{
	if (s1 == NULL && s2 == NULL)
		return (0);
	if (s1 == NULL || s2 == NULL)
		return (-1);
	while ((*s1) == (*s2) && (*s1) != '\0')
	{
		s1++;
		s2++;
	}

	if (((*s1) == '\0') && ((*s2) != '\0'))
		return (-1);
	if (((*s2) == '\0') && ((*s1) != '\0'))
		return (-1);

	if ((*s1) == '\0')
		s1--;
	if ((*s2) == '\0')
		s2--;

	return ((*s1) - (*s2));
}

/**
 * _strcmp - comparison
 * @s1: first string
 * @s2: 2nd string
 *
 * Return: an integer
 */

int _strcmp(char *s1, char *s2)
{
	if (s1 == NULL && s2 == NULL)
		return (0);
	if (s1 == NULL || s2 == NULL)
		return (-1);

	while ((*s1) == (*s2) && (*s1) != '\0')
	{
		s1++;
		s2++;
	}
	if (((*s1) == '\0') && ((*s2) != '\0'))
		return (-1);
	if (((*s2) == '\0') && ((*s1) != '\0'))
		return (-1);
	if ((*s1) == '\0')
		s1--;
	if ((*s2) == '\0')
		s2--;
	return ((*s1) - (*s2));
}

/**
 * remove_sl - remove \n
 * @s: the string
 *
 * Return: Nothing
 */

void remove_sl(char *s)
{
	int i, len = 0;

	len  = _strlen(s);
	if (s != NULL)
	{
		for (i = 0; s[i] != '\n' && i < len; i++)
			;
		if (s[i] == '\n')
			s[i] = '\0';
	}
}
