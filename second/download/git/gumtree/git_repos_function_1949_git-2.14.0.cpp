static int parse_color(struct color *out, const char *name, int len)
{
	/* Positions in array must match ANSI color codes */
	static const char * const color_names[] = {
		"black", "red", "green", "yellow",
		"blue", "magenta", "cyan", "white"
	};
	char *end;
	int i;
	long val;

	/* First try the special word "normal"... */
	if (match_word(name, len, "normal")) {
		out->type = COLOR_NORMAL;
		return 0;
	}

	/* Try a 24-bit RGB value */
	if (len == 7 && name[0] == '#') {
		if (!get_hex_color(name + 1, &out->red) &&
		    !get_hex_color(name + 3, &out->green) &&
		    !get_hex_color(name + 5, &out->blue)) {
			out->type = COLOR_RGB;
			return 0;
		}
	}

	/* Then pick from our human-readable color names... */
	for (i = 0; i < ARRAY_SIZE(color_names); i++) {
		if (match_word(name, len, color_names[i])) {
			out->type = COLOR_ANSI;
			out->value = i;
			return 0;
		}
	}

	/* And finally try a literal 256-color-mode number */
	val = strtol(name, &end, 10);
	if (end - name == len) {
		/*
		 * Allow "-1" as an alias for "normal", but other negative
		 * numbers are bogus.
		 */
		if (val < -1)
			; /* fall through to error */
		else if (val < 0) {
			out->type = COLOR_NORMAL;
			return 0;
		/* Rewrite low numbers as more-portable standard colors. */
		} else if (val < 8) {
			out->type = COLOR_ANSI;
			out->value = val;
			return 0;
		} else if (val < 256) {
			out->type = COLOR_256;
			out->value = val;
			return 0;
		}
	}

	return -1;
}