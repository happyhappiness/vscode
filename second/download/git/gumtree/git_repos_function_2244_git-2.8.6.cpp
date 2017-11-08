ssize_t strbuf_read_once(struct strbuf *sb, int fd, size_t hint)
{
	ssize_t cnt;

	strbuf_grow(sb, hint ? hint : 8192);
	cnt = xread(fd, sb->buf + sb->len, sb->alloc - sb->len - 1);
	if (cnt > 0)
		strbuf_setlen(sb, sb->len + cnt);
	return cnt;
}