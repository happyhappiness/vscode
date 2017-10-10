	untracked_cache_invalidate_path(istate, path);
}

/* Update gitfile and core.worktree setting to connect work tree and git dir */
void connect_work_tree_and_git_dir(const char *work_tree_, const char *git_dir_)
{
	struct strbuf file_name = STRBUF_INIT;
	struct strbuf rel_path = STRBUF_INIT;
	char *git_dir = real_pathdup(git_dir_, 1);
	char *work_tree = real_pathdup(work_tree_, 1);

	/* Update gitfile */
	strbuf_addf(&file_name, "%s/.git", work_tree);
	write_file(file_name.buf, "gitdir: %s",
		   relative_path(git_dir, work_tree, &rel_path));

	/* Update core.worktree setting */
	strbuf_reset(&file_name);
	strbuf_addf(&file_name, "%s/config", git_dir);
	git_config_set_in_file(file_name.buf, "core.worktree",
			       relative_path(work_tree, git_dir, &rel_path));

	strbuf_release(&file_name);
	strbuf_release(&rel_path);
	free(work_tree);
	free(git_dir);
}

/*
