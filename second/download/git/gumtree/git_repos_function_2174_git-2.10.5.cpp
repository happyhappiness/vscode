static int is_scissors_line(const struct strbuf *line)
{
	size_t i, len = line->len;
	int scissors = 0, gap = 0;
	int first_nonblank = -1;
	int last_nonblank = 0, visible, perforation = 0, in_perforation = 0;
	const char *buf = line->buf;

	for (i = 0; i < len; i++) {
		if (isspace(buf[i])) {
			if (in_perforation) {
				perforation++;
				gap++;
			}
			continue;
		}
		last_nonblank = i;
		if (first_nonblank < 0)
			first_nonblank = i;
		if (buf[i] == '-') {
			in_perforation = 1;
			perforation++;
			continue;
		}
		if (i + 1 < len &&
		    (!memcmp(buf + i, ">8", 2) || !memcmp(buf + i, "8<", 2) ||
		     !memcmp(buf + i, ">%", 2) || !memcmp(buf + i, "%<", 2))) {
			in_perforation = 1;
			perforation += 2;
			scissors += 2;
			i++;
			continue;
		}
		in_perforation = 0;
	}

	/*
	 * The mark must be at least 8 bytes long (e.g. "-- >8 --").
	 * Even though there can be arbitrary cruft on the same line
	 * (e.g. "cut here"), in order to avoid misidentification, the
	 * perforation must occupy more than a third of the visible
	 * width of the line, and dashes and scissors must occupy more
	 * than half of the perforation.
	 */

	visible = last_nonblank - first_nonblank + 1;
	return (scissors && 8 <= visible &&
		visible < perforation * 3 &&
		gap * 2 < perforation);
}