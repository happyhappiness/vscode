	int pid;
	int to_child_pipe[2];
	int from_child_pipe[2];

	if (pipe(to_child_pipe) < 0 ||
	    pipe(from_child_pipe) < 0) {
		fprintf(FERROR,"pipe: %s\n",strerror(errno));
		exit_cleanup(1);
	}


	pid = do_fork();
	if (pid < 0) {
		fprintf(FERROR,"fork: %s\n",strerror(errno));
		exit_cleanup(1);
	}

	if (pid == 0) {
		extern int am_sender;
		extern int am_server;
