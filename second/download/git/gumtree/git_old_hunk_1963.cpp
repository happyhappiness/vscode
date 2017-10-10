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
		die(_("Malformed ident string: '%s'"), buf->buf);
}

static int author_date_is_interesting(void)
{
	return author_message || force_date;
}

static void adjust_comment_line_char(const struct strbuf *sb)
