#include "microshell.h"
#include <stdio.h>
void	exec_bin(char **argv, int n, char **envp) {

	argv[n] = NULL;
	execve(argv[0], argv, envp);
	write(2, "microshell: execution failed : ", 31);
	write(2, argv[0], strlen(argv[0]));
	write(2, "\n", 1);
	exit(1);
}

int	exec_cd(char **argv, int i) {

	// if (strcmp(argv[0], "cd") != 0)
	// 	return 0;
	if (i != 2) {
		write(2, "cd: too many arguments\n", 23);
		return 1;
	}
	else if (chdir(argv[1]) != 0) {
		write(2, "cd: no such file or directory : ", 32);
		write(2, argv[1], strlen(argv[1]));
		write(2, "\n", 1);
		return 1;
	}
	printf("direectory changed\n");
	return 0;
}

int	main(__attribute__ ((unused)) int argc, char **argv, char **envp) {

	int		i;
	pid_t	pid;
	int		fd[2];
	int		tmp_fd;

	i = 0;
	tmp_fd = dup(STDIN_FILENO);
	while (argv[i]) {

		argv = &argv[i + 1];
		while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
			i++;
		if (strcmp(argv[0], "cd") == 0)
			exec_cd(argv, i);
		else if (strcmp(argv[i], "|") == 0) {
			pipe(fd);
			pid = fork();
			if (pid == 0) {
				dup2(tmp_fd, STDIN_FILENO);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
				exec_bin(argv, i, envp);
			}
			else {
				close(fd[1]);
				close(tmp_fd);
				wait(NULL);
				tmp_fd = dup(fd[0]);
				close(fd[0]);
			}
		}
		else {
			pid = fork();
			if (pid == 0) {
				exec_bin(argv, i, envp);
			}
			else {
				wait(NULL);
			}
		}
	}
	return 0;
}
