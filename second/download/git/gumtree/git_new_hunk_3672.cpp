		/* an explicit -m msg without --[no-]edit */
		return 0;

	if (e) {
		int v = git_config_maybe_bool(name, e);
		if (v < 0)
			die(_("Bad value '%s' in environment '%s'"), e, name);
		return v;
	}

	/* Use editor if stdin and stdout are the same and is a tty */
	return (!fstat(0, &st_stdin) &&
		!fstat(1, &st_stdout) &&
