 * Make sure the format string is well formed, and parse out
 * the used atoms.
 */
static int verify_format(const char *format)
{
	const char *cp, *sp;
	static const char color_reset[] = "color:reset";

	need_color_reset_at_eol = 0;
	for (cp = format; *cp && (sp = find_next(cp)); ) {
		const char *ep = strchr(sp, ')');
		int at;

		if (!ep)
			return error("malformed format string %s", sp);
		/* sp points at "%(" and ep points at the closing ")" */
		at = parse_atom(sp + 2, ep);
		cp = ep + 1;

		if (starts_with(used_atom[at], "color:"))
			need_color_reset_at_eol = !!strcmp(used_atom[at], color_reset);
	}
	return 0;
}

/*
 * Given an object name, read the object data and size, and return a
