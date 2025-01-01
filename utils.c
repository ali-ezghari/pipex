/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezghari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 18:33:50 by aezghari          #+#    #+#             */
/*   Updated: 2024/12/28 11:24:52 by aezghari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*fullpath;
	int		i;

	i = 0;
	while (env[i] && !ft_strnstr(env[i], "PATH=", 5))
		i++;
	if (!env[i] || !ft_strnstr(env[i], "PATH=", 5))
		custom_error("Error", "a Problem in the Environment", 1);
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		exit(EXIT_FAILURE);
	i = -1;
	while (paths[++i])
	{
		fullpath = ft_strjoin(paths[i], cmd);
		if (access(fullpath, X_OK) == 0)
		{
			free_all(paths, NULL, NULL);
			return (fullpath);
		}
		free(fullpath);
	}
	free_all(paths, NULL, NULL);
	return (custom_error(cmd + 1, "Command not found", 127));
}

void	execcmd(char *cmd_with_flags, char **env)
{
	char	**cmdarr;
	char	*cmd;
	char	*path;

	cmdarr = ft_split(cmd_with_flags, ' ');
	if (!cmdarr)
		exit(EXIT_FAILURE);
	cmd = ft_strjoin("/", cmdarr[0]);
	if (!cmd)
	{
		free_all(cmdarr, NULL, NULL);
		exit(EXIT_FAILURE);
	}
	if (execve(cmd, cmdarr, env) == -1)
	{
		path = find_path(cmd, env);
		if (!path)
		{
			free_all(cmdarr, cmd, NULL);
			exit(EXIT_FAILURE);
		}
		execve(path, cmdarr, env);
	}
	free_all(cmdarr, cmd, path);
	exit(EXIT_FAILURE);
}

void	free_all(char **tab, char *str1, char *str2)
{
	int	i;

	i = 0;
	if (tab != NULL)
	{
		while (tab[i] != NULL)
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
	if (str1 != NULL)
	{
		free(str1);
	}
	if (str2 != NULL)
	{
		free(str2);
	}
}

void	exit_error(int status)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	if (status >= 1)
	{
		exit(status);
	}
}

char	*custom_error(char *header, char *msg, int status)
{
	ft_putstr_fd(header, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	if (status >= 1)
	{
		exit(status);
	}
	return (NULL);
}
