pid_t local_child(int argc, char **argv, int *f_in, int *f_out,
		  int (*child_main)(int, char*[]))
{
	pid_t pid;
	int to_child_pipe[2];
	int from_child_pipe[2];

	/* The parent process is always the sender for a local rsync. */
	assert(am_sender);

	if (fd_pair(to_child_pipe) < 0 ||
	    fd_pair(from_child_pipe) < 0) {
		rsyserr(FERROR, errno, "pipe");
		exit_cleanup(RERR_IPC);
	}

	pid = do_fork();
	if (pid == -1) {
		rsyserr(FERROR, errno, "fork");
		exit_cleanup(RERR_IPC);
	}

	if (pid == 0) {
		am_sender = 0;
		am_server = 1;
		filesfrom_fd = -1;
		munge_symlinks = 0; /* Each side needs its own option. */
		chmod_modes = NULL; /* Let the sending side handle this. */

		/* Let the client side handle this. */
		if (logfile_name) {
			logfile_name = NULL;
			logfile_close();
		}

		if (remote_option_cnt) {
			int rc = remote_option_cnt + 1;
			const char **rv = remote_options;
			if (!parse_arguments(&rc, &rv)) {
				option_error();
				exit_cleanup(RERR_SYNTAX);
			}
		}

		if (dup2(to_child_pipe[0], STDIN_FILENO) < 0 ||
		    close(to_child_pipe[1]) < 0 ||
		    close(from_child_pipe[0]) < 0 ||
		    dup2(from_child_pipe[1], STDOUT_FILENO) < 0) {
			rsyserr(FERROR, errno, "Failed to dup/close");
			exit_cleanup(RERR_IPC);
		}
		if (to_child_pipe[0] != STDIN_FILENO)
			close(to_child_pipe[0]);
		if (from_child_pipe[1] != STDOUT_FILENO)
			close(from_child_pipe[1]);
#ifdef ICONV_CONST
		setup_iconv();
#endif
		child_main(argc, argv);
	}

	if (close(from_child_pipe[1]) < 0 ||
	    close(to_child_pipe[0]) < 0) {
		rsyserr(FERROR, errno, "Failed to close");
		exit_cleanup(RERR_IPC);
	}

	*f_in = from_child_pipe[0];
	*f_out = to_child_pipe[1];

	return pid;
}