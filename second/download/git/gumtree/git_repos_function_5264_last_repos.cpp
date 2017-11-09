static void determine_author_info(struct strbuf *author_ident)
{
	char *name, *email, *date;
	struct ident_split author;

	name = xstrdup_or_null(getenv("GIT_AUTHOR_NAME"));
	email = xstrdup_or_null(getenv("GIT_AUTHOR_EMAIL"));
	date = xstrdup_or_null(getenv("GIT_AUTHOR_DATE"));

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
	assert_split_ident(&author, author_ident);
	export_one("GIT_AUTHOR_NAME", author.name_begin, author.name_end, 0);
	export_one("GIT_AUTHOR_EMAIL", author.mail_begin, author.mail_end, 0);
	export_one("GIT_AUTHOR_DATE", author.date_begin, author.tz_end, '@');
	free(name);
	free(email);
	free(date);
}