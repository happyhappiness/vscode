void strbuf_trim(struct strbuf *sb)
{
	strbuf_rtrim(sb);
	strbuf_ltrim(sb);
}