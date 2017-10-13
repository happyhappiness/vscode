int strbuf_getwholeline(struct strbuf *sb, FILE *fp, int term)
{
	ssize_t r;

	if (feof(fp))
		return EOF;

	strbuf_reset(sb);

	/* Translate slopbuf to NULL, as we cannot call realloc on it */
	if (!sb->alloc)
		sb->buf = NULL;
	r = getdelim(&sb->buf, &sb->alloc, term, fp);

	if (r > 0) {
		sb->len = r;
		return 0;
	}
	assert(r == -1);

	/*
	 * Normally we would have called xrealloc, which will try to free
	 * memory and recover. But we have no way to tell getdelim() to do so.
	 * Worse, we cannot try to recover ENOMEM ourselves, because we have
	 * no idea how many bytes were read by getdelim.
	 *
	 * Dying here is reasonable. It mirrors what xrealloc would do on
	 * catastrophic memory failure. We skip the opportunity to free pack
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