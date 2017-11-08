static void http_status(struct strbuf *hdr, unsigned code, const char *msg)
{
	strbuf_addf(hdr, "Status: %u %s\r\n", code, msg);
}