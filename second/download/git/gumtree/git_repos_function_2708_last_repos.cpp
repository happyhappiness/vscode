ssize_t strbuf_write(struct strbuf *sb, FILE *f)
{
	return sb->len ? fwrite(sb->buf, 1, sb->len, f) : 0;
}