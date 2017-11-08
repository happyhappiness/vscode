static void read_props(void)
{
	static struct strbuf key = STRBUF_INIT;
	static struct strbuf val = STRBUF_INIT;
	const char *t;
	/*
	 * NEEDSWORK: to support simple mode changes like
	 *	K 11
	 *	svn:special
	 *	V 1
	 *	*
	 *	D 14
	 *	svn:executable
	 * we keep track of whether a mode has been set and reset to
	 * plain file only if not.  We should be keeping track of the
	 * symlink and executable bits separately instead.
	 */
	uint32_t type_set = 0;
	while ((t = buffer_read_line(&input)) && strcmp(t, "PROPS-END")) {
		uint32_t len;
		const char type = t[0];
		int ch;

		if (!type || t[1] != ' ')
			die("invalid property line: %s", t);
		len = atoi(&t[2]);
		strbuf_reset(&val);
		buffer_read_binary(&input, &val, len);
		if (val.len < len)
			die_short_read();

		/* Discard trailing newline. */
		ch = buffer_read_char(&input);
		if (ch == EOF)
			die_short_read();
		if (ch != '\n')
			die("invalid dump: expected newline after %s", val.buf);

		switch (type) {
		case 'K':
			strbuf_swap(&key, &val);
			continue;
		case 'D':
			handle_property(&val, NULL, &type_set);
			continue;
		case 'V':
			handle_property(&key, &val, &type_set);
			strbuf_reset(&key);
			continue;
		default:
			die("invalid property line: %s", t);
		}
	}
}