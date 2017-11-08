static char *parse_ident(const char *buf)
{
	const char *ltgt;
	size_t name_len;
	char *ident;

	/* ensure there is a space delimiter even if there is no name */
	if (*buf == '<')
		--buf;

	ltgt = buf + strcspn(buf, "<>");
	if (*ltgt != '<')
		die("Missing < in ident string: %s", buf);
	if (ltgt != buf && ltgt[-1] != ' ')
		die("Missing space before < in ident string: %s", buf);
	ltgt = ltgt + 1 + strcspn(ltgt + 1, "<>");
	if (*ltgt != '>')
		die("Missing > in ident string: %s", buf);
	ltgt++;
	if (*ltgt != ' ')
		die("Missing space after > in ident string: %s", buf);
	ltgt++;
	name_len = ltgt - buf;
	ident = xmalloc(name_len + 24);
	strncpy(ident, buf, name_len);

	switch (whenspec) {
	case WHENSPEC_RAW:
		if (validate_raw_date(ltgt, ident + name_len, 24) < 0)
			die("Invalid raw date \"%s\" in ident: %s", ltgt, buf);
		break;
	case WHENSPEC_RFC2822:
		if (parse_date(ltgt, ident + name_len, 24) < 0)
			die("Invalid rfc2822 date \"%s\" in ident: %s", ltgt, buf);
		break;
	case WHENSPEC_NOW:
		if (strcmp("now", ltgt))
			die("Date in ident must be 'now': %s", buf);
		datestamp(ident + name_len, 24);
		break;
	}

	return ident;
}