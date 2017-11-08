int strbuf_getline(struct strbuf *sb, FILE *fp)
{
	if (strbuf_getwholeline(sb, fp, '\n'))
		return EOF;
	if (sb->buf[sb->len - 1] == '\n') {
		strbuf_setlen(sb, sb->len - 1);
		if (sb->len && sb->buf[sb->len - 1] == '\r')
			strbuf_setlen(sb, sb->len - 1);
	}
	return 0;
}