/* Update gitfile and core.worktree setting to connect work tree and git dir */
void connect_work_tree_and_git_dir(const char *work_tree, const char *git_dir)
{
	struct strbuf file_name = STRBUF_INIT;
	struct strbuf rel_path = STRBUF_INIT;
	const char *real_work_tree = xstrdup(real_path(work_tree));
	FILE *fp;

	/* Update gitfile */
	strbuf_addf(&file_name, "%s/.git", work_tree);
	fp = fopen(file_name.buf, "w");
	if (!fp)
		die(_("Could not create git link %s"), file_name.buf);
	fprintf(fp, "gitdir: %s\n", relative_path(git_dir, real_work_tree,
						  &rel_path));
	fclose(fp);

	/* Update core.worktree setting */
	strbuf_reset(&file_name);
	strbuf_addf(&file_name, "%s/config", git_dir);
	if (git_config_set_in_file(file_name.buf, "core.worktree",
				   relative_path(real_work_tree, git_dir,
