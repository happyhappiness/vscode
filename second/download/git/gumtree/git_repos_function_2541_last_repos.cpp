void relocate_gitdir(const char *path, const char *old_git_dir, const char *new_git_dir)
{
	if (rename(old_git_dir, new_git_dir) < 0)
		die_errno(_("could not migrate git directory from '%s' to '%s'"),
			old_git_dir, new_git_dir);

	connect_work_tree_and_git_dir(path, new_git_dir);
}