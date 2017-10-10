		*argv = new_argv;
		*argcp += count - 1;

		ret = 1;
	}

	restore_env(0);

	errno = saved_errno;

	return ret;
}

