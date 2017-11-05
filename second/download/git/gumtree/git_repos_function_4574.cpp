static size_t fractional_time_len(const char *line, size_t len)
{
	const char *p;
	size_t n;

	/* Expected format: 19:41:17.620000023 */
	if (!len || !isdigit(line[len - 1]))
		return 0;
	p = line + len - 1;

	/* Fractional seconds. */
	while (p > line && isdigit(*p))
		p--;
	if (*p != '.')
		return 0;

	/* Hours, minutes, and whole seconds. */
	n = short_time_len(line, p - line);
	if (!n)
		return 0;

	return line + len - p + n;
}