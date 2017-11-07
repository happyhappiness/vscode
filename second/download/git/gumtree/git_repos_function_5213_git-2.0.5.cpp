static int ansi_emulate(const char *str, FILE *stream)
{
	int rv = 0;
	const char *pos = str;

	while (*pos) {
		pos = strstr(str, "\033[");
		if (pos) {
			size_t len = pos - str;

			if (len) {
				size_t out_len = fwrite(str, 1, len, stream);
				rv += out_len;
				if (out_len < len)
					return rv;
			}

			str = pos + 2;
			rv += 2;

			fflush(stream);

			pos = set_attr(str);
			rv += pos - str;
			str = pos;
		} else {
			rv += strlen(str);
			fputs(str, stream);
			return rv;
		}
	}
	return rv;
}