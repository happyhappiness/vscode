	if (fseek(fp, 0L, SEEK_SET))
		die_errno(_("fseek failed"));

	if (regcomp(&regex, header_regex, REG_NOSUB | REG_EXTENDED))
		die("invalid pattern: %s", header_regex);

	while (!strbuf_getline_crlf(&sb, fp)) {
		if (!sb.len)
			break; /* End of header */

		/* Ignore indented folded lines */
		if (*sb.buf == '\t' || *sb.buf == ' ')
			continue;
