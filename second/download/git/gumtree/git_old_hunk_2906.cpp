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

int git_config_colorbool(const char *var, const char *value)
{
	if (value) {
		if (!strcasecmp(value, "never"))
