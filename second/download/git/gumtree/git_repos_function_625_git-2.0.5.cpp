static inline void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2)
{
	strbuf_grow(sb, sb2->len);
	strbuf_add(sb, sb2->buf, sb2->len);
}