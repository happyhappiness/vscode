static int strbuf_getdelim(struct strbuf *sb, FILE *fp, int term)
{
	if (strbuf_getwholeline(sb, fp, term))
		return EOF;
	if (sb->buf[sb->len - 1] == term)
		strbuf_setlen(sb, sb->len - 1);
	return 0;
}