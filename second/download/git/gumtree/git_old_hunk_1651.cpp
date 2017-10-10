		git_config_string_dup(&opts->strategy, key, value);
	else if (!strcmp(key, "options.gpg-sign"))
		git_config_string_dup(&opts->gpg_sign, key, value);
	else if (!strcmp(key, "options.strategy-option")) {
		ALLOC_GROW(opts->xopts, opts->xopts_nr + 1, opts->xopts_alloc);
		opts->xopts[opts->xopts_nr++] = xstrdup(value);
	} else
		return error(_("invalid key: %s"), key);

	if (!error_flag)
		return error(_("invalid value for %s: %s"), key, value);

	return 0;
