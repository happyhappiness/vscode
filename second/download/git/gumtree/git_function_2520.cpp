static int default_edit_option(void)
{
	static const char name[] = "GIT_MERGE_AUTOEDIT";
	const char *e = getenv(name);
	struct stat st_stdin, st_stdout;

	if (have_message)
		/* an explicit -m msg without --[no-]edit */
		return 0;

	if (e) {
		int v = git_config_maybe_bool(name, e);
		if (v < 0)
			die("Bad value '%s' in environment '%s'", e, name);
		return v;
	}

	/* Use editor if stdin and stdout are the same and is a tty */
	return (!fstat(0, &st_stdin) &&
		!fstat(1, &st_stdout) &&
		isatty(0) && isatty(1) &&
		st_stdin.st_dev == st_stdout.st_dev &&
		st_stdin.st_ino == st_stdout.st_ino &&
		st_stdin.st_mode == st_stdout.st_mode);
}