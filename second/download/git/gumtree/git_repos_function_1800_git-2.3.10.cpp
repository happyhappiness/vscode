int simple_length(const char *match)
{
	int len = -1;

	for (;;) {
		unsigned char c = *match++;
		len++;
		if (c == '\0' || is_glob_special(c))
			return len;
	}
}