static char *sanitize_client(const char *in)
{
	struct strbuf out = STRBUF_INIT;
	sanitize_client_strbuf(&out, in);
	return strbuf_detach(&out, NULL);
}