	if (cp[0] && cp[1])
		return (hex1(cp[0]) << 4) | hex1(cp[1]);
	else
		return -1;
}

static void emit(const char *cp, const char *ep)
{
	while (*cp && (!ep || cp < ep)) {
		if (*cp == '%') {
			if (cp[1] == '%')
				cp++;
			else {
				int ch = hex2(cp + 1);
				if (0 <= ch) {
					putchar(ch);
					cp += 3;
					continue;
				}
			}
		}
		putchar(*cp);
		cp++;
	}
}

void show_ref_array_item(struct ref_array_item *info, const char *format, int quote_style)
{
	const char *cp, *sp, *ep;

	for (cp = format; *cp && (sp = find_next(cp)); cp = ep + 1) {
		struct atom_value *atomv;

		ep = strchr(sp, ')');
		if (cp < sp)
			emit(cp, sp);
		get_ref_atom_value(info, parse_ref_filter_atom(sp + 2, ep), &atomv);
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

/*  If no sorting option is given, use refname to sort as default */
struct ref_sorting *ref_default_sorting(void)
{
