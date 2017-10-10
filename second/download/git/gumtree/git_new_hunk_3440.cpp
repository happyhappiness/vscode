			exit(127);
		} else {
			die_errno("cannot exec '%s'", cmd->argv[0]);
		}
	}
	if (cmd->pid < 0)
		error_errno("cannot fork() for %s", cmd->argv[0]);
	else if (cmd->clean_on_exit)
		mark_child_for_cleanup(cmd->pid);

	/*
	 * Wait for child's execvp. If the execvp succeeds (or if fork()
	 * failed), EOF is seen immediately by the parent. Otherwise, the
