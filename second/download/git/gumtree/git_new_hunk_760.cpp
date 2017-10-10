	if (run_command(&cp))
		return 0;

	return 1;
}

/*
 * Check if it is a bad idea to remove a submodule, i.e. if we'd lose data
 * when doing so.
 *
 * Return 1 if we'd lose data, return 0 if the removal is fine,
 * and negative values for errors.
 */
int bad_to_remove_submodule(const char *path, unsigned flags)
{
	ssize_t len;
	struct child_process cp = CHILD_PROCESS_INIT;
	struct strbuf buf = STRBUF_INIT;
	int ret = 0;

	if (!file_exists(path) || is_empty_dir(path))
		return 0;

	if (!submodule_uses_gitfile(path))
		return 1;

	argv_array_pushl(&cp.args, "status", "--porcelain",
				   "--ignore-submodules=none", NULL);

	if (flags & SUBMODULE_REMOVAL_IGNORE_UNTRACKED)
		argv_array_push(&cp.args, "-uno");
	else
		argv_array_push(&cp.args, "-uall");

	if (!(flags & SUBMODULE_REMOVAL_IGNORE_IGNORED_UNTRACKED))
		argv_array_push(&cp.args, "--ignored");

	prepare_submodule_repo_env(&cp.env_array);
	cp.git_cmd = 1;
	cp.no_stdin = 1;
	cp.out = -1;
	cp.dir = path;
	if (start_command(&cp)) {
		if (flags & SUBMODULE_REMOVAL_DIE_ON_ERROR)
			die(_("could not start 'git status in submodule '%s'"),
				path);
		ret = -1;
		goto out;
	}

	len = strbuf_read(&buf, cp.out, 1024);
	if (len > 2)
		ret = 1;
	close(cp.out);

	if (finish_command(&cp)) {
		if (flags & SUBMODULE_REMOVAL_DIE_ON_ERROR)
			die(_("could not run 'git status in submodule '%s'"),
				path);
		ret = -1;
	}
out:
	strbuf_release(&buf);
	return ret;
}

static int find_first_merges(struct object_array *result, const char *path,
		struct commit *a, struct commit *b)
{
	int i, j;
