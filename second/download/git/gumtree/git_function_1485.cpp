static void determine_author_info(struct strbuf *author_ident)
{
	char *name, *email, *date;
	struct ident_split author;
	char date_buf[64];

	name = getenv("GIT_AUTHOR_NAME");
	email = getenv("GIT_AUTHOR_EMAIL");
	date = getenv("GIT_AUTHOR_DATE");

	if (author_message) {
		const char *a, *lb, *rb, *eol;
		size_t len;

		a = strstr(author_message_buffer, "\nauthor ");
		if (!a)
			die(_("invalid commit: %s"), author_message);

		lb = strchrnul(a + strlen("\nauthor "), '<');
		rb = strchrnul(lb, '>');
		eol = strchrnul(rb, '\n');
		if (!*lb || !*rb || !*eol)
			die(_("invalid commit: %s"), author_message);

		if (lb == a + strlen("\nauthor "))
			/* \nauthor <foo@example.com> */
			name = xcalloc(1, 1);
		else
			name = xmemdupz(a + strlen("\nauthor "),
					(lb - strlen(" ") -
					 (a + strlen("\nauthor "))));
		email = xmemdupz(lb + strlen("<"), rb - (lb + strlen("<")));
		len = eol - (rb + strlen("> "));
		date = xmalloc(len + 2);
		*date = '@';
		memcpy(date + 1, rb + strlen("> "), len);
		date[len + 1] = '\0';
	}

	if (force_author) {
		const char *lb = strstr(force_author, " <");
		const char *rb = strchr(force_author, '>');

		if (!lb || !rb)
			die(_("malformed --author parameter"));
		name = xstrndup(force_author, lb - force_author);
		email = xstrndup(lb + 2, rb - (lb + 2));
	}

	if (force_date) {
		if (parse_force_date(force_date, date_buf, sizeof(date_buf)))
			die(_("invalid date format: %s"), force_date);
		date = date_buf;
	}

	strbuf_addstr(author_ident, fmt_ident(name, email, date, IDENT_STRICT));
	if (!split_ident_line(&author, author_ident->buf, author_ident->len) &&
	    sane_ident_split(&author)) {
		export_one("GIT_AUTHOR_NAME", author.name_begin, author.name_end, 0);
		export_one("GIT_AUTHOR_EMAIL", author.mail_begin, author.mail_end, 0);
		export_one("GIT_AUTHOR_DATE", author.date_begin, author.tz_end, '@');
	}
}