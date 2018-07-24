#include "ltg_hcilib.h"

int     hciscanwhitelist(char *path)
{
    int     status = 0;

    if (!path)
        return (EXIT_FAILURE);
    if ((scan = fork()) < 0)
    {
        ft_putendl_fd("Error: forking", STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
    else if (scan == 0)
    {
        close(STDOUT_FILENO);
        execl(path, path, "lescan", "--whitelist", "--duplicates", NULL);
    }
    else
        waitpid(scan, &status, 0);
    return (status);
}


int    hcidump(char *path)
{
    int     status = 0;
    int     fd;

    if (!path)
        return (EXIT_FAILURE);
    if ((dump = fork()) < 0)
    {
        ft_putendl_fd("Error: forking", STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
    else if (dump == 0)
    {
        //fd = open(LOG_FILE, O_RDWR | O_CREAT | O_TRUNC); ????
        //close(fd);
        execl(path, path, "--raw", NULL);
    }
    else
        waitpid(dump, &status, WNOHANG);
    return (status);
}