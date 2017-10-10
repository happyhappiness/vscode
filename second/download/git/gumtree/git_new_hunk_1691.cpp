	if (!person->date_begin || !person->date_end ||
	    !person->tz_begin || !person->tz_end)
		return 0;
	return 1;
}

static int parse_force_date(const char *in, struct strbuf *out)
{
	strbuf_addch(out, '@');

	if (parse_date(in, out) < 0) {
		int errors = 0;
		unsigned long t = approxidate_careful(in, &errors);
		if (errors)
			return -1;
		strbuf_addf(out, "%lu", t);
	}

	return 0;
}

static void set_ident_var(char **buf, char *val)
{
	free(*buf);
	*buf = val;
}

static char *envdup(const char *var)
{
	const char *val = getenv(var);
	return val ? xstrdup(val) : NULL;
}

static void determine_author_info(struct strbuf *author_ident)
{
	char *name, *email, *date;
	struct ident_split author;

	name = envdup("GIT_AUTHOR_NAME");
	email = envdup("GIT_AUTHOR_EMAIL");
	date = envdup("GIT_AUTHOR_DATE");

	if (author_message) {
		struct ident_split ident;
		size_t len;
		const char *a;

		a = find_commit_header(author_message_buffer, "author", &len);
		if (!a)
			die(_("commit '%s' lacks author header"), author_message);
		if (split_ident_line(&ident, a, len) < 0)
			die(_("commit '%s' has malformed author line"), author_message);

		set_ident_var(&name, xmemdupz(ident.name_begin, ident.name_end - ident.name_begin));
		set_ident_var(&email, xmemdupz(ident.mail_begin, ident.mail_end - ident.mail_begin));

		if (ident.date_begin) {
			struct strbuf date_buf = STRBUF_INIT;
			strbuf_addch(&date_buf, '@');
			strbuf_add(&date_buf, ident.date_begin, ident.date_end - ident.date_begin);
			strbuf_addch(&date_buf, ' ');
			strbuf_add(&date_buf, ident.tz_begin, ident.tz_end - ident.tz_begin);
			set_ident_var(&date, strbuf_detach(&date_buf, NULL));
		}
	}

	if (force_author) {
		struct ident_split ident;

		if (split_ident_line(&ident, force_author, strlen(force_author)) < 0)
			die(_("malformed --author parameter"));
		set_ident_var(&name, xmemdupz(ident.name_begin, ident.name_end - ident.name_begin));
		set_ident_var(&email, xmemdupz(ident.mail_begin, ident.mail_end - ident.mail_begin));
	}

	if (force_date) {
		struct strbuf date_buf = STRBUF_INIT;
		if (parse_force_date(force_date, &date_buf))
			die(_("invalid date format: %s"), force_date);
		set_ident_var(&date, strbuf_detach(&date_buf, NULL));
	}

	strbuf_addstr(author_ident, fmt_ident(name, email, date, IDENT_STRICT));
	if (!split_ident_line(&author, author_ident->buf, author_ident->len) &&
	    sane_ident_split(&author)) {
		export_one("GIT_AUTHOR_NAME", author.name_begin, author.name_end, 0);
		export_one("GIT_AUTHOR_EMAIL", author.mail_begin, author.mail_end, 0);
		export_one("GIT_AUTHOR_DATE", author.date_begin, author.tz_end, '@');
	}

	free(name);
	free(email);
	free(date);
}

static void split_ident_or_die(struct ident_split *id, const struct strbuf *buf)
{
	if (split_ident_line(id, buf->buf, buf->len) ||
	    !sane_ident_split(id))
