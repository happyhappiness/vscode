static void git_config_raw(config_fn_t fn, void *data)
{
	struct config_options opts = {0};

	opts.respect_includes = 1;
	if (git_config_with_options(fn, data, NULL, &opts) < 0)
		/*
		 * git_config_with_options() normally returns only
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