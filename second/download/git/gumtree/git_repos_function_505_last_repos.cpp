static const char *get_next_line(const char *start, const char *end)
{
	const char *nl = memchr(start, '\n', end - start);
	return nl ? nl + 1 : end;
}