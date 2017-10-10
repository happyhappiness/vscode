}
#endif

static int grep_cmd_config(const char *var, const char *value, void *cb)
{
	int st = grep_config(var, value, cb);
	if (git_default_config(var, value, cb) < 0)
		st = -1;

	if (!strcmp(var, "grep.threads")) {
		num_threads = git_config_int(var, value);
		if (num_threads < 0)
			die(_("invalid number of threads specified (%d) for %s"),
