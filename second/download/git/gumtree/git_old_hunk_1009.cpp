	struct strbuf sb = STRBUF_INIT;
	const char *gitfile;
	const char *shallow_file;
	const char *replace_ref_base;

	git_dir = getenv(GIT_DIR_ENVIRONMENT);
	if (!git_dir)
		git_dir = DEFAULT_GIT_DIR_ENVIRONMENT;
	gitfile = read_gitfile(git_dir);
	git_dir = xstrdup(gitfile ? gitfile : git_dir);
	if (get_common_dir(&sb, git_dir))
		git_common_dir_env = 1;
	git_common_dir = strbuf_detach(&sb, NULL);
	git_object_dir = git_path_from_env(DB_ENVIRONMENT, git_common_dir,
