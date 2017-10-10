	 * memory and retry, but that's unlikely to help for a malloc small
	 * enough to hold a single line of input, anyway.
	 */
	if (errno == ENOMEM)
		die("Out of memory, getdelim failed");

	/*
	 * Restore strbuf invariants; if getdelim left us with a NULL pointer,
	 * we can just re-init, but otherwise we should make sure that our
	 * length is empty, and that the result is NUL-terminated.
	 */
	if (!sb->buf)
		strbuf_init(sb, 0);
	else
		strbuf_reset(sb);
	return EOF;
}
#else
int strbuf_getwholeline(struct strbuf *sb, FILE *fp, int term)
{
	int ch;
