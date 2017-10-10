
		if (strict) {
			if (name == git_default_name.buf)
				fputs(env_hint, stderr);
			die("empty ident name (for <%s>) not allowed", email);
		}
		pw = xgetpwuid_self();
		name = pw->pw_name;
	}

	if (strict && email == git_default_email.buf &&
	    strstr(email, "(none)")) {
		fputs(env_hint, stderr);
		die("unable to auto-detect email address (got '%s')", email);
	}

	strbuf_reset(&ident);
	if (want_name) {
