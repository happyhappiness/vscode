	if (strict && email == git_default_email.buf &&
	    strstr(email, "(none)")) {
		fputs(env_hint, stderr);
		die("unable to auto-detect email address (got '%s')", email);
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

const char *fmt_name(const char *name, const char *email)
{
	return fmt_ident(name, email, NULL, IDENT_STRICT | IDENT_NO_DATE);
