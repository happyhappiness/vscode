void color_parse_mem(const char *value, int value_len, const char *var,
		char *dst)
{
	const char *ptr = value;
	int len = value_len;
	unsigned int attr = 0;
	int fg = -2;
	int bg = -2;

	if (!strncasecmp(value, "reset", len)) {
		strcpy(dst, GIT_COLOR_RESET);
		return;
	}

	/* [fg [bg]] [attr]... */
	while (len > 0) {
		const char *word = ptr;
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

		val = parse_color(word, wordlen);
		if (val >= -1) {
			if (fg == -2) {
				fg = val;
				continue;
			}
			if (bg == -2) {
				bg = val;
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

	if (attr || fg >= 0 || bg >= 0) {
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
			*dst++ = '0' + i;
		}
		if (fg >= 0) {
			if (sep++)
				*dst++ = ';';
			if (fg < 8) {
				*dst++ = '3';
				*dst++ = '0' + fg;
			} else {
				dst += sprintf(dst, "38;5;%d", fg);
			}
		}
		if (bg >= 0) {
			if (sep++)
				*dst++ = ';';
			if (bg < 8) {
				*dst++ = '4';
				*dst++ = '0' + bg;
			} else {
				dst += sprintf(dst, "48;5;%d", bg);
			}
		}
		*dst++ = 'm';
	}
	*dst = 0;
	return;
bad:
	die("bad color value '%.*s' for variable '%s'", value_len, value, var);
}