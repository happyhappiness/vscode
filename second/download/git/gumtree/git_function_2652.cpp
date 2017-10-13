void connect_work_tree_and_git_dir(const char *work_tree, const char *git_dir)
{
	struct strbuf file_name = STRBUF_INIT;
	struct strbuf rel_path = STRBUF_INIT;
	const char *real_work_tree = xstrdup(real_path(work_tree));

	/* Update gitfile */
	strbuf_addf(&file_name, "%s/.git", work_tree);
	write_file(file_name.buf, "gitdir: %s",
		   relative_path(git_dir, real_work_tree, &rel_path));

	/* Update core.worktree setting */
	strbuf_reset(&file_name);
	strbuf_addf(&file_name, "%s/config", git_dir);
	if (git_config_set_in_file(file_name.buf, "core.worktree",
				   relative_path(real_work_tree, git_dir,
						 &rel_path)))
		die(_("Could not set core.worktree in %s"),
		    file_name.buf);

	strbuf_release(&file_name);
	strbuf_release(&rel_path);
	free((void *)real_work_tree);
}