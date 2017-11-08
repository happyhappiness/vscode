static size_t has_non_ascii(const char *s, size_t maxlen, size_t *strlen_c)
{
	const uint8_t *ptr = (const uint8_t *)s;
	size_t strlen_chars = 0;
	size_t ret = 0;

	if (!ptr || !*ptr)
		return 0;

	while (*ptr && maxlen) {
		if (*ptr & 0x80)
			ret++;
		strlen_chars++;
		ptr++;
		maxlen--;
	}
	if (strlen_c)
		*strlen_c = strlen_chars;

	return ret;
}