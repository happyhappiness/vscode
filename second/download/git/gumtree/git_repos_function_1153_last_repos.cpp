int utf8_strnwidth(const char *string, int len, int skip_ansi)
{
	int width = 0;
	const char *orig = string;

	if (len == -1)
		len = strlen(string);
	while (string && string < orig + len) {
		int skip;
		while (skip_ansi &&
		       (skip = display_mode_esc_sequence_len(string)) != 0)
			string += skip;
		width += utf8_width(&string, NULL);
	}
	return string ? width : len;
}