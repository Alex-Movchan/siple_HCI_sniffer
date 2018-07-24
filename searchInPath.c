#include "ltg_hcilib.h"

char	*file_in_path(char *name, char *path)
{
	char	*res = NULL;
	char	*buff = NULL;

	if (!name || !path)
		return (res);
	if (path[ft_strlen(path)] != '/')
		buff = ft_strjoin(path, "/");
	else
		buff = ft_strdup(path);
	res = ft_strjoin(buff, name);
	ft_strdel(&buff);
	return (res);
}

void	dell_arrey(char **tmp)
{
	for (int i = 0; tmp[i]; i++)
		ft_strdel(&tmp[i]);
	free(tmp);
}

char	*ltg_seatchinparh(char *name, char *path)
{
	char		**tmp = NULL;
	char		*res = NULL;
	DIR		*ptr = NULL;
	struct dirent	*dir = NULL;

	if (!name || !path)
		return (res);
	if (!(tmp = ft_strsplit(path, ':')))
		return (res);
	for (int i = 0; tmp[i]; i++)
	{
		if (!(ptr = opendir(tmp[i])))
		{
			ft_putstr_fd("Error: opening dir: ", STDERR_FILENO);
			ft_putendl_fd(tmp[i], STDERR_FILENO);
			dell_arrey(tmp);
			exit(EXIT_FAILURE);
		}
		while ((dir = readdir(ptr)))
		{
			if (dir->d_name[0] == '.')
				continue;
			if (!strcmp(dir->d_name, name))
			{
				res = file_in_path(name, tmp[i]);
				break;
			}
		}
		closedir(ptr);
		if (res)
			break;
	}
	dell_arrey(tmp);
	return (res);
}
