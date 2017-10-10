
		if (strict) {
			if (name == git_default_name.buf)
				fputs(env_hint, stderr);
			die("empty ident name (for <%s>) not allowed", email);
		}
		pw = xgetpwuid_self(NULL);
		name = pw->pw_name;
	}

	if (want_name && strict &&
	    name == git_default_name.buf && default_name_is_bogus) {
		fputs(env_hint, stderr);
		die("unable to auto-detect name (got '%s')", name);
	}

	if (strict && email == git_default_email.buf && default_email_is_bogus) {
		fputs(env_hint, stderr);
		die("unable to auto-detect email address (got '%s')", email);
	}

	strbuf_reset(&ident);
	if (want_name) {
