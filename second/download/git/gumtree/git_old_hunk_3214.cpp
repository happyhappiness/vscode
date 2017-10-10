		*argv = new_argv;
		*argcp += count - 1;

		ret = 1;
	}

	if (subdir && chdir(subdir))
		die_errno("Cannot change to '%s'", subdir);

	errno = saved_errno;

	return ret;
}

