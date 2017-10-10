{
	static struct strbuf ident = STRBUF_INIT;
	int strict = (flag & IDENT_STRICT);
	int want_date = !(flag & IDENT_NO_DATE);
	int want_name = !(flag & IDENT_NO_NAME);

	if (!email) {
		if (strict && ident_use_config_only
		    && !(ident_config_given & IDENT_MAIL_GIVEN)) {
			fputs(_(env_hint), stderr);
			die(_("no email was given and auto-detection is disabled"));
		}
		email = ident_default_email();
		if (strict && default_email_is_bogus) {
			fputs(_(env_hint), stderr);
			die(_("unable to auto-detect email address (got '%s')"), email);
		}
	}

	if (want_name) {
		int using_default = 0;
		if (!name) {
			if (strict && ident_use_config_only
			    && !(ident_config_given & IDENT_NAME_GIVEN)) {
				fputs(_(env_hint), stderr);
				die(_("no name was given and auto-detection is disabled"));
			}
			name = ident_default_name();
			using_default = 1;
			if (strict && default_name_is_bogus) {
				fputs(_(env_hint), stderr);
				die(_("unable to auto-detect name (got '%s')"), name);
			}
		}
		if (!*name) {
			struct passwd *pw;
			if (strict) {
				if (using_default)
					fputs(_(env_hint), stderr);
				die(_("empty ident name (for <%s>) not allowed"), email);
			}
			pw = xgetpwuid_self(NULL);
			name = pw->pw_name;
		}
		if (strict && !has_non_crud(name))
			die(_("name consists only of disallowed characters: %s"), name);
	}

	strbuf_reset(&ident);
	if (want_name) {
		strbuf_addstr_without_crud(&ident, name);
		strbuf_addstr(&ident, " <");
