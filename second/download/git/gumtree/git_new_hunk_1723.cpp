		const char *git_dir_parent = strrchr(git_dir, '/');
		if (git_dir_parent) {
			char *rel = xstrndup(git_dir, git_dir_parent - git_dir);
			git_work_tree_cfg = xstrdup(real_path(rel));
			free(rel);
		}
		if (!git_work_tree_cfg)
			git_work_tree_cfg = xgetcwd();
		if (work_tree)
			set_git_work_tree(work_tree);
		else
			set_git_work_tree(git_work_tree_cfg);
		if (access(get_git_work_tree(), X_OK))
			die_errno (_("Cannot access work tree '%s'"),
				   get_git_work_tree());
	}
	else {
		if (work_tree)
			set_git_work_tree(work_tree);
	}

	set_git_dir_init(git_dir, real_git_dir, 1);

	return init_db(template_dir, flags);
}
