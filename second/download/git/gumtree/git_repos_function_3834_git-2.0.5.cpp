static int prepare_lines(struct scoreboard *sb)
{
	const char *buf = sb->final_buf;
	unsigned long len = sb->final_buf_size;
	const char *end = buf + len;
	const char *p;
	int *lineno;
	int num = 0, incomplete = 0;

	for (p = buf;;) {
		p = memchr(p, '\n', end - p);
		if (p) {
			p++;
			num++;
			continue;
		}
		break;
	}

	if (len && end[-1] != '\n')
		incomplete++; /* incomplete line at the end */

	sb->lineno = xmalloc(sizeof(*sb->lineno) * (num + incomplete + 1));
	lineno = sb->lineno;

	*lineno++ = 0;
	for (p = buf;;) {
		p = memchr(p, '\n', end - p);
		if (p) {
			p++;
			*lineno++ = p - buf;
			continue;
		}
		break;
	}

	if (incomplete)
		*lineno++ = len;

	sb->num_lines = num + incomplete;
	return sb->num_lines;
}