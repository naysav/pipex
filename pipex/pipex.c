#include "pipex.h"
#include "libft/libft.h"
#include <stdio.h>

char	*get_path(char *cmd, char **env)
{
	char	*path;
	char	*dir;
	char	*bin;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp("PATH=", env[i], 5))
		i++;
	if (!env[i])
		return (cmd);
	path = env[i] + 5;
	while (path && find_nbr_char(path, ':') > -1)
	{
		dir = dup_up2_n(path, find_nbr_char(path, ':'));
		bin = path_join(dir, cmd);
		free(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		path += find_nbr_char(path, ':') + 1;
	}
	return (cmd);
}

void	exec(char *cmd, char **env)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (find_nbr_char(args[0], '/') > -1)
		path = args[0];
	else
		path = get_path(args[0], env);
	execve(path, args, env);
	display_error("Error: check your first or second command.\n");
}

void	redir(char *cmd, char **env, int in_fd)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == -1)
		display_error("Error: fork did not cope.\n");
	if (pid)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN);
		waitpid(pid, NULL, 0);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		if (in_fd == STDIN)
			exit(1);
		else
			exec(cmd, env);
	}
}

int	main(int argc, char **argv, char **env)
{
	int	in_fd;
	int	out_fd;

	if (argc != 5)
		display_error("Error: wrong number of arguments.\n");
	in_fd = open(argv[1], O_RDONLY);
	if (in_fd == -1)
		display_error("Error: open first file failed.\n");
	out_fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (out_fd == -1)
		display_error("Error: open second file failed.\n");
	dup2(in_fd, STDIN);
	dup2(out_fd, STDOUT);
	redir(argv[2], env, in_fd);
	exec(argv[3], env);
	return (1);
}
