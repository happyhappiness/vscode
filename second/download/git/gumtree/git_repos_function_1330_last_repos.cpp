static size_t trailing_spaces_len(const char *line, size_t len)
{
	const char *p;

	/* Expected format: ' ' x (1 or more)  */
	if (!len || line[len - 1] != ' ')
		return 0;

	p = line + len;
	while (p != line) {
		p--;
		if (*p != ' ')
			return line + len - (p + 1);
	}

	/* All spaces! */
	return len;
}