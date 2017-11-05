void connect_work_tree_and_git_dir(const char *work_tree_, const char *git_dir_)
{
	struct strbuf gitfile_sb = STRBUF_INIT;
	struct strbuf cfg_sb = STRBUF_INIT;
	struct strbuf rel_path = STRBUF_INIT;
	char *git_dir, *work_tree;

	/* Prepare .git file */
	strbuf_addf(&gitfile_sb, "%s/.git", work_tree_);
	if (safe_create_leading_directories_const(gitfile_sb.buf))
		die(_("could not create directories for %s"), gitfile_sb.buf);

	/* Prepare config file */
	strbuf_addf(&cfg_sb, "%s/config", git_dir_);
	if (safe_create_leading_directories_const(cfg_sb.buf))
		die(_("could not create directories for %s"), cfg_sb.buf);

	git_dir = real_pathdup(git_dir_, 1);
	work_tree = real_pathdup(work_tree_, 1);

	/* Write .git file */
	write_file(gitfile_sb.buf, "gitdir: %s",
		   relative_path(git_dir, work_tree, &rel_path));
	/* Update core.worktree setting */
	git_config_set_in_file(cfg_sb.buf, "core.worktree",
			       relative_path(work_tree, git_dir, &rel_path));

	strbuf_release(&gitfile_sb);
	strbuf_release(&cfg_sb);
	strbuf_release(&rel_path);
	free(work_tree);
	free(git_dir);
}