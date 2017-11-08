static int prepare_lines(struct scoreboard *sb)
{
	const char *buf = sb->final_buf;
	unsigned long len = sb->final_buf_size;
	const char *end = buf + len;
	const char *p;
	int *lineno;
	int num = 0;

	for (p = buf; p < end; p = get_next_line(p, end))
		num++;

	sb->lineno = lineno = xmalloc(sizeof(*sb->lineno) * (num + 1));

	for (p = buf; p < end; p = get_next_line(p, end))
		*lineno++ = p - buf;

	*lineno = len;

	sb->num_lines = num;
	return sb->num_lines;
}