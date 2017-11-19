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