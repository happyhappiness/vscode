static int has_conforming_footer(struct strbuf *sb, struct strbuf *sob,
	int ignore_footer)
{
	char prev;
	int i, k;
	int len = sb->len - ignore_footer;
	const char *buf = sb->buf;
	int found_sob = 0;

	/* footer must end with newline */
	if (!len || buf[len - 1] != '\n')
		return 0;

	prev = '\0';
	for (i = len - 1; i > 0; i--) {
		char ch = buf[i];
		if (prev == '\n' && ch == '\n') /* paragraph break */
			break;
		prev = ch;
	}

	/* require at least one blank line */
	if (prev != '\n' || buf[i] != '\n')
		return 0;

	/* advance to start of last paragraph */
	while (i < len - 1 && buf[i] == '\n')
		i++;

	for (; i < len; i = k) {
		int found_rfc2822;

		for (k = i; k < len && buf[k] != '\n'; k++)
			; /* do nothing */
		k++;

		found_rfc2822 = is_rfc2822_line(buf + i, k - i - 1);
		if (found_rfc2822 && sob &&
		    !strncmp(buf + i, sob->buf, sob->len))
			found_sob = k;

		if (!(found_rfc2822 ||
		      is_cherry_picked_from_line(buf + i, k - i - 1)))
			return 0;
	}
	if (found_sob == i)
		return 3;
	if (found_sob)
		return 2;
	return 1;
}