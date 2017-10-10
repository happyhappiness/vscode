	c->refs_from_env = 0;
	c->mode_from_env = 0;
	if (rewrite_mode_env) {
		c->mode_from_env = 1;
		c->combine = parse_combine_notes_fn(rewrite_mode_env);
		if (!c->combine)
			/* TRANSLATORS: The first %s is the name of the
			   environment variable, the second %s is its value */
			error(_("Bad %s value: '%s'"), GIT_NOTES_REWRITE_MODE_ENVIRONMENT,
					rewrite_mode_env);
	}
	if (rewrite_refs_env) {
		c->refs_from_env = 1;
		string_list_add_refs_from_colon_sep(c->refs, rewrite_refs_env);
