	if (fd[1] != -1) close(fd[1]);
	if (listener != -1) close(listener);
	return -1;
}


/*******************************************************************
run a program on a local tcp socket, this is used to launch smbd
when regression testing
the return value is a socket which is attached to a subprocess
running "prog". stdin and stdout are attached. stderr is left
attached to the original stderr
 ******************************************************************/
int sock_exec(const char *prog)
{
	int fd[2];
	if (socketpair_tcp(fd) != 0) {
		rprintf (FERROR, RSYNC_NAME
			 ": socketpair_tcp failed (%s)\n",
			 strerror(errno));
		return -1;
	}
	if (fork() == 0) {
		close(fd[0]);
		close(0);
		close(1);
		dup(fd[1]);
		dup(fd[1]);
		if (verbose > 3)
			fprintf (stderr,
				 RSYNC_NAME ": execute socket program \"%s\"\n",
				 prog);
		exit (system (prog));
	}
	close (fd[1]);
	return fd[0];
}

