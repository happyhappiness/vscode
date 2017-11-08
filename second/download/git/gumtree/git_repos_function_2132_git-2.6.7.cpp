void strbuf_add_commented_lines(struct strbuf *out, const char *buf, size_t size)
{
	static char prefix1[3];
	static char prefix2[2];

	if (prefix1[0] != comment_line_char) {
		sprintf(prefix1, "%c ", comment_line_char);
		sprintf(prefix2, "%c", comment_line_char);
	}
	add_lines(out, prefix1, prefix2, buf, size);
}