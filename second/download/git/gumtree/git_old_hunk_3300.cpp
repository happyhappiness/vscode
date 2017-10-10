	int want_date = !(flag & IDENT_NO_DATE);
	int want_name = !(flag & IDENT_NO_NAME);

	if (want_name) {
		int using_default = 0;
		if (!name) {
			name = ident_default_name();
			using_default = 1;
			if (strict && default_name_is_bogus) {
				fputs(env_hint, stderr);
				die("unable to auto-detect name (got '%s')", name);
			}
			if (strict && ident_use_config_only
			    && !(ident_config_given & IDENT_NAME_GIVEN))
				die("user.useConfigOnly set but no name given");
		}
		if (!*name) {
			struct passwd *pw;
			if (strict) {
				if (using_default)
					fputs(env_hint, stderr);
