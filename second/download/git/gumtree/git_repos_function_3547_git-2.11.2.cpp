static void read_early_config(config_fn_t cb, void *data)
{
	git_config_with_options(cb, data, NULL, 1);

	/*
	 * Note that this is a really dirty hack that does the wrong thing in
	 * many cases. The crux of the problem is that we cannot run
	 * setup_git_directory() early on in git's setup, so we have no idea if
	 * we are in a repository or not, and therefore are not sure whether
	 * and how to read repository-local config.
	 *
	 * So if we _aren't_ in a repository (or we are but we would reject its
	 * core.repositoryformatversion), we'll read whatever is in .git/config
	 * blindly. Similarly, if we _are_ in a repository, but not at the
	 * root, we'll fail to find .git/config (because it's really
	 * ../.git/config, etc). See t7006 for a complete set of failures.
	 *
	 * However, we have historically provided this hack because it does
	 * work some of the time (namely when you are at the top-level of a
	 * valid repository), and would rarely make things worse (i.e., you do
	 * not generally have a .git/config file sitting around).
	 */
	if (!startup_info->have_repository) {
		struct git_config_source repo_config;

		memset(&repo_config, 0, sizeof(repo_config));
		repo_config.file = ".git/config";
		git_config_with_options(cb, data, &repo_config, 1);
	}
}