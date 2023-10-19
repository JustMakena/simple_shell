#include "main.h"

/**
 * len_w - len of a char
 * @s: the string
 * @i: point
 * @d: delimiter
 *
 * Return: the len
 */

int len_w(char *s, int i, const char d[])
{
	int j;
	int l = 0;

	if (s == NULL)
		return (0);
	for (j = i; s[j] != d[0] && s[j] != '\0'; j++)
		l++;
	return (l);
}

/**
 * size - size
 * @s: the string
 * @d: delimiter
 *
 * Return: number of word in the string delimited by d
 */

int size(char *s, const char d[])
{
	int l = 0;
	int i;

	if (s == NULL)
		return (0);
	for (i = 0; s[i] != '\0'; i++)
		if (s[i] == d[0])
			l++;
	return (l + 2);
}

/**
 * str_splt - spliting a string
 * @ch: the string
 * @d: delimiter
 *
 * Return: array of string
 */

char **str_splt(char *ch, const char d[])
{
	int i = 0, j = 0, t = -1, k = 0, w = 0, w_i = 0;
	char **tab = NULL;

	if (ch == NULL)
		return (NULL);
	tab = malloc(size(ch, d) * sizeof(*tab));
	if (tab == NULL)
		return (NULL);
	for (j = 0; j < size(ch, d); j++)
		tab[j] = NULL;
	for (i = 0; ch[i] != '\0'; i++)
	{
		if (ch[i] == d[0] || i == 0)
		{
			t++;
			if (i != 0)
				w_i = i + 1;
			w = len_w(ch, w_i, d);
			tab[t] = malloc(w + 1);
			if (tab[t] == NULL)
			{
				for (k = 0; k <= t; k++)
					free_c(tab[k]);
				free_p(tab);
				return (NULL);
			}
			if (i != 0)
				i++;
			for (j = 0; j < w; j++)
			{
				tab[t][j] = ch[i];
				i++;
			}
			i--;
			tab[t][j] = '\0';
		}
	}
	return (tab);
}
