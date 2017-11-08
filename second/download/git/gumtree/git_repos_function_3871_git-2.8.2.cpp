const char *fmt_ident(const char *name, const char *email,
		      const char *date_str, int flag)
{
	static struct strbuf ident = STRBUF_INIT;
	int strict = (flag & IDENT_STRICT);
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
				die("empty ident name (for <%s>) not allowed", email);
			}
			pw = xgetpwuid_self(NULL);
			name = pw->pw_name;
		}
	}

	if (!email) {
		email = ident_default_email();
		if (strict && default_email_is_bogus) {
			fputs(env_hint, stderr);
			die("unable to auto-detect email address (got '%s')", email);
		}
		if (strict && ident_use_config_only
		    && !(ident_config_given & IDENT_MAIL_GIVEN))
			die("user.useConfigOnly set but no mail given");
	}

	strbuf_reset(&ident);
	if (want_name) {
		strbuf_addstr_without_crud(&ident, name);
		strbuf_addstr(&ident, " <");
	}
	strbuf_addstr_without_crud(&ident, email);
	if (want_name)
			strbuf_addch(&ident, '>');
	if (want_date) {
		strbuf_addch(&ident, ' ');
		if (date_str && date_str[0]) {
			if (parse_date(date_str, &ident) < 0)
				die("invalid date format: %s", date_str);
		}
		else
			strbuf_addstr(&ident, ident_default_date());
	}

	return ident.buf;
}