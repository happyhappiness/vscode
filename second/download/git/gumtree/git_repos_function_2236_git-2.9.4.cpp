void strbuf_tolower(struct strbuf *sb)
{
	char *p = sb->buf, *end = sb->buf + sb->len;
	for (; p < end; p++)
		*p = tolower(*p);
}