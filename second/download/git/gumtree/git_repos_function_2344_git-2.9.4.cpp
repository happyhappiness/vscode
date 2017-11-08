static size_t next_quote_pos(const char *s, ssize_t maxlen)
{
	size_t len;
	if (maxlen < 0) {
		for (len = 0; !sq_must_quote(s[len]); len++);
	} else {
		for (len = 0; len < maxlen && !sq_must_quote(s[len]); len++);
	}
	return len;
}