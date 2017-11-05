static void show_ref(struct refinfo *info, const char *format, int quote_style)
{
	const char *cp, *sp, *ep;

	for (cp = format; *cp && (sp = find_next(cp)); cp = ep + 1) {
		struct atom_value *atomv;

		ep = strchr(sp, ')');
		if (cp < sp)
			emit(cp, sp);
		get_value(info, parse_atom(sp + 2, ep), &atomv);
		print_value(atomv, quote_style);
	}
	if (*cp) {
		sp = cp + strlen(cp);
		emit(cp, sp);
	}
	if (need_color_reset_at_eol) {
		struct atom_value resetv;
		char color[COLOR_MAXLEN] = "";

		if (color_parse("reset", color) < 0)
			die("BUG: couldn't parse 'reset' as a color");
		resetv.s = color;
		print_value(&resetv, quote_style);
	}
	putchar('\n');
}