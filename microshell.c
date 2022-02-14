#include "microshell.h"


void	exec(char **cmd, int n, char **envp) {

	printf("cmd = %s\n", cmd[0]);
	cmd[n] = NULL;
	execve(cmd[0], cmd, envp);
	write(2, "microshell: execution failed :\n", 31);
	write(2, cmd[0], strlen(cmd[0]));
	write(2, "\n", 1);
	exit(1);
}

int	main(__attribute__ ((unused)) int argc, char **argv, char **envp) {

	int		i;
	pid_t	pid;
	// int		pipe[2];

	i = 0;
	while (argv[i]) {

		int	n;

		printf("i = %d\n", i);
		n = i;
		while (argv[n] && strcmp(argv[n], "|") && strcmp(argv[n], ";"))
			n++;
		pid = fork();
		if (pid == 0) {
			exec(argv, n, envp);
		}
		else {
			wait(NULL);
		}
		i++;
	}
	return 0;
}
