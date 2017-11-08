void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2)
{
	strbuf_grow(sb, sb2->len);
	memcpy(sb->buf + sb->len, sb2->buf, sb2->len);
	strbuf_setlen(sb, sb->len + sb2->len);
}