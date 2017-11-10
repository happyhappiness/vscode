static void cleanup_space(struct strbuf *sb)
{
	size_t pos, cnt;
	for (pos = 0; pos < sb->len; pos++) {
		if (isspace(sb->buf[pos])) {
			sb->buf[pos] = ' ';
			for (cnt = 0; isspace(sb->buf[pos + cnt + 1]); cnt++);
			strbuf_remove(sb, pos + 1, cnt);
		}
	}
}