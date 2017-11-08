void strbuf_grow(struct strbuf *sb, size_t extra)
{
	int new_buf = !sb->alloc;
	if (unsigned_add_overflows(extra, 1) ||
	    unsigned_add_overflows(sb->len, extra + 1))
		die("you want to use way too much memory");
	if (new_buf)
		sb->buf = NULL;
	ALLOC_GROW(sb->buf, sb->len + extra + 1, sb->alloc);
	if (new_buf)
		sb->buf[0] = '\0';
}