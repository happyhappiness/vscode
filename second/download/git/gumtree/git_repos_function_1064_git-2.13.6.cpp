void strbuf_add_wrapped_bytes(struct strbuf *buf, const char *data, int len,
			     int indent, int indent2, int width)
{
	char *tmp = xstrndup(data, len);
	strbuf_add_wrapped_text(buf, tmp, indent, indent2, width);
	free(tmp);
}