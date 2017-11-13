static int populate_opts_cb(const char *key, const char *value, void *data)
{
	struct replay_opts *opts = data;
	int error_flag = 1;

	if (!value)
		error_flag = 0;
	else if (!strcmp(key, "options.no-commit"))
		opts->no_commit = git_config_bool_or_int(key, value, &error_flag);
	else if (!strcmp(key, "options.edit"))
		opts->edit = git_config_bool_or_int(key, value, &error_flag);
	else if (!strcmp(key, "options.signoff"))
		opts->signoff = git_config_bool_or_int(key, value, &error_flag);
	else if (!strcmp(key, "options.record-origin"))
		opts->record_origin = git_config_bool_or_int(key, value, &error_flag);
	else if (!strcmp(key, "options.allow-ff"))
		opts->allow_ff = git_config_bool_or_int(key, value, &error_flag);
	else if (!strcmp(key, "options.mainline"))
		opts->mainline = git_config_int(key, value);
	else if (!strcmp(key, "options.strategy"))
		git_config_string(&opts->strategy, key, value);
	else if (!strcmp(key, "options.gpg-sign"))
		git_config_string(&opts->gpg_sign, key, value);
	else if (!strcmp(key, "options.strategy-option")) {
		ALLOC_GROW(opts->xopts, opts->xopts_nr + 1, opts->xopts_alloc);
		opts->xopts[opts->xopts_nr++] = xstrdup(value);
	} else
		return error(_("Invalid key: %s"), key);

	if (!error_flag)
		return error(_("Invalid value for %s: %s"), key, value);

	return 0;
}