int is_utf8(const char *text)
{
	while (*text) {
		if (*text == '\n' || *text == '\t' || *text == '\r') {
			text++;
			continue;
		}
		utf8_width(&text, NULL);
		if (!text)
			return 0;
	}
	return 1;
}