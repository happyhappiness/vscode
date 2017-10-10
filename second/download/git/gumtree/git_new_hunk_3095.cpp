		errno = exists_in_PATH(file) ? EACCES : ENOENT;
	else if (errno == ENOTDIR && !strchr(file, '/'))
		errno = ENOENT;
	return -1;
}

static const char **prepare_shell_cmd(struct argv_array *out, const char **argv)
{
	if (!argv[0])
		die("BUG: shell command is empty");

	if (strcspn(argv[0], "|&;<>()$`\\\"' \t\n*?[#~=%") != strlen(argv[0])) {
#ifndef GIT_WINDOWS_NATIVE
		argv_array_push(out, SHELL_PATH);
#else
		argv_array_push(out, "sh");
#endif
		argv_array_push(out, "-c");

		/*
		 * If we have no extra arguments, we do not even need to
		 * bother with the "$@" magic.
		 */
		if (!argv[1])
			argv_array_push(out, argv[0]);
		else
			argv_array_pushf(out, "%s \"$@\"", argv[0]);
	}

	argv_array_pushv(out, argv);
	return out->argv;
}

#ifndef GIT_WINDOWS_NATIVE
static int execv_shell_cmd(const char **argv)
{
	struct argv_array nargv = ARGV_ARRAY_INIT;
	prepare_shell_cmd(&nargv, argv);
	trace_argv_printf(nargv.argv, "trace: exec:");
	sane_execvp(nargv.argv[0], (char **)nargv.argv);
	argv_array_clear(&nargv);
	return -1;
}
#endif

#ifndef GIT_WINDOWS_NATIVE
static int child_notifier = -1;
