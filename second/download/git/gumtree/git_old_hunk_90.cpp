		if (!lb || !rb)
			die(_("malformed --author parameter"));
		name = xstrndup(force_author, lb - force_author);
		email = xstrndup(lb + 2, rb - (lb + 2));
	}

	if (force_date)
		date = force_date;
	strbuf_addstr(author_ident, fmt_ident(name, email, date, IDENT_STRICT));
	if (!split_ident_line(&author, author_ident->buf, author_ident->len) &&
	    sane_ident_split(&author)) {
		export_one("GIT_AUTHOR_NAME", author.name_begin, author.name_end, 0);
		export_one("GIT_AUTHOR_EMAIL", author.mail_begin, author.mail_end, 0);
		export_one("GIT_AUTHOR_DATE", author.date_begin, author.tz_end, '@');
	}
}

static char *cut_ident_timestamp_part(char *string)
{
	char *ket = strrchr(string, '>');
	if (!ket || ket[1] != ' ')
		die(_("Malformed ident string: '%s'"), string);
	*++ket = '\0';
	return ket;
}

static int prepare_to_commit(const char *index_file, const char *prefix,
			     struct commit *current_head,
			     struct wt_status *s,
			     struct strbuf *author_ident)
