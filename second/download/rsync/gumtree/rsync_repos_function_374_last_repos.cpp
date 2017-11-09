int glob_expand(const char *arg, char ***argv_p, int *argc_p, int *maxargs_p)
{
	int ret, save_argc;
	char *s;

	if (!arg) {
		if (glob.filt_buf)
			free(glob.filt_buf);
		free(glob.arg_buf);
		memset(&glob, 0, sizeof glob);
		return -1;
	}

	if (sanitize_paths)
		s = sanitize_path(NULL, arg, "", 0, SP_KEEP_DOT_DIRS);
	else {
		s = strdup(arg);
		if (!s)
			out_of_memory("glob_expand");
		clean_fname(s, CFN_KEEP_DOT_DIRS
			     | CFN_KEEP_TRAILING_SLASH
			     | CFN_COLLAPSE_DOT_DOT_DIRS);
	}

	ENSURE_MEMSPACE(glob.arg_buf, char, glob.absize, MAXPATHLEN);
	*glob.arg_buf = '\0';

	glob.argc = save_argc = *argc_p;
	glob.argv = *argv_p;
	glob.maxargs = *maxargs_p;

	ENSURE_MEMSPACE(glob.argv, char *, glob.maxargs, 100);

	glob_match(s, 0, -1);

	/* The arg didn't match anything, so add the failed arg to the list. */
	if (glob.argc == save_argc) {
		ENSURE_MEMSPACE(glob.argv, char *, glob.maxargs, glob.argc + 1);
		glob.argv[glob.argc++] = s;
		ret = 0;
	} else {
		free(s);
		ret = 1;
	}

	*maxargs_p = glob.maxargs;
	*argv_p = glob.argv;
	*argc_p = glob.argc;

	return ret;
}