	 * memory and retry, but that's unlikely to help for a malloc small
	 * enough to hold a single line of input, anyway.
	 */
	if (errno == ENOMEM)
		die("Out of memory, getdelim failed");

	/* Restore slopbuf that we moved out of the way before */
	if (!sb->buf)
		strbuf_init(sb, 0);
	return EOF;
}
#else
int strbuf_getwholeline(struct strbuf *sb, FILE *fp, int term)
{
	int ch;
