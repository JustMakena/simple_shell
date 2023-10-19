#ifndef _HEADER_
#define _HEADER_

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>

extern char **environ;

char *_getenv(const char *name);
int len_P(void);
char **_pathD(void);
char *existP(char *file);
void _printenv(char **s);

int _strstr(char *haystack, char *needle);
int exit_checker(char *com);
void f_h(char *com, char **av, char **env);
size_t letters_f(const char *file);
void file_mode(char **av, char **env);

void free_c(char *s);
void free_p(char **a);
void error_h(char *av, char *args);

int h_fork(char **args, char *s, char **l_com);
int h_forkEnd(char **args);
void sp_handler(char *com);
void non_ith(char *com, char **av, char **env);

char *_getline(void);
int sp_checker(char *com);
int _putchar(char c);
void myprintf(int n);
char *comments_h(char *com);

void choice_maker(char *com, char **av, char **env);
int se_colh(char *com, char **av, char **env);
void and_or_h(char *com, char **av, char **env, const char d[]);
int and_or_checker(char *com, const char d[]);
void final_and_or(char *com, char **av, char **env);

int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int _strcmpc(char *s1, const char *s2);
int _strcmp(char *s1, char *s2);
void remove_sl(char *s);

char *_strdup(char *s);
char *_strcat(char *dest, char *src);
char *_strcath(char *dest, char *src);
int _atoi(char *s);
void delete_letter(char *s, const char d[]);

int len_w(char *s, int i, const char d[]);
int size(char *s, const char d[]);
char **str_splt(char *ch, const char d[]);

void exit_handler(char **args, char *s, char **l_com, int n);
int cd_envh(char *args);
int whereToUnset(char *name);
int _unsetenv(char *name);

int env_size(void);
int whereToSet(char *name, char *value);
int change_value(char *name, char *value);
int add_env(char *name, char *value);
int _setenv(char *name, char *value, int overwrite);

int cd_home(void);
int cd_previous(void);
int cd_dir(char **args);
int cd_handler(char **args);

void handle_sigint(int sig);
void endSeCol(char *s);
int _strstr(char *haystack, char *needle);
char *existH(char **P, char *file);

#endif
