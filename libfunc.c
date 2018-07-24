#include "ltg_hcilib.h"

void	ft_bzero(void *s, size_t n)
{
    size_t i;

    i = 0;
    while (i < n)
    {
        ((char*)s)[i] = 0;
        i++;
    }
}

char	*ft_strcat(char *s1, const char *s2)
{
    int		i;
    int		j;

    i = 0;
    j = 0;
    while (s1[i])
        i++;
    while (s2[j])
    {
        s1[i] = s2[j];
        i++;
        j++;
    }
    s1[i] = 0;
    return (s1);
}

char	*ft_strcpy(char *dest, const char *src)
{
    int	i;

    i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

char	*ft_strdup(const char *s1)
{
    char	*s2;

    if (!s1)
        return (NULL);
    if (!(s2 = ft_strnew(ft_strlen(s1))))
        return (NULL);
    else
    {
        s2 = ft_strcpy(s2, s1);
        return (s2);
    }
}

char	*ft_strjoin(char const *s1, char const *s2)
{
    char *s;

    if (!s1 && !s2)
        return (NULL);
    if (!s1)
        return (ft_strdup(s2));
    if (!s2)
        return (ft_strdup(s1));
    if (!(s = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1)))
        return (NULL);
    s = ft_strcpy(s, s1);
    s = ft_strcat(s, s2);
    return (s);
}

size_t	ft_strlen(const char *s)
{
    size_t	i;

    i = 0;
    if (!s)
        return (i);
    while (s[i])
        i++;
    return (i);
}

int	ft_ln_w(char const *str, char c)
{
    char	*s;

    if (!*str)
        return (0);
    while (*str == c && *str)
        str++;
    s = (char *)str;
    while (*s != c && *s)
        s++;
    return (s - str);
}

void	ft_strdel(char **as)
{
    if (as && *as)
        ft_memdel((void **)as);
}


int	ft_nb_words(char const *str, char c)
{
    char	*p;
    int		cw;

    cw = 0;
    if (!*str)
        return (0);
    while (*str)
    {
        while (*str == c && *str)
            str++;
        p = (char *)str;
        while (*p != c && *p)
            p++;
        (*str != c && *str) ? cw++ : 0;
        str = p;
    }
    return (cw);
}

char	**ft_strsplit(char const *s, char c)
{
    char	**res;
    char	*s1;
    char	**s2;

    if (!s || !(res = malloc(sizeof(char*) * (ft_nb_words(s, c) + 1))))
        return (NULL);
    s2 = res;
    while (*s)
    {
        while (*s == c && *s && s++)
            ;
        if (*s)
        {
            if (!(s1 = malloc(sizeof(char) * ft_ln_w(s, c) + 1)))
                return (NULL);
            *res = s1;
            while (*s != c && *s && (*s1++ = *s++))
                ;
            *s1 = '\0';
            res++;
        }
    }
    *res = NULL;
    return (s2);
}


char	*ft_strnew(size_t size)
{
    char	*str;

    if ((str = (char *)malloc(size + 1)) == NULL)
        return (NULL);
    ft_bzero(str, (size + 1));
    return (str);
}

void	ft_memdel(void **ap)
{
    if (ap && *ap)
    {
        free(*ap);
        *ap = NULL;
    }
}

void	ft_putendl_fd(char const *s, int fd)
{
    if (s)
    {
        write(fd, s, ft_strlen(s));
    }
    write(fd, "\n", 1);
}

void	ft_putstr_fd(char const *s, int fd)
{
    if (s)
    {
        write(fd, s, ft_strlen(s));
    }
}
