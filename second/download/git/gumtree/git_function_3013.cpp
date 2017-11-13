static void git_config_raw(config_fn_t fn, void *data)
{
	if (git_config_with_options(fn, data, NULL, 1) < 0)
		/*
		 * git_config_with_options() normally returns only
		 * positive values, as most errors are fatal, and
		 * non-fatal potential errors are guarded by "if"
		 * statements that are entered only when no error is
		 * possible.
		 *
		 * If we ever encounter a non-fatal error, it means
		 * something went really wrong and we should stop
		 * immediately.
		 */
		die(_("unknown error occured while reading the configuration files"));
}