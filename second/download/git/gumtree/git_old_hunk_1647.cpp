}

/*
 * Make sure the format string is well formed, and parse out
 * the used atoms.
 */
int verify_ref_format(const char *format)
{
	const char *cp, *sp;

	need_color_reset_at_eol = 0;
	for (cp = format; *cp && (sp = find_next(cp)); ) {
		const char *color, *ep = strchr(sp, ')');
		int at;

		if (!ep)
			return error(_("malformed format string %s"), sp);
		/* sp points at "%(" and ep points at the closing ")" */
		at = parse_ref_filter_atom(sp + 2, ep);
		cp = ep + 1;

		if (skip_prefix(used_atom[at].name, "color:", &color))
			need_color_reset_at_eol = !!strcmp(color, "reset");
	}
	return 0;
}

/*
 * Given an object name, read the object data and size, and return a
 * "struct object".  If the object data we are returning is also borrowed
