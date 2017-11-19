static int grep_cmd_config(const char *var, const char *value, void *cb)
{
	int st = grep_config(var, value, cb);
	if (git_color_default_config(var, value, cb) < 0)
		st = -1;

	if (!strcmp(var, "grep.threads")) {
		num_threads = git_config_int(var, value);
		if (num_threads < 0)
			die(_("invalid number of threads specified (%d) for %s"),
			    num_threads, var);
#ifdef NO_PTHREADS
		else if (num_threads && num_threads != 1) {
			/*
			 * TRANSLATORS: %s is the configuration
			 * variable for tweaking threads, currently
			 * grep.threads
			 */
			warning(_("no threads support, ignoring %s"), var);
			num_threads = 0;
		}
#endif
	}

	if (!strcmp(var, "submodule.recurse"))
		recurse_submodules = git_config_bool(var, value);

	return st;
}