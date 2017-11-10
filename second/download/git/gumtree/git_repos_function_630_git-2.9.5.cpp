size_t parse_signature(const char *buf, unsigned long size)
{
	char *eol;
	size_t len = 0;
	while (len < size && !starts_with(buf + len, PGP_SIGNATURE) &&
			!starts_with(buf + len, PGP_MESSAGE)) {
		eol = memchr(buf + len, '\n', size - len);
		len += eol ? eol - (buf + len) + 1 : size - len;
	}
	return len;
}