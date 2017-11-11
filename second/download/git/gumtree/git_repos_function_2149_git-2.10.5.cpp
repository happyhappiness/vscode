static const char *parse_range_funcname(const char *arg, nth_line_fn_t nth_line_cb,
					void *cb_data, long lines, long anchor, long *begin, long *end,
					const char *path)
{
	char *pattern;
	const char *term;
	struct userdiff_driver *drv;
	xdemitconf_t *xecfg = NULL;
	const char *start;
	const char *p;
	int reg_error;
	regex_t regexp;

	if (*arg == '^') {
		anchor = 1;
		arg++;
	}

	assert(*arg == ':');
	term = arg+1;
	while (*term && *term != ':') {
		if (*term == '\\' && *(term+1))
			term++;
		term++;
	}
	if (term == arg+1)
		return NULL;
	if (!begin) /* skip_range_arg case */
		return term;

	pattern = xstrndup(arg+1, term-(arg+1));

	anchor--; /* input is in human terms */
	start = nth_line_cb(cb_data, anchor);

	drv = userdiff_find_by_path(path);
	if (drv && drv->funcname.pattern) {
		const struct userdiff_funcname *pe = &drv->funcname;
		xecfg = xcalloc(1, sizeof(*xecfg));
		xdiff_set_find_func(xecfg, pe->pattern, pe->cflags);
	}

	reg_error = regcomp(&regexp, pattern, REG_NEWLINE);
	if (reg_error) {
		char errbuf[1024];
		regerror(reg_error, &regexp, errbuf, 1024);
		die("-L parameter '%s': %s", pattern, errbuf);
	}

	p = find_funcname_matching_regexp(xecfg, (char*) start, &regexp);
	if (!p)
		die("-L parameter '%s' starting at line %ld: no match",
		    pattern, anchor + 1);
	*begin = 0;
	while (p > nth_line_cb(cb_data, *begin))
		(*begin)++;

	if (*begin >= lines)
		die("-L parameter '%s' matches at EOF", pattern);

	*end = *begin+1;
	while (*end < lines) {
		const char *bol = nth_line_cb(cb_data, *end);
		const char *eol = nth_line_cb(cb_data, *end+1);
		if (match_funcname(xecfg, bol, eol))
			break;
		(*end)++;
	}

	regfree(&regexp);
	free(xecfg);
	free(pattern);

	/* compensate for 1-based numbering */
	(*begin)++;

	return term;
}