static const char *update_worktree(unsigned char *sha1)
{
	const char *retval;
	const char *work_tree = git_work_tree_cfg ? git_work_tree_cfg : "..";
	struct argv_array env = ARGV_ARRAY_INIT;

	if (is_bare_repository())
		return "denyCurrentBranch = updateInstead needs a worktree";

	argv_array_pushf(&env, "GIT_DIR=%s", absolute_path(get_git_dir()));

	if (!find_hook(push_to_checkout_hook))
		retval = push_to_deploy(sha1, &env, work_tree);
	else
		retval = push_to_checkout(sha1, &env, work_tree);

	argv_array_clear(&env);
	return retval;
}