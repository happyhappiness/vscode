		setenv(GIT_WORK_TREE_ENVIRONMENT, ".", 1);

	set_git_dir(remove_leading_path(git_dir, work_tree));
	initialized = 1;
}

static int check_repo_format(const char *var, const char *value, void *cb)
{
	if (strcmp(var, "core.repositoryformatversion") == 0)
		repository_format_version = git_config_int(var, value);
	else if (strcmp(var, "core.sharedrepository") == 0)
		shared_repository = git_config_perm(var, value);
	return 0;
}

static int check_repository_format_gently(const char *gitdir, int *nongit_ok)
{
	struct strbuf sb = STRBUF_INIT;
	const char *repo_config;
	config_fn_t fn;
	int ret = 0;

	if (get_common_dir(&sb, gitdir))
		fn = check_repo_format;
	else
		fn = check_repository_format_version;
	strbuf_addstr(&sb, "/config");
	repo_config = sb.buf;

	/*
	 * git_config() can't be used here because it calls git_pathdup()
	 * to get $GIT_CONFIG/config. That call will make setup_git_env()
	 * set git_dir to ".git".
	 *
	 * We are in gitdir setup, no git dir has been found useable yet.
	 * Use a gentler version of git_config() to check if this repo
	 * is a good one.
	 */
	git_config_early(fn, NULL, repo_config);
	if (GIT_REPO_VERSION < repository_format_version) {
		if (!nongit_ok)
			die ("Expected git repo version <= %d, found %d",
			     GIT_REPO_VERSION, repository_format_version);
		warning("Expected git repo version <= %d, found %d",
			GIT_REPO_VERSION, repository_format_version);
		warning("Please upgrade Git");
		*nongit_ok = -1;
		ret = -1;
	}
	strbuf_release(&sb);
	return ret;
}

static void update_linked_gitdir(const char *gitfile, const char *gitdir)
{
	struct strbuf path = STRBUF_INIT;
	struct stat st;

	strbuf_addf(&path, "%s/gitfile", gitdir);
	if (stat(path.buf, &st) || st.st_mtime + 24 * 3600 < time(NULL))
		write_file(path.buf, 0, "%s\n", gitfile);
	strbuf_release(&path);
}

/*
 * Try to read the location of the git directory from the .git file,
 * return path to git directory if found.
 */
