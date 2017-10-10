		/*
		 * Redirect the channel to write syscall error messages to
		 * before redirecting the process's stderr so that all die()
		 * in subsequent call paths use the parent's stderr.
		 */
		if (cmd->no_stderr || need_err) {
			child_err = dup(2);
			set_cloexec(child_err);
		}
		set_die_routine(die_child);
		set_error_routine(error_child);

		close(notify_pipe[0]);
		set_cloexec(notify_pipe[1]);
		child_notifier = notify_pipe[1];
		atexit(notify_parent);

