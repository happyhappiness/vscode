static int parse_dirstat_params(struct diff_options *options, const char *params_string,
				struct strbuf *errmsg)
{
	char *params_copy = xstrdup(params_string);
	struct string_list params = STRING_LIST_INIT_NODUP;
	int ret = 0;
	int i;

	if (*params_copy)
		string_list_split_in_place(&params, params_copy, ',', -1);
	for (i = 0; i < params.nr; i++) {
		const char *p = params.items[i].string;
		if (!strcmp(p, "changes")) {
			DIFF_OPT_CLR(options, DIRSTAT_BY_LINE);
			DIFF_OPT_CLR(options, DIRSTAT_BY_FILE);
		} else if (!strcmp(p, "lines")) {
			DIFF_OPT_SET(options, DIRSTAT_BY_LINE);
			DIFF_OPT_CLR(options, DIRSTAT_BY_FILE);
		} else if (!strcmp(p, "files")) {
			DIFF_OPT_CLR(options, DIRSTAT_BY_LINE);
			DIFF_OPT_SET(options, DIRSTAT_BY_FILE);
		} else if (!strcmp(p, "noncumulative")) {
			DIFF_OPT_CLR(options, DIRSTAT_CUMULATIVE);
		} else if (!strcmp(p, "cumulative")) {
			DIFF_OPT_SET(options, DIRSTAT_CUMULATIVE);
		} else if (isdigit(*p)) {
			char *end;
			int permille = strtoul(p, &end, 10) * 10;
			if (*end == '.' && isdigit(*++end)) {
				/* only use first digit */
				permille += *end - '0';
				/* .. and ignore any further digits */
				while (isdigit(*++end))
					; /* nothing */
			}
			if (!*end)
				options->dirstat_permille = permille;
			else {
				strbuf_addf(errmsg, _("  Failed to parse dirstat cut-off percentage '%s'\n"),
					    p);
				ret++;
			}
		} else {
			strbuf_addf(errmsg, _("  Unknown dirstat parameter '%s'\n"), p);
			ret++;
		}

	}
	string_list_clear(&params, 0);
	free(params_copy);
	return ret;
}