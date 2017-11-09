char *quote_path_relative(const char *in, const char *prefix,
			  struct strbuf *out)
{
	struct strbuf sb = STRBUF_INIT;
	const char *rel = relative_path(in, prefix, &sb);
	strbuf_reset(out);
	quote_c_style_counted(rel, strlen(rel), out, NULL, 0);
	strbuf_release(&sb);

	return out->buf;
}