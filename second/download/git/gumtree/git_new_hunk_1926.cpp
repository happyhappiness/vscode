
/* FIXME: move prefix to startup_info struct and get rid of this arg */
void trace_repo_setup(const char *prefix)
{
	static struct trace_key key = TRACE_KEY_INIT(SETUP);
	const char *git_work_tree;
	char *cwd;

	if (!trace_want(&key))
		return;

	cwd = xgetcwd();

	if (!(git_work_tree = get_git_work_tree()))
		git_work_tree = "(null)";

	if (!prefix)
		prefix = "(null)";

	trace_printf_key(&key, "setup: git_dir: %s\n", quote_crnl(get_git_dir()));
	trace_printf_key(&key, "setup: worktree: %s\n", quote_crnl(git_work_tree));
	trace_printf_key(&key, "setup: cwd: %s\n", quote_crnl(cwd));
	trace_printf_key(&key, "setup: prefix: %s\n", quote_crnl(prefix));

	free(cwd);
}

int trace_want(struct trace_key *key)
{
	return !!get_trace_fd(key);
}
