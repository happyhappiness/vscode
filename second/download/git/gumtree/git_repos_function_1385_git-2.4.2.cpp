int color_parse_mem(const char *value, int value_len, char *dst)
{
	const char *ptr = value;
	int len = value_len;
	unsigned int attr = 0;
	struct color fg = { COLOR_UNSPECIFIED };
	struct color bg = { COLOR_UNSPECIFIED };

	if (!strncasecmp(value, "reset", len)) {
		strcpy(dst, GIT_COLOR_RESET);
		return 0;
	}

	/* [fg [bg]] [attr]... */
	while (len > 0) {
		const char *word = ptr;
		struct color c;
		int val, wordlen = 0;

		while (len > 0 && !isspace(word[wordlen])) {
			wordlen++;
			len--;
		}

		ptr = word + wordlen;
		while (len > 0 && isspace(*ptr)) {
			ptr++;
			len--;
		}

		if (!parse_color(&c, word, wordlen)) {
			if (fg.type == COLOR_UNSPECIFIED) {
				fg = c;
				continue;
			}
			if (bg.type == COLOR_UNSPECIFIED) {
				bg = c;
				continue;
			}
			goto bad;
		}
		val = parse_attr(word, wordlen);
		if (0 <= val)
			attr |= (1 << val);
		else
			goto bad;
	}

	if (attr || !color_empty(&fg) || !color_empty(&bg)) {
		int sep = 0;
		int i;

		*dst++ = '\033';
		*dst++ = '[';

		for (i = 0; attr; i++) {
			unsigned bit = (1 << i);
			if (!(attr & bit))
				continue;
			attr &= ~bit;
			if (sep++)
				*dst++ = ';';
			dst += sprintf(dst, "%d", i);
		}
		if (!color_empty(&fg)) {
			if (sep++)
				*dst++ = ';';
			/* foreground colors are all in the 3x range */
			dst = color_output(dst, &fg, '3');
		}
		if (!color_empty(&bg)) {
			if (sep++)
				*dst++ = ';';
			/* background colors are all in the 4x range */
			dst = color_output(dst, &bg, '4');
		}
		*dst++ = 'm';
	}
	*dst = 0;
	return 0;
bad:
	return error(_("invalid color value: %.*s"), value_len, value);
}