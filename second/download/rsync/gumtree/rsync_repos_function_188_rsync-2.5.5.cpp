pid_t local_child(int argc, char **argv,int *f_in,int *f_out)
{
	pid_t pid;
	int to_child_pipe[2];
	int from_child_pipe[2];
	extern int read_batch;  /* dw */

	if (fd_pair(to_child_pipe) < 0 ||
	    fd_pair(from_child_pipe) < 0) {
		rprintf(FERROR,"pipe: %s\n",strerror(errno));
		exit_cleanup(RERR_IPC);
	}


	pid = do_fork();
	if (pid == -1) {
		rprintf(FERROR,"fork: %s\n",strerror(errno));
		exit_cleanup(RERR_IPC);
	}

	if (pid == 0) {
		extern int am_sender;
		extern int am_server;

		am_sender = read_batch ? 0 : !am_sender;
		am_server = 1;		

		if (dup2(to_child_pipe[0], STDIN_FILENO) < 0 ||
		    close(to_child_pipe[1]) < 0 ||
		    close(from_child_pipe[0]) < 0 ||
		    dup2(from_child_pipe[1], STDOUT_FILENO) < 0) {
			rprintf(FERROR,"Failed to dup/close : %s\n",strerror(errno));
			exit_cleanup(RERR_IPC);
		}
		if (to_child_pipe[0] != STDIN_FILENO) close(to_child_pipe[0]);
		if (from_child_pipe[1] != STDOUT_FILENO) close(from_child_pipe[1]);
		start_server(STDIN_FILENO, STDOUT_FILENO, argc, argv);
	}

	if (close(from_child_pipe[1]) < 0 ||
	    close(to_child_pipe[0]) < 0) {
		rprintf(FERROR,"Failed to close : %s\n",strerror(errno));   
		exit_cleanup(RERR_IPC);
	}

	*f_in = from_child_pipe[0];
	*f_out = to_child_pipe[1];
  
	return pid;
}