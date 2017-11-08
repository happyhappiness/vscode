static const char *parse_ref_line(struct strbuf *line, unsigned char *sha1)
{
	const char *ref;

	/*
	 * 42: the answer to everything.
	 *
	 * In this case, it happens to be the answer to
	 *  40 (length of sha1 hex representation)
	 *  +1 (space in between hex and name)
	 *  +1 (newline at the end of the line)
	 */
	if (line->len <= 42)
		return NULL;

	if (get_sha1_hex(line->buf, sha1) < 0)
		return NULL;
	if (!isspace(line->buf[40]))
		return NULL;

	ref = line->buf + 41;
	if (isspace(*ref))
		return NULL;

	if (line->buf[line->len - 1] != '\n')
		return NULL;
	line->buf[--line->len] = 0;

	return ref;
}