int strbuf_normalize_path(struct strbuf *src)
{
	struct strbuf dst = STRBUF_INIT;

	strbuf_grow(&dst, src->len);
	if (normalize_path_copy(dst.buf, src->buf) < 0) {
		strbuf_release(&dst);
		return -1;
	}

	/*
	 * normalize_path does not tell us the new length, so we have to
	 * compute it by looking for the new NUL it placed
	 */
	strbuf_setlen(&dst, strlen(dst.buf));
	strbuf_swap(src, &dst);
	strbuf_release(&dst);
	return 0;
}