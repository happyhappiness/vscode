	int lno = 0;
	struct strbuf sb = STRBUF_INIT;

	patterns = from_stdin ? stdin : fopen(arg, "r");
	if (!patterns)
		die_errno(_("cannot open '%s'"), arg);
	while (strbuf_getline(&sb, patterns, '\n') == 0) {
		/* ignore empty line like grep does */
		if (sb.len == 0)
			continue;

		append_grep_pat(grep_opt, sb.buf, sb.len, arg, ++lno,
				GREP_PATTERN);
