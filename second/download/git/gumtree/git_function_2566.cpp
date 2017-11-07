static int git_parse_source(config_fn_t fn, void *data)
{
	int comment = 0;
	int baselen = 0;
	struct strbuf *var = &cf->var;
	int error_return = 0;
	char *error_msg = NULL;

	/* U+FEFF Byte Order Mark in UTF8 */
	const char *bomptr = utf8_bom;

	for (;;) {
		int c = get_next_char();
		if (bomptr && *bomptr) {
			/* We are at the file beginning; skip UTF8-encoded BOM
			 * if present. Sane editors won't put this in on their
			 * own, but e.g. Windows Notepad will do it happily. */
			if (c == (*bomptr & 0377)) {
				bomptr++;
				continue;
			} else {
				/* Do not tolerate partial BOM. */
				if (bomptr != utf8_bom)
					break;
				/* No BOM at file beginning. Cool. */
				bomptr = NULL;
			}
		}
		if (c == '\n') {
			if (cf->eof)
				return 0;
			comment = 0;
			continue;
		}
		if (comment || isspace(c))
			continue;
		if (c == '#' || c == ';') {
			comment = 1;
			continue;
		}
		if (c == '[') {
			/* Reset prior to determining a new stem */
			strbuf_reset(var);
			if (get_base_var(var) < 0 || var->len < 1)
				break;
			strbuf_addch(var, '.');
			baselen = var->len;
			continue;
		}
		if (!isalpha(c))
			break;
		/*
		 * Truncate the var name back to the section header
		 * stem prior to grabbing the suffix part of the name
		 * and the value.
		 */
		strbuf_setlen(var, baselen);
		strbuf_addch(var, tolower(c));
		if (get_value(fn, data, var) < 0)
			break;
	}

	switch (cf->origin_type) {
	case CONFIG_ORIGIN_BLOB:
		error_msg = xstrfmt(_("bad config line %d in blob %s"),
				      cf->linenr, cf->name);
		break;
	case CONFIG_ORIGIN_FILE:
		error_msg = xstrfmt(_("bad config line %d in file %s"),
				      cf->linenr, cf->name);
		break;
	case CONFIG_ORIGIN_STDIN:
		error_msg = xstrfmt(_("bad config line %d in standard input"),
				      cf->linenr);
		break;
	case CONFIG_ORIGIN_SUBMODULE_BLOB:
		error_msg = xstrfmt(_("bad config line %d in submodule-blob %s"),
				       cf->linenr, cf->name);
		break;
	case CONFIG_ORIGIN_CMDLINE:
		error_msg = xstrfmt(_("bad config line %d in command line %s"),
				       cf->linenr, cf->name);
		break;
	default:
		error_msg = xstrfmt(_("bad config line %d in %s"),
				      cf->linenr, cf->name);
	}

	if (cf->die_on_error)
		die("%s", error_msg);
	else
		error_return = error("%s", error_msg);

	free(error_msg);
	return error_return;
}