static inline void strbuf_complete_line(struct strbuf *sb)
{
	if (sb->len && sb->buf[sb->len - 1] != '\n')
		strbuf_addch(sb, '\n');
}