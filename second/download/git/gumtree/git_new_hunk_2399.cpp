	}

	/* #3, #7, #11, #15, #19, #23, #27, #31 (see t1510) */
	if (work_tree_env)
		set_git_work_tree(work_tree_env);
	else if (is_bare_repository_cfg > 0) {
		if (git_work_tree_cfg) {
			/* #22.2, #30 */
			warning("core.bare and core.worktree do not make sense");
			work_tree_config_is_bogus = 1;
		}

		/* #18, #26 */
		set_git_dir(gitdirenv);
		free(gitfile);
		return NULL;
	}
