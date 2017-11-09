static void strbuf_add_tabexpand(struct strbuf *sb, int tabwidth,
				 const char *line, int linelen)
{
	const char *tab;

	while ((tab = memchr(line, '\t', linelen)) != NULL) {
		int width = pp_utf8_width(line, tab);

		/*
		 * If it wasn't well-formed utf8, or it
		 * had characters with badly defined
		 * width (control characters etc), just
		 * give up on trying to align things.
		 */
		if (width < 0)
			break;

		/* Output the data .. */
		strbuf_add(sb, line, tab - line);

		/* .. and the de-tabified tab */
		strbuf_addchars(sb, ' ', tabwidth - (width % tabwidth));

		/* Skip over the printed part .. */
		linelen -= tab + 1 - line;
		line = tab + 1;
	}

	/*
	 * Print out everything after the last tab without
	 * worrying about width - there's nothing more to
	 * align.
	 */
	strbuf_add(sb, line, linelen);
}