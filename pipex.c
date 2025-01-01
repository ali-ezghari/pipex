/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezghari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 18:33:43 by aezghari          #+#    #+#             */
/*   Updated: 2024/12/28 12:02:47 by aezghari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	exec_parent(int *pipes, char **argv, char **env)
{
	int	out_fd;

	out_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (out_fd == -1)
		exit(128);
	close(pipes[1]);
	dup2(pipes[0], STDIN_FILENO);
	dup2(out_fd, STDOUT_FILENO);
	close(pipes[0]);
	close(out_fd);
	wait(NULL);
	execcmd(argv[3], env);
}

void	exec_child(int *pipes, char **argv, char **env)
{
	int	in_fd;

	in_fd = open(argv[1], O_RDONLY, 0777);
	if (in_fd == -1)
		exit_error(128);
	close(pipes[0]);
	dup2(in_fd, STDIN_FILENO);
	dup2(pipes[1], STDOUT_FILENO);
	close(in_fd);
	close(pipes[1]);
	execcmd(argv[2], env);
}

int	main(int argc, char **argv, char **env)
{
	int	pipes[2];
	int	child1;

	if (argc == 5)
	{
		if (access(argv[1], R_OK) == -1)
			exit_error(1);
		if (pipe(pipes) == -1)
			exit(0);
		child1 = fork();
		if (child1 == -1)
		{
			close(pipes[0]);
			close(pipes[1]);
			exit(0);
		}
		if (child1 == 0)
			exec_child(pipes, argv, env);
		else
			exec_parent(pipes, argv, env);
	}
	else
		custom_error("Error", "Invalid Number of Arguments", 1);
	return (0);
}
