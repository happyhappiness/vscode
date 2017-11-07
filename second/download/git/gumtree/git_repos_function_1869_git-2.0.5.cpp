void strbuf_add_lines(struct strbuf *out, const char *prefix,
		      const char *buf, size_t size)
{
	add_lines(out, prefix, NULL, buf, size);
}