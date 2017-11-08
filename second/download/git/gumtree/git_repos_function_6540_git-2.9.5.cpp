static int convert_date_line(char *dst, void **buf, unsigned long *sp)
{
	unsigned long size = *sp;
	char *line = *buf;
	char *next = strchr(line, '\n');
	char *date = strchr(line, '>');
	int len;

	if (!next || !date)
		die("missing or bad author/committer line %s", line);
	next++; date += 2;

	*buf = next;
	*sp = size - (next - line);

	len = date - line;
	memcpy(dst, line, len);
	dst += len;

	/* Is it already in new format? */
	if (isdigit(*date)) {
		int datelen = next - date;
		memcpy(dst, date, datelen);
		return len + datelen;
	}

	/*
	 * Hacky hacky: one of the sparse old-style commits does not have
	 * any date at all, but we can fake it by using the committer date.
	 */
	if (*date == '\n' && strchr(next, '>'))
		date = strchr(next, '>')+2;

	return len + sprintf(dst, "%lu -0700\n", parse_oldstyle_date(date));
}