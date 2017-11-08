void _exit_cleanup(int code, const char *file, int line)
{
	int ocode = code;
	static int inside_cleanup = 0;

	if (inside_cleanup > 10) {
		/* prevent the occasional infinite recursion */
		return;
	}
	inside_cleanup++;

	SIGACTION(SIGUSR1, SIG_IGN);
	SIGACTION(SIGUSR2, SIG_IGN);

	if (verbose > 3) {
		rprintf(FINFO,"_exit_cleanup(code=%d, file=%s, line=%d): entered\n",
			code, file, line);
	}

	if (cleanup_child_pid != -1) {
		int status;
		if (wait_process(cleanup_child_pid, &status, WNOHANG)
		 == cleanup_child_pid) {
			status = WEXITSTATUS(status);
			if (status > code)
				code = status;
		}
	}

	if (cleanup_got_literal && cleanup_fname && keep_partial
	    && handle_partial_dir(cleanup_new_fname, PDIR_CREATE)) {
		char *fname = cleanup_fname;
		cleanup_fname = NULL;
		if (cleanup_fd_r != -1)
			close(cleanup_fd_r);
		if (cleanup_fd_w != -1) {
			flush_write_file(cleanup_fd_w);
			close(cleanup_fd_w);
		}
		finish_transfer(cleanup_new_fname, fname, NULL,
				cleanup_file, 0, !partial_dir);
	}
	io_flush(FULL_FLUSH);
	if (cleanup_fname)
		do_unlink(cleanup_fname);
	if (code)
		kill_all(SIGUSR1);
	if (cleanup_pid && cleanup_pid == getpid()) {
		char *pidf = lp_pid_file();
		if (pidf && *pidf)
			unlink(lp_pid_file());
	}

	if (code == 0) {
		if (io_error & IOERR_DEL_LIMIT)
			code = RERR_DEL_LIMIT;
		if (io_error & IOERR_VANISHED)
			code = RERR_VANISHED;
		if (io_error & IOERR_GENERAL || log_got_error)
			code = RERR_PARTIAL;
	}

	if (code)
		log_exit(code, file, line);

	if (verbose > 2) {
		rprintf(FINFO,"_exit_cleanup(code=%d, file=%s, line=%d): about to call exit(%d)\n",
			ocode, file, line, code);
	}

	close_all();
	exit(code);
}