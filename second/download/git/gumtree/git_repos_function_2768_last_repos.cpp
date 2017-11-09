static const char *next_line(const char *line, size_t len)
{
	const char *nl = memchr(line, '\n', len);
	if (!nl)
		return line + len; /* incomplete line */
	return nl + 1;
}