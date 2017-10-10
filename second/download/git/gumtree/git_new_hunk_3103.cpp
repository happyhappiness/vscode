	write_file(file_name.buf, "gitdir: %s",
		   relative_path(git_dir, real_work_tree, &rel_path));

	/* Update core.worktree setting */
	strbuf_reset(&file_name);
	strbuf_addf(&file_name, "%s/config", git_dir);
	git_config_set_in_file(file_name.buf, "core.worktree",
			       relative_path(real_work_tree, git_dir,
					     &rel_path));

	strbuf_release(&file_name);
	strbuf_release(&rel_path);
	free((void *)real_work_tree);
}
