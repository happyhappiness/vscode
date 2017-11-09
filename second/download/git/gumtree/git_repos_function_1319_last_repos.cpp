static int read_patch_file(struct strbuf *sb, int fd)
{
	if (strbuf_read(sb, fd, 0) < 0)
		return error_errno("git apply: failed to read");

	/*
	 * Make sure that we have some slop in the buffer
	 * so that we can do speculative "memcmp" etc, and
	 * see to it that it is NUL-filled.
	 */
	strbuf_grow(sb, SLOP);
	memset(sb->buf + sb->len, 0, SLOP);
	return 0;
}