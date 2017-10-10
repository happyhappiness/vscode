	const char *shallow_file;
	const char *replace_ref_base;

	git_dir = getenv(GIT_DIR_ENVIRONMENT);
	if (!git_dir) {
		if (!startup_info->have_repository)
			BUG("setup_git_env called without repository");
		git_dir = DEFAULT_GIT_DIR_ENVIRONMENT;
	}
	gitfile = read_gitfile(git_dir);
	git_dir = xstrdup(gitfile ? gitfile : git_dir);
	if (get_common_dir(&sb, git_dir))
		git_common_dir_env = 1;
