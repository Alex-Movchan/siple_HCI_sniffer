#include "ltg_hcilib.h"

pid_t   dump;
pid_t   scan;

int     hciup(char *path)
{
    pid_t   pid;
    int     status = 0;

    if (!path)
        return (EXIT_FAILURE);
    if ((pid = fork()) < 0)
    {
        ft_putendl_fd("Error: forking", STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        ft_putstr_fd("Open and initialize HCI device: ", STDOUT_FILENO);
        close(STDOUT_FILENO);
        execl(path, path, "up", NULL);
    }
    else
        waitpid(pid, &status, 0);
    if (status == EXIT_SUCCESS)
        ft_putendl_fd(SUCCESS_MSG, STDOUT_FILENO);
    else
        ft_putendl_fd(FAILURE_MSG, STDOUT_FILENO);
    if (flag[RESET] == true && status == EXIT_SUCCESS)
    {
        if ((pid = fork()) < 0)
        {
            ft_putendl_fd("Error: forking", STDERR_FILENO);
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            ft_putstr_fd("Reset HCI device: ", STDOUT_FILENO);
            close(STDOUT_FILENO);
            execl(path, path, "reset", NULL);
        }
        else
            waitpid(pid, &status, 0);
        if (status == EXIT_SUCCESS)
            ft_putendl_fd(SUCCESS_MSG, STDOUT_FILENO);
        else
            ft_putendl_fd(FAILURE_MSG, STDOUT_FILENO);
    }
    return (status);
}

int     hcilewlclr(char *path)
{
    pid_t   pid;
    int     status = 0;

    if (!path)
        return (EXIT_FAILURE);
    if ((pid = fork()) < 0)
    {
        ft_putendl_fd("Error: forking", STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        ft_putstr_fd("Clear LE white list: ", STDOUT_FILENO);
        close(STDOUT_FILENO);
        execl(path, path, "lewlclr", NULL);
    }
    else
        waitpid(pid, &status, 0);
    if (status == EXIT_SUCCESS)
        ft_putendl_fd(SUCCESS_MSG, STDOUT_FILENO);
    else
        ft_putendl_fd(FAILURE_MSG, STDOUT_FILENO);
    return (status);
}

int     hciaddwhitelist(char *path, char *mack)
{
    pid_t   pid;
    int     status = 0;

    if (!path || !mack)
        return (EXIT_FAILURE);
    if ((pid = fork()) < 0)
    {
        ft_putendl_fd("Error forking", STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        ft_putstr_fd("Add device: ", STDOUT_FILENO);
        ft_putstr_fd(mack, STDOUT_FILENO);
        ft_putstr_fd(" to LE white list: ", STDOUT_FILENO);
        execl(path, path, "lewladd", mack, NULL);
    }
    else
        waitpid(pid, &status, 0);
    if (status == EXIT_SUCCESS)
        ft_putendl_fd(SUCCESS_MSG, STDOUT_FILENO);
    else
        ft_putendl_fd(FAILURE_MSG, STDOUT_FILENO);
    return (status);
}
