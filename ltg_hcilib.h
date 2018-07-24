#ifndef LTG_HCILIB_H
#define LTG_HCILIB_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>
#include <wait.h>
#include <signal.h>
#include <fcntl.h>

#define HCICONFIG "hciconfig"
#define HCITOOL "hcitool"
#define HCIDUMP "hcidump"
#define LOG_FILE ".hci.log"
#define SUCCESS_MSG "\033[0;32mSUCCESS\033[0m"
#define FAILURE_MSG "\033[0;31mFAILURE\033[0m"
#define FLAGSIZE 5
#define WCL 0
#define RESET 1



extern pid_t    dump;
extern pid_t    scan;
extern bool     flag[FLAGSIZE];

void	ft_bzero(void *s, size_t n);
void	ft_memdel(void **ap);
void	ft_putendl_fd(char const *s, int fd);
void	ft_putstr_fd(char const *s, int fd);
char	*ft_strcat(char *s1, const char *s2);
void	ft_strdel(char **as);
char	*ft_strjoin(char const *s1, char const *s2);
void	dell_arrey(char **tmp);
size_t  ft_strlen(const char *s);
char	*ft_strnew(size_t size);
char	*ft_strdup(const char *s1);
char	*ft_strcpy(char *dest, const char *src);
char    *ltg_seatchinparh(char *name, char *path);
char	**ft_strsplit(char const *s, char c);
int     hciup(char *path);
int     hcilewlclr(char *path);
int     hciscanwhitelist(char *path);
int     hciaddwhitelist(char *path, char *mack);
int     hcidump(char *path);

#endif
