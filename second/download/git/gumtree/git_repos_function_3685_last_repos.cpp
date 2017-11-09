static void canonicalize_client(struct strbuf *out, const char *in)
{
	sanitize_client(out, in);
	strbuf_tolower(out);
}