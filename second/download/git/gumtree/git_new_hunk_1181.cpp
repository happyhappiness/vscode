		 * mimics the exit code that a POSIX shell would report for
		 * a program that died from this signal.
		 */
		code += 128;
	} else if (WIFEXITED(status)) {
		code = WEXITSTATUS(status);
	} else {
		error("waitpid is confused (%s)", argv0);
	}

	clear_child_for_cleanup(pid);

