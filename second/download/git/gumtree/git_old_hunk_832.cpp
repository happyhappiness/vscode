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
