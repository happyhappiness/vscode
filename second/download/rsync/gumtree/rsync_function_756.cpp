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
		if (verbose > 3) {
			/* Can't use rprintf because we've forked. */
			fprintf (stderr,
				 RSYNC_NAME ": execute socket program \"%s\"\n",
				 prog);
		}
		exit (system (prog));
	}
	close (fd[1]);
	return fd[0];
}