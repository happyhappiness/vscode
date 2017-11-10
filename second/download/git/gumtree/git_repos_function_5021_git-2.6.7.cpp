static const char *push_to_deploy(unsigned char *sha1,
				  struct argv_array *env,
				  const char *work_tree)
{
	const char *update_refresh[] = {
		"update-index", "-q", "--ignore-submodules", "--refresh", NULL
	};
	const char *diff_files[] = {
		"diff-files", "--quiet", "--ignore-submodules", "--", NULL
	};
	const char *diff_index[] = {
		"diff-index", "--quiet", "--cached", "--ignore-submodules",
		NULL, "--", NULL
	};
	const char *read_tree[] = {
		"read-tree", "-u", "-m", NULL, NULL
	};
	struct child_process child = CHILD_PROCESS_INIT;

	child.argv = update_refresh;
	child.env = env->argv;
	child.dir = work_tree;
	child.no_stdin = 1;
	child.stdout_to_stderr = 1;
	child.git_cmd = 1;
	if (run_command(&child))
		return "Up-to-date check failed";

	/* run_command() does not clean up completely; reinitialize */
	child_process_init(&child);
	child.argv = diff_files;
	child.env = env->argv;
	child.dir = work_tree;
	child.no_stdin = 1;
	child.stdout_to_stderr = 1;
	child.git_cmd = 1;
	if (run_command(&child))
		return "Working directory has unstaged changes";

	/* diff-index with either HEAD or an empty tree */
	diff_index[4] = head_has_history() ? "HEAD" : EMPTY_TREE_SHA1_HEX;

	child_process_init(&child);
	child.argv = diff_index;
	child.env = env->argv;
	child.no_stdin = 1;
	child.no_stdout = 1;
	child.stdout_to_stderr = 0;
	child.git_cmd = 1;
	if (run_command(&child))
		return "Working directory has staged changes";

	read_tree[3] = sha1_to_hex(sha1);
	child_process_init(&child);
	child.argv = read_tree;
	child.env = env->argv;
	child.dir = work_tree;
	child.no_stdin = 1;
	child.no_stdout = 1;
	child.stdout_to_stderr = 0;
	child.git_cmd = 1;
	if (run_command(&child))
		return "Could not update working tree to new HEAD";

	return NULL;
}