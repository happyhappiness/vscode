}

/*
 * Make sure the format string is well formed, and parse out
 * the used atoms.
 */
int verify_ref_format(struct ref_format *format)
{
	const char *cp, *sp;

	format->need_color_reset_at_eol = 0;
	for (cp = format->format; *cp && (sp = find_next(cp)); ) {
		const char *color, *ep = strchr(sp, ')');
		int at;

		if (!ep)
			return error(_("malformed format string %s"), sp);
		/* sp points at "%(" and ep points at the closing ")" */
		at = parse_ref_filter_atom(format, sp + 2, ep);
		cp = ep + 1;

		if (skip_prefix(used_atom[at].name, "color:", &color))
			format->need_color_reset_at_eol = !!strcmp(color, "reset");
	}
	if (format->need_color_reset_at_eol && !want_color(format->use_color))
		format->need_color_reset_at_eol = 0;
	return 0;
}

/*
 * Given an object name, read the object data and size, and return a
 * "struct object".  If the object data we are returning is also borrowed
