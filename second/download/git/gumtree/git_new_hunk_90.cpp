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

static void split_ident_or_die(struct ident_split *id, const struct strbuf *buf)
{
	if (split_ident_line(id, buf->buf, buf->len) ||
	    !sane_ident_split(id))
		die(_("Malformed ident string: '%s'"), buf->buf);
}

static int author_date_is_interesting(void)
{
	return author_message || force_date;
}

static void adjust_comment_line_char(const struct strbuf *sb)
{
	char candidates[] = "#;@!$%^&|:";
	char *candidate;
	const char *p;

	comment_line_char = candidates[0];
	if (!memchr(sb->buf, comment_line_char, sb->len))
		return;

	p = sb->buf;
	candidate = strchr(candidates, *p);
	if (candidate)
		*candidate = ' ';
	for (p = sb->buf; *p; p++) {
		if ((p[0] == '\n' || p[0] == '\r') && p[1]) {
			candidate = strchr(candidates, p[1]);
			if (candidate)
				*candidate = ' ';
		}
	}

	for (p = candidates; *p == ' '; p++)
		;
	if (!*p)
		die(_("unable to select a comment character that is not used\n"
		      "in the current commit message"));
	comment_line_char = *p;
}

static int prepare_to_commit(const char *index_file, const char *prefix,
			     struct commit *current_head,
			     struct wt_status *s,
			     struct strbuf *author_ident)
