#include "ltg_hcilib.h"

bool    flag[FLAGSIZE];

static char	*get_path(char **env)
{
	char	*path = NULL;

	for (int i = 0; env[i]; i++)
	{
		if (!strncmp(env[i], "PATH=", 5))
		{
			path = env[i] + 5;
			break ;
		}
	}
	return (path);
}

static char	*hciconfig(char *path, char *adrr)
{
	char	*comand;

	if (!path || !adrr)
        return (NULL);
	if (!(comand =  ltg_seatchinparh(HCICONFIG, path)))
	{
		ft_putendl_fd("Error: finding hciconfig", STDERR_FILENO);
		ft_putendl_fd("Try to: sudo apt install hciconfig", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (hciup(comand) != EXIT_SUCCESS)
	{
		ft_putendl_fd("Error: hciconig", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	ft_strdel(&comand);
	if (!(comand =  ltg_seatchinparh(HCITOOL, path)))
	{
		ft_putendl_fd("Error: finding hcitool", STDERR_FILENO);
		ft_putendl_fd("Try to: sudo apt install hcitool", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (flag[WCL] == true && hcilewlclr(comand) != EXIT_SUCCESS)
	    exit(EXIT_FAILURE);
	if (hciaddwhitelist(comand, adrr))
		exit(EXIT_FAILURE);
    return (comand);
}

static bool validbdaddr(char *addr)
{
    char    flag = 0;
    int     i;

    for (i = 0; addr[i]; i++)
    {
        if (addr[i] >= 48 && addr[i] <= 57)
            continue ;
        if (addr[i] >= 65 && addr[i] <= 70)
            continue ;
        if (addr[i] == ':')
            flag++;
        else
        {
            ft_putendl_fd("Error: invalid device", STDERR_FILENO);
            return (false);
        }
    }
    if (flag == 5 && i == 17)
        return (true);
    else
    {
        ft_putendl_fd("Error: invalid device", STDERR_FILENO);
        return (false);
    }
}


static char *parsarg(int ac, char **av)
{
    char    *addr = NULL;

    for (int j = 0; j < FLAGSIZE; j++)
        flag[j] = false;
    for (int i = 1; i < ac; i++)
    {
        if (av[i][0] == '-')
        {
            if (!strcmp(av[i], "-wcl"))
                flag[WCL] = true;
            else if (!strcmp(av[i], "-reset"))
                flag[RESET] = true;
            else
            {
                ft_putstr_fd("Error: invalid options: ", STDERR_FILENO);
                ft_putendl_fd(av[i], STDERR_FILENO);
                return (NULL);
            }
        }
        else
        {
            if (addr)
            {
                ft_putendl_fd("Error: mast be only one device", STDERR_FILENO);
                return (NULL);
            }
            if (!validbdaddr(av[i]))
                return (NULL);
            addr = av[i];
        }
    }
    if (!addr)
    {
        ft_putstr_fd("Usag: ", STDOUT_FILENO);
        ft_putstr_fd(av[0], STDOUT_FILENO);
        ft_putendl_fd(" [options] <bdaddr>", STDOUT_FILENO);
    }
    return (addr);
}

void     sigmalhendl(int sig)
{
    if (sig == SIGINT)
    {
        if (scan != -1)
            if (kill(scan, SIGINT) != 0)
                ft_putendl_fd("Error: hci lescan does not sop", STDERR_FILENO);
        if (dump != -1)
            if (kill(dump, SIGINT) != 0)
                ft_putendl_fd("Error: hcidump does not sop", STDERR_FILENO);
        exit(EXIT_SUCCESS);
    }
}

int         main(int ac, char **av, char **env)
{
    char    *comand = NULL;
    char    *dumppath = NULL;
    char	*path = NULL;
    char    *addr = NULL;

    if (ac < 2)
    {
        ft_putstr_fd("Usag: ", STDOUT_FILENO);
        ft_putstr_fd(av[0], STDOUT_FILENO);
        ft_putendl_fd(" [options] <bdaddr>", STDOUT_FILENO);
    }
	if (getuid() != 0)
	{
		ft_putendl_fd("Error: premission denied", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
    if (!(path = get_path(env)))
    {
        ft_putendl_fd("Error: finding path", STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
    scan = -1;
    dump = -1;
    signal(SIGINT, sigmalhendl);
    signal(SIGCHLD, SIG_IGN);
    if (!(addr = parsarg(ac, av)) || !(comand = hciconfig(path, addr)))
        return (EXIT_FAILURE);
    if (!(dumppath =  ltg_seatchinparh(HCIDUMP, path)))
    {
        ft_putendl_fd("Error: finding hcidump", STDERR_FILENO);
        ft_putendl_fd("Try to: sudo apt install hcidump", STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
    hcidump(dumppath);
    hciscanwhitelist(comand);
    return (EXIT_SUCCESS);
}
