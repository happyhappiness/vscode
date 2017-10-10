	return new_path;
}

/* FIXME: move prefix to startup_info struct and get rid of this arg */
void trace_repo_setup(const char *prefix)
{
	static const char *key = "GIT_TRACE_SETUP";
	const char *git_work_tree;
	char cwd[PATH_MAX];

	if (!trace_want(key))
		return;

	if (!getcwd(cwd, PATH_MAX))
		die("Unable to get current working directory");

	if (!(git_work_tree = get_git_work_tree()))
		git_work_tree = "(null)";

	if (!prefix)
		prefix = "(null)";

	trace_printf_key(key, "setup: git_dir: %s\n", quote_crnl(get_git_dir()));
	trace_printf_key(key, "setup: worktree: %s\n", quote_crnl(git_work_tree));
	trace_printf_key(key, "setup: cwd: %s\n", quote_crnl(cwd));
	trace_printf_key(key, "setup: prefix: %s\n", quote_crnl(prefix));
}

int trace_want(const char *key)
{
	const char *trace = getenv(key);

	if (!trace || !strcmp(trace, "") ||
	    !strcmp(trace, "0") || !strcasecmp(trace, "false"))
		return 0;
	return 1;
}
