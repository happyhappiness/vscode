static void repo_read_config(struct repository *repo)
{
	struct config_options opts;

	opts.respect_includes = 1;
	opts.commondir = repo->commondir;
	opts.git_dir = repo->gitdir;

	if (!repo->config)
		repo->config = xcalloc(1, sizeof(struct config_set));
	else
		git_configset_clear(repo->config);

	git_configset_init(repo->config);

	if (config_with_options(config_set_callback, repo->config, NULL, &opts) < 0)
		/*
		 * config_with_options() normally returns only
		 * zero, as most errors are fatal, and
		 * non-fatal potential errors are guarded by "if"
		 * statements that are entered only when no error is
		 * possible.
		 *
		 * If we ever encounter a non-fatal error, it means
		 * something went really wrong and we should stop
		 * immediately.
		 */
		die(_("unknown error occurred while reading the configuration files"));
}