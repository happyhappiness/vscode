static const char *end_of_token(const char *s, int c, size_t n)
{
	const char *next = memchr(s, c, n);
	if (!next)
		next = s + n;
	return next;
}