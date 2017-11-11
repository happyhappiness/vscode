int log_format_has(const char *format, char esc)
{
	const char *p;

	if (!format)
		return 0;

	for (p = format; (p = strchr(p, '%')) != NULL; ) {
		for (p++; *p == '\''; p++) {} /*SHARED ITERATOR*/
		if (*p == '-')
			p++;
		while (isDigit(p))
			p++;
		while (*p == '\'') p++;
		if (!*p)
			break;
		if (*p == esc)
			return 1;
	}
	return 0;
}