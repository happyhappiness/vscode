		;	/* nothing */
	if (in_signal)
		return 0;

	if (waiting < 0) {
		failed_errno = errno;
		error_errno("waitpid for %s failed", argv0);
	} else if (waiting != pid) {
		error("waitpid is confused (%s)", argv0);
	} else if (WIFSIGNALED(status)) {
		code = WTERMSIG(status);
		if (code != SIGINT && code != SIGQUIT && code != SIGPIPE)
			error("%s died of signal %d", argv0, code);
