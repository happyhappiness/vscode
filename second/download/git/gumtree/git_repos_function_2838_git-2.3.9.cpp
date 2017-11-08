static char *canonicalize_client(const char *in)
{
	struct strbuf out = STRBUF_INIT;
	sanitize_client_strbuf(&out, in);
	strbuf_tolower(&out);
	return strbuf_detach(&out, NULL);
}